#ifndef __DIFFERENTIALGEOMETRY_H__
#define __DIFFERENTIALGEOMETRY_H__

#include <OpenEXR/ImathVec.h>
#include <memory>
#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/geometry/Shape.h"

namespace gssmraytracer {
  namespace geometry {
    struct DifferentialGeometry {
      DifferentialGeometry() : u(0.), v(0.), shape(NULL) {}
      DifferentialGeometry(
            const Point &P,
            const Imath::Vec3<float> &dpdu, const Imath::Vec3<float> &dpdv,
            const Imath::Vec3<float> &dndu, const Imath::Vec3<float> &dndv,
            const float u,
            const float v,
            const std::shared_ptr<Shape> sh);
      Point p;
      Imath::Vec3<float> nn;
      float u, v;
      Imath::Vec3<float> dpdu, dpdv;
      Imath::Vec3<float> dndu, dndv;
      const std::shared_ptr<Shape> shape;
    };
  }
}
#endif //__DIFFERENTIALGEOMETRY_H__
