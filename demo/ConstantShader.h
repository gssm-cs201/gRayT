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
      Color shade(const geometry::Point &hitpoint,
                     const geometry::Normal &normal
                     );

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
