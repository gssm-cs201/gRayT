#ifndef __DIFFERENTIALGEOMETRY_H__
#define __DIFFERENTIALGEOMETRY_H__

#include "gssmraytracer/math/Vector.h"
#include "gssmraytracer/geometry/Normal.h"
#include <memory>
#include "gssmraytracer/geometry/Point.h"

namespace gssmraytracer {
  namespace geometry {
    struct DifferentialGeometry {
      class Shape;
      DifferentialGeometry() : p(), nn(0.,1.,0.), u(0.), v(0.), dpdu(),
                                dpdv(), dndu(0.,1.,0.), dndv(0.,1.,0.), shape(NULL) {}
      DifferentialGeometry(
            const Point &P,
            const math::Vector &dpdu, const math::Vector &dpdv,
            const Normal &dndu, const Normal &dndv,
            const float u,
            const float v,
            const std::shared_ptr<Shape> sh
      );
      DifferentialGeometry(const DifferentialGeometry &dg);
      Point p;
      Normal nn;
      float u, v;
      math::Vector dpdu, dpdv;
      Normal dndu, dndv;
      const std::shared_ptr<Shape> shape;
    };
  }
}
#endif //__DIFFERENTIALGEOMETRY_H__
