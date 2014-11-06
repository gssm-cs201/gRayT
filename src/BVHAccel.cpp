#include "gssmraytracer/utils/BVHAccel.h"
#include "gssmraytracer/geometry/BBox.h"
#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/memory/Memory.h"
#include <algorithm>
#define SPLIT_MIDDLE 111
#define SPLIT_SAH 222

using namespace gssmraytracer::memory;
namespace gssmraytracer {
  namespace utils {


    struct BVHPrimitiveInfo {
      BVHPrimitiveInfo(const int pn, const geometry::BBox &b) : primitiveNumber(pn), bounds(b) {
        centroid = b.centroid();
        std::cout << "bbox = " << b << std::endl;
        std::cout << "centroid = " << centroid << std::endl;
      }
      int primitiveNumber;
      geometry::Point centroid;
      geometry::BBox bounds;
    };

    struct LinearBVHNode {
      geometry::BBox bounds;
      union {
        int primitivesOffset; // leaf
        int secondChildOffset; // interior
      };
      int nPrimitives;
      int axis;
      int pad[2];
    };

    struct BVHBuildNode {
      BVHBuildNode() { children[0] = children[1] = NULL;}

      void initLeaf(int first, int n, const geometry::BBox &b) {
        firstPrimOffset = first;
        nPrimitives = n;
        bounds = b;
      }


      void initInterior(int axis, BVHBuildNode *c0, BVHBuildNode *c1) {
        children[0] = c0;
        children[1] = c1;
        bounds = combine(c0, c1);
        splitAxis = axis;
        nPrimitives = 0;
      }

      const geometry::BBox combine(BVHBuildNode *c0, BVHBuildNode *c1) const {
        return c0->bounds.combine(c1->bounds);
      }

      geometry::BBox bounds;
      BVHBuildNode *children[2];
      int splitAxis, firstPrimOffset, nPrimitives;
    };

    struct CompareToMid {
      CompareToMid(int d, float m) : dim(d), mid(m) {}
      int dim;
      float mid;
      bool operator()(const BVHPrimitiveInfo &a) const {
        return a.centroid[dim] < mid;
      }
    };
    struct ComparePoints {
      ComparePoints(int d) : dim(d) {}
      int dim;
      bool operator()(const BVHPrimitiveInfo &a,
                      const BVHPrimitiveInfo &b) const {
                        return a.centroid[dim] < b.centroid[dim];
                      }
    };
    struct CompareToBucket {
      CompareToBucket(int split, int num, int d, const geometry::BBox &b)
        : centroidBounds(b) { splitBucket = split; nBuckets = num; dim = d; }
        bool operator()(const BVHPrimitiveInfo &p) const;
        int splitBucket, nBuckets, dim;
        const geometry::BBox &centroidBounds;
    };

    class BVHAccel::Impl {
    public:
      std::vector<std::shared_ptr<geometry::Primitive> > primitives;
      int maxPrimsInNodes;
      LinearBVHNode *nodes;

      BVHBuildNode *recursiveBuild(std::vector<BVHPrimitiveInfo> &buildData,
              int start, int end, int *totalNodes, std::vector<std::shared_ptr<geometry::Primitive> > &orderedPrims);
      int flattenBVHTree(BVHBuildNode *node, int *offset);

    };

    BVHAccel::~BVHAccel() {
      FreeAligned(mImpl->nodes);
    }

    bool CompareToBucket::operator()(const BVHPrimitiveInfo &p) const {
      int b = nBuckets * ((p.centroid[dim] - centroidBounds.min()[dim])/
            (centroidBounds.max()[dim] - centroidBounds.min()[dim]));
      if (b == nBuckets) b = nBuckets - 1;
      return b <= splitBucket;
    }


    BVHAccel::BVHAccel(const std::vector<std::shared_ptr<geometry::Primitive> > &prims, const int maxPrimsInNodes): mImpl(new Impl) {

      mImpl->primitives = prims;
      mImpl->maxPrimsInNodes = maxPrimsInNodes;

      if (prims.size() == 0) {
        mImpl->nodes = NULL;
        return;
      }

      // initialize buildData array for primitives
      std::vector<BVHPrimitiveInfo> buildData;
      buildData.reserve(mImpl->primitives.size());

      for (int i = 0; i < mImpl->primitives.size(); ++i) {
        geometry::BBox bbox = prims[i]->worldBound();
        buildData.push_back(BVHPrimitiveInfo(i, bbox));
      }



      // Recursively build BVH tree for primitives
      int totalNodes = 0;
      std::vector<std::shared_ptr<geometry::Primitive> > orderedPrims;
      orderedPrims.reserve(mImpl->primitives.size());
      BVHBuildNode *root = mImpl->recursiveBuild(buildData, 0, mImpl->primitives.size(), &totalNodes, orderedPrims);
      mImpl->primitives.swap(orderedPrims);

      // compute representation of depth-first traversal of BVH tree
      mImpl->nodes = AllocAligned<LinearBVHNode>(totalNodes);

      for (int i = 0; i < totalNodes; ++i) {
        new(&mImpl->nodes[i]) LinearBVHNode;
      }
      int offset = 0;
      mImpl->flattenBVHTree(root, &offset);

      std::cout << "offset = " << offset << " totalNodes = " << totalNodes << std::endl;

    }

