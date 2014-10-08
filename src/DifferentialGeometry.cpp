#include "gssmraytracer/geometry/DifferentialGeometry.h"

namespace gssmraytracer {
  namespace geometry {
    DifferentialGeometry::DifferentialGeometry(
          const Point &P,
          const Imath::Vec3<float> &DPDU, const Imath::Vec3<float> &DPDV,
          const Imath::Vec3<float> &DNDU, const Imath::Vec3<float> &DNDV,
          const float uu,
          const float vv,
          const std::shared_ptr<Shape> sh) : p(P), u(uu), v(vv), dpdu(DPDU), dpdv(DPDV), dndu(DNDU), dndv(DNDV),
                 shape(sh){

              nn = (dpdu.cross(dpdv)).normalize();

          }

  }
}
