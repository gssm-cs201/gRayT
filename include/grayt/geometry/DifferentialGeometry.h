#ifndef __DIFFERENTIALGEOMETRY_H__
#define __DIFFERENTIALGEOMETRY_H__

#include "grayt/math/Vector.h"
#include "grayt/geometry/Normal.h"
#include <memory>
#include "grayt/geometry/Point.h"
#include "grayt/utils/Ray.h"
namespace grayt {
  namespace geometry {
    class Shape;
    struct DifferentialGeometry {
      /*! \brief Object for holding information for shading
       *
       * P is the hit point,
       * dpdu, and dpdv are the partial derivatives along u and v
       * dndu and dndv are the partial derivatives of the Normal
       * u and v are the u v coordinates
       * sh holds a pointer to a shape
       */
      DifferentialGeometry(
            const Point &P,
            const math::Vector &dpdu, const math::Vector &dpdv,
            const Normal &dndu, const Normal &dndv,
            const float u,
            const float v,
            const Shape *sh
      );

      //! Copy constructor.  Performs shallow copy of *sh
      DifferentialGeometry(const DifferentialGeometry &dg);
      Point p;
      Normal nn;
      float u, v;
      math::Vector dpdu, dpdv;
      Normal dndu, dndv;
      const Shape *shape;
    private:
      //! Assignment operator forbidden.
      DifferentialGeometry& operator=(const DifferentialGeometry dg);
    };
  }
}
#endif //__DIFFERENTIALGEOMETRY_H__