    int BVHAccel::Impl::flattenBVHTree(BVHBuildNode *node, int *offset) {
      LinearBVHNode *linearNode = NULL;
      linearNode = &nodes[*offset];

      linearNode->bounds = node->bounds;
      int myOffset = (*offset)++;

      if (node->nPrimitives > 0) {
        linearNode->primitivesOffset = node->firstPrimOffset;
        linearNode->nPrimitives = node->nPrimitives;
      }
      else {
        // create interior flattened BVH node
        linearNode->axis = node->splitAxis;
        linearNode->nPrimitives = 0;
        flattenBVHTree(node->children[0], offset);
        linearNode->secondChildOffset = flattenBVHTree(node->children[1], offset);
      }
      return myOffset;
    }

    BVHBuildNode *BVHAccel::Impl::recursiveBuild(
            std::vector<BVHPrimitiveInfo> &buildData,
            int start, int end, int *totalNodes,
            std::vector<std::shared_ptr<geometry::Primitive> > &orderedPrims) {
              (*totalNodes)++;
              BVHBuildNode *node = new BVHBuildNode();

              // compute bounds for all primitives in BVH node
              geometry::BBox bbox;
              for (int i = start; i < end; ++i) {
                bbox = bbox.combine(buildData[i].bounds);
              }

              int nPrimitives = end - start;
              if (nPrimitives == 1) {
                // create leaf BVHBuildNode
                int firstPrimOffset = orderedPrims.size();
                for (int i = start; i < end; ++i) {
                  int primNum = buildData[i].primitiveNumber;
                  orderedPrims.push_back(primitives[primNum]);
                }
                node->initLeaf(firstPrimOffset, nPrimitives, bbox);
              }
              else {
                // compute bound of primitive centroids, choose split dimension
                geometry::BBox centroidBounds;
                for (int i = start; i < end; ++i) {
                  centroidBounds = centroidBounds.combine(buildData[i].centroid);
                }
                int dim = centroidBounds.maximumExtent();
                int splitMethod = SPLIT_SAH;

                      // partition primitives into two sets and build children
                      int mid = (start + end)/2;
                      if (centroidBounds.max()[dim] == centroidBounds.min()[dim]) {
                        // create leaf bvhbuildnode
                        int firstPrimOffset = orderedPrims.size();
                        for (int i = start; i < end; ++i) {
                          int primNum = buildData[i].primitiveNumber;
                          orderedPrims.push_back(primitives[primNum]);
                        }
                        node->initLeaf(firstPrimOffset, nPrimitives, bbox);
                        return node;
                      }
                      switch(splitMethod) {
                        case SPLIT_MIDDLE: {
                      // partition primitives based on splitMethod

                       //partition through node's Midpoint
                      float pmid = 0.5 * (centroidBounds.min()[dim] + centroidBounds.max()[dim]);
                      BVHPrimitiveInfo *midPtr = std::partition(&buildData[start],
                                                                &buildData[end-1] + 1,
                                                                CompareToMid(dim, pmid));
                      mid = midPtr - &buildData[0];
                      break;
                  }
                  case SPLIT_SAH: default: {
                //////////////////////////////////////////////////////////////////////


                 // partition using approximate SAH
                if (nPrimitives <= 4) {
                  // partition primitives into equally-sized subsets
                  mid = (start + end)/2;
                  std::nth_element(&buildData[start], &buildData[mid],
                                   &buildData[end-1]+1, ComparePoints(dim));
                }
                else {
                  // allocate bucketinfo for SAH partition buckets
                  const int nBuckets = 12;
                  struct BucketInfo {
                    BucketInfo() { count = 0;}
                    int count;
                    geometry::BBox bounds;
                  };
                  BucketInfo buckets[nBuckets];

                  //init bucketinfo for SAH partition buckets
                  for (int i = start; i < end; ++i) {
                    int b = nBuckets *
                      ((buildData[i].centroid[dim] - centroidBounds.min()[dim])/
                      (centroidBounds.max()[dim] - centroidBounds.min()[dim]));
                      if (b == nBuckets) b = nBuckets - 1;
                      buckets[b].count++;
                      buckets[b].bounds = buckets[b].bounds.combine(buildData[i].bounds);
                  }

                  // compute costs for splitting after each bucket
                  float cost[nBuckets - 1];
                  for (int i =0; i < nBuckets - 1; ++i) {
                    geometry::BBox b0, b1;
                    int count0 = 0, count1 = 0;
                    for (int j = 0; j <= i; ++j) {
                      b0 = b0.combine(buckets[j].bounds);
                      count0 += buckets[j].count;
                    }
                    for (int j = i+1; j < nBuckets; ++j) {
                      b1 = b1.combine(buckets[j].bounds);
                      count1 += buckets[j].count;
                    }
                    cost[i] = 0.125f + (count0 *b0.surfaceArea() + count1 * b1.surfaceArea())/
                            bbox.surfaceArea();
                  }
                  // find bucket to split at that minimizes SAH metric
                  float minCost = cost[0];
                  int minCostSplit = 0;
                  for (int i = 1;i < nBuckets-1; ++i) {
                    if (cost[i] < minCost) {
                      minCost = cost[i];
                      minCostSplit = i;
                    }
                  }
                  // either create leaf or split primitives at selected SAH bucket
                  if (nPrimitives > maxPrimsInNodes ||
                      minCost < nPrimitives) {
                        BVHPrimitiveInfo *pmid = std::partition(&buildData[start],
                        &buildData[end - 1] + 1,
                        CompareToBucket(minCostSplit, nBuckets, dim, centroidBounds));
                        mid = pmid - &buildData[0];
                  }
                  else {
                    int firstPrimOffset = orderedPrims.size();
                    for (int i = start; i < end; ++i) {
                      int primNum = buildData[i].primitiveNumber;
                      orderedPrims.push_back(primitives[primNum]);
                    }
                    node->initLeaf(firstPrimOffset, nPrimitives, bbox);
                  }
                }
                //////////////////////////////////////////////////////////
                break;
              }
            }

            node->initInterior(dim,
                        recursiveBuild(buildData, start, mid, totalNodes, orderedPrims),
                        recursiveBuild(buildData,   mid, end, totalNodes, orderedPrims));
            }
            return node;


            }
    static inline bool IntersectP(const geometry::BBox &bounds, const Ray &ray,
        const math::Vector &invDir, const int dirIsNeg[3]) {
          //!FIXME!
          return true; // fix!
          // check for ray intersection against x and y slabs
          float txmin = (bounds[  dirIsNeg[0]].x() - ray.origin().x()) * invDir.x();

          float txmax = (bounds[1-dirIsNeg[0]].x() - ray.origin().x()) * invDir.x();

          float tymin = (bounds[  dirIsNeg[1]].y() - ray.origin().y()) * invDir.y();

          float tymax = (bounds[1-dirIsNeg[1]].y() - ray.origin().y()) * invDir.y();

          if ((txmin > tymax) || (tymin > txmax))
            return false;
          if (tymin > txmin) txmin = tymin;
          if (tymax < txmax) txmax = tymax;

          // check for ray intersection against z slab
          float tzmin = (bounds[  dirIsNeg[2]].z() - ray.origin().z()) * invDir.z();
          float tzmax = (bounds[1-dirIsNeg[2]].z() - ray.origin().z()) * invDir.z();


          if ((txmin > tzmax) || (tzmin > txmax))
            return false;
          if (tzmin > txmin) txmin = tzmin;
          if (tzmax < txmax) txmax = tzmax;

          return (txmin < ray.maxt()) && (txmax > ray.mint());
        }


