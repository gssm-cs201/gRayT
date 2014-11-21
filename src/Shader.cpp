#include "gssmraytracer/utils/Shader.h"
#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/utils/Scene.h"

#include "gssmraytracer/utils/Color.h"

namespace gssmraytracer {
  namespace utils {
    class Shader::Impl {
    public:
      Impl() : reflectivity(0) {}
      float reflectivity;
    };
    Shader::Shader() : mImpl(new Impl) {}
    const float Shader::reflectivity() const {
      return mImpl->reflectivity;

    }
    void Shader::reflectivity(const float reflectivity) {
      mImpl->reflectivity = reflectivity;

    }
  }
}
