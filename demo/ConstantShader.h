#include <gssmraytracer/utils/Shader.h>
#include <gssmraytracer/utils/Color.h>
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class ConstantShader: public Shader {
    public:
      ConstantShader(const Color &color);
      ConstantShader(const ConstantShader &);
      ConstantShader& operator=(const ConstantShader &);
      Color shade(const Imath::Vec3<float> &hitpoint,
                     const Imath::Vec3<float> &normal
                     );

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
