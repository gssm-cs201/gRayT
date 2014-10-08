#include "gssmraytracer/geometry/Normal.h"

namespace gssmraytracer {
  namespace geometry {
    class Normal::Impl {
    public:
      Imath::Vec3<float> vec;

    };

    Normal::Normal(const Imath::Vec3<float> &vec) : mImpl(new Impl) {
      mImpl->vec = vec;
    }
    Normal::Normal(const float x, const float y, const float z): mImpl(new Impl) {
      mImpl->vec.x = x;
      mImpl->vec.y = y;
      mImpl->vec.z = z;
    }

    const float Normal::x() const { return mImpl->vec.x;}
    const float Normal::y() const { return mImpl->vec.y;}
    const float Normal::z() const { return mImpl->vec.z;}


  }


}
