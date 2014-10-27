#include "gssmraytracer/utils/Ray.h"
#include <limits>

namespace gssmraytracer {
  namespace utils {
    class Ray::Impl {
    public:
      Impl() : origin(), direction(), mint(0),
          maxt(std::numeric_limits<float>::infinity()), epsilon(0.0f) {}
      geometry::Point origin;
      math::Vector direction;
      float mint;
      float maxt;
      float epsilon;
    };

    Ray::Ray() : mImpl(new Impl) {}
    Ray::Ray(const geometry::Point &origin,
             const math::Vector &direction) : mImpl(new Impl) {
               mImpl->origin = origin;
               mImpl->direction = direction;

             }
    //! copy constructor
    Ray& Ray::operator=(const Ray &other) {
      if (this != &other) {
        mImpl->origin = other.mImpl->origin;
        mImpl->direction =other.mImpl->direction;
        mImpl->mint = other.mImpl->mint;
        mImpl->maxt = other.mImpl->maxt;
        mImpl->epsilon = other.mImpl->epsilon;
      }
      return *this;
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

    const float Ray::mint() const {
      return mImpl->mint;
    }
    void Ray::setMint(const float mint) {
      mImpl->mint = mint;
    }
    const float Ray::maxt() const {
      return mImpl->maxt;
    }
    void Ray::setMaxt(const float maxt) {
      mImpl->maxt = maxt;
    }

    //! returns the ray epsilon value
    const float Ray::epsilon() const {
      return mImpl->epsilon;
    }

    //! sets the ray epsilon value
    void Ray::epsilon(const float epsilon) {
      mImpl->epsilon = epsilon;
    }
    const geometry::Point Ray::operator()(const float t) const {
      return  origin() + (dir() * (t-mImpl->epsilon));
    }


  }
}
