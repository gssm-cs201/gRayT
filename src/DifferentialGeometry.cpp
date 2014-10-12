#include "gssmraytracer/geometry/DifferentialGeometry.h"

namespace gssmraytracer {
  namespace geometry {
    DifferentialGeometry::DifferentialGeometry(
          const Point &P,
          const math::Vector &DPDU, const math::Vector &DPDV,
          const Normal &DNDU, const Normal &DNDV,
          const float uu,
          const float vv,
          const std::shared_ptr<Shape> sh) : p(P), nn(0.,1.,0.), u(uu), v(vv), dpdu(DPDU), dpdv(DPDV), dndu(DNDU), dndv(DNDV),
                 shape(sh){

              nn = Normal(dpdu.cross(dpdv)).normalized();

          }

  }
}
