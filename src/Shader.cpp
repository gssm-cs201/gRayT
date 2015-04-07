#include "grayt/utils/Shader.h"
#include "grayt/geometry/Point.h"
#include "grayt/utils/Scene.h"

#include "grayt/utils/Color.h"

namespace grayt {
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
