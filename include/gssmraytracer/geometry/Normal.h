#include <OpenEXR/ImathVec.h>
namespace gssmraytracer {
  namespace geometry {
    struct Normal {
      explicit Normal(const Imath::Vec3<float> &vec)
                      : x(vec.x), y(vec.y), z(vec.z) {}
      Normal(const float xx, const float xy, const float xz)
                      : x(xx), y(yy), z(zz) {}


    };
  }
}
