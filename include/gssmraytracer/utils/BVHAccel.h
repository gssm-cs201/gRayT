#ifndef __BVHACCEL_H__
#define __BVHACCEL_H__
#include "gssmraytracer/geometry/Primitive.h"
#include <memory>
#include <vector>

namespace gssmraytracer {
  namespace utils {
    class BVHAccel {
    public:
      BVHAccel(const std::vector<std::shared_ptr<geometry::Primitive> > &prims, const int maxPrimsInLeafNode);

      const bool intersect(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg,
        std::shared_ptr<geometry::Primitive> &prim) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };

  }
}
#endif // __BVHACCEL_H__