    const bool BVHAccel::intersect(const Ray &ws_ray, float &hit_time,
                std::shared_ptr<geometry::DifferentialGeometry>  &dg,
                std::shared_ptr<geometry::Primitive> &prim) const {

        if (!mImpl->nodes) return false;
        bool hit = false;

        geometry::Point origin = ws_ray(ws_ray.mint());
        math::Vector invDir(1.f/ws_ray.dir().x(), 1.f/ws_ray.dir().y(), 1.f/ws_ray.dir().z());
        int dirIsNeg[3] = { invDir.x() < 0, invDir.y() < 0, invDir.z() < 0 };
        // follow ray through BVH nodes to find primitive intersections
        int todoOffset = 0, nodeNum = 0;
        int todo[64];

        while(true) {
          const LinearBVHNode *node = &mImpl->nodes[nodeNum];

          // check ray against BVH node
          if (IntersectP(node->bounds, ws_ray, invDir, dirIsNeg)) {
            if (node->nPrimitives > 0) {
              // Intersect ray with primitives in leaf BVH node
              for (int i = 0; i < node->nPrimitives; ++i) {
                if (mImpl->primitives[node->primitivesOffset+i]->hit(ws_ray, hit_time, dg)) {
                  prim = mImpl->primitives[node->primitivesOffset+i];
                  hit = true;
                }
              }
              if (todoOffset == 0) break;
              nodeNum = todo[--todoOffset];

            }
            else {
              //put far BVH on todo stack, advance to near node
              if (dirIsNeg[node->axis]) {
                todo[todoOffset++] = nodeNum + 1;
                nodeNum = node->secondChildOffset;
              }
              else {
                todo[todoOffset++] = node->secondChildOffset;
                nodeNum = nodeNum + 1;
              }
            }
          }
          else {
            if (todoOffset == 0) break;
            nodeNum = todo[--todoOffset];
          }

        }
        return hit;

    }

  }
}
