#include "gssmraytracer/utils/Light.h"
namespace gssmraytracer {
  namespace utils {
    class Light::Impl {
    public:
      math::Transform transform;
      math::Transform invTransform;
      int numSamples;
    };

    Light::Light(const math::Transform &l2w, const int ns) : mImpl(new Impl) {
      mImpl->transform = l2w;
      mImpl->invTransform = l2w.inverse();
      mImpl->numSamples = ns;
    }

    const math::Transform Light::lightToWorldSpace() const {
      return mImpl->transform;
    }

    const math::Transform Light::worldToLightSpace() const {
      return mImpl->invTransform;
    }
  }
}
