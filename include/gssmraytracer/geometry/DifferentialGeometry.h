#ifndef __DIFFERENTIALGEOMETRY_H__
#define __DIFFERENTIALGEOMETRY_H__

#include <OpenEXR/ImathVec.h>
#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/geometry/Normal.h"
#include "gssmraytracer/utils/Shape.h"

namespace gssmraytracer {
  namespace geometry {
    struct DifferentialGeometry {
      DifferentialGeometry() : u(0.), v(0.), shape(NULL) {}
      Point p;
      Imath::Vec3<float> nn;
      float u, v;
      const Shape *shape;
      Imath::Vec3<float> dpdu, dpdv;
      Imath::Vec3<float> dndu, dndv;
    };
  }
}
#endif //__DIFFERENTIALGEOMETRY_H__
