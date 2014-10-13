#ifndef __DIFFERENTIALGEOMETRY_H__
#define __DIFFERENTIALGEOMETRY_H__

#include "gssmraytracer/math/Vector.h"
#include "gssmraytracer/geometry/Normal.h"
#include <memory>
#include "gssmraytracer/geometry/Point.h"
namespace gssmraytracer {
  namespace geometry {
    class Shape;
    struct DifferentialGeometry {

      DifferentialGeometry(
            const Point &P,
            const math::Vector &dpdu, const math::Vector &dpdv,
            const Normal &dndu, const Normal &dndv,
            const float u,
            const float v,
            const Shape *sh
      );
      DifferentialGeometry(const DifferentialGeometry &dg);
      Point p;
      Normal nn;
      float u, v;
      math::Vector dpdu, dpdv;
      Normal dndu, dndv;
      const Shape *shape;
    private:
      DifferentialGeometry& operator=(const DifferentialGeometry dg); 
    };
  }
}
#endif //__DIFFERENTIALGEOMETRY_H__
