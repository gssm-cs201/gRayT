#include "gssmraytracer/geometry/DifferentialGeometry.h"

namespace gssmraytracer {
  namespace geometry {
    DifferentialGeometry::DifferentialGeometry(
          const Point &P,
          const math::Vector &DPDU, const math::Vector &DPDV,
          const Normal &DNDU, const Normal &DNDV,
          const float uu,
          const float vv,
          const utils::Ray &vview,
          const Shape *sh) : p(P), nn(0.,1.,0.), u(uu), v(vv), dpdu(DPDU), dpdv(DPDV), view(vview), dndu(DNDU), dndv(DNDV),
                 shape(sh){

              nn = Normal(dpdu.cross(dpdv)).normalized();

          }
          DifferentialGeometry::DifferentialGeometry(
                                            const DifferentialGeometry &dg) :
            p(dg.p), nn(dg.nn), u(dg.u), v(dg.v), dpdu(dg.dpdu), dpdv(dg.dpdv),
            view(dg.view), dndu(dg.dndu), dndv(dg.dndv), shape(dg.shape) {}



  }
}
