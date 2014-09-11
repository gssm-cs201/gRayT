#include "gssmraytracer/utils/Ray.h"
#include <limits>

namespace gssmraytracer {
  namespace utils {
    class Ray::Impl {
    public:
      Imath::Vec3<float> origin;
      Imath::Vec3<float> direction;
      double mint;
      double maxt;
    };

    Ray::Ray() : mImpl(new Impl) {}
    Ray::Ray(const Imath::Vec3<float> &origin,
             const Imath::Vec3<float> &direction) : mImpl(new Impl) {
               mImpl->origin = origin;
               mImpl->direction = direction;
               mImpl->mint = 0;
               mImpl->maxt = std::numeric_limits<double>::infinity();
             }

    const Imath::Vec3<float> Ray::origin() {
      return mImpl->origin;
    }
    const Imath::Vec3<float> Ray::dir() {
      return mImpl->direction.normalize();
    }

    const double Ray::mint() {
      return mImpl->mint;
    }
    void Ray::setMint(const double mint) {
      mImpl->mint = mint;
    }
    const double Ray::maxt() {
      return mImpl->maxt;
    }
    void Ray::setMaxt(const double maxt) {
      mImpl->maxt = maxt;
    }
  }
}
