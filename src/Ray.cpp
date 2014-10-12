#include "gssmraytracer/utils/Ray.h"
#include <limits>

namespace gssmraytracer {
  namespace utils {
    class Ray::Impl {
    public:
      geometry::Point origin;
      math::Vector direction;
      double mint;
      double maxt;
    };

    Ray::Ray() : mImpl(new Impl) {}
    Ray::Ray(const geometry::Point &origin,
             const math::Vector &direction) : mImpl(new Impl) {
               mImpl->origin = origin;
               mImpl->direction = direction;
               mImpl->mint = 0;
               mImpl->maxt = std::numeric_limits<double>::infinity();
             }
    std::ostream& operator<<(std::ostream &os, const Ray &ray) {
      os << "(" << ray.origin() << ", " << ray.dir() << ")" << std::endl;
      return os;
    }
    const geometry::Point Ray::origin() const {
      return mImpl->origin;
    }
    const math::Vector Ray::dir() const {
      return mImpl->direction.normalized();
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
    const geometry::Point Ray::point(const float t) const {
      return  origin() + (dir() * t);
    }


  }
}
