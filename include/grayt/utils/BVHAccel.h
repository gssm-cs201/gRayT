#ifndef __BVHACCEL_H__
#define __BVHACCEL_H__
#include "grayt/geometry/Primitive.h"
#include <memory>
#include <vector>


namespace grayt {
  namespace utils {
    class BVHAccel {
    public:
      //! BVHAccel takes a vector of primitive smart pointers and the maximum
      //! number of primitives in a leaf node
      BVHAccel(const std::vector<std::shared_ptr<geometry::Primitive> > &prims, const uint32_t maxPrimsInLeafNode);
      ~BVHAccel();

      const bool intersect(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg,
        std::shared_ptr<geometry::Primitive> &prim) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };

  }
}
#endif // __BVHACCEL_H__
