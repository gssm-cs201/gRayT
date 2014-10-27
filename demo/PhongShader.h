#include <gssmraytracer/utils/Shader.h>
#include <gssmraytracer/utils/Color.h>
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class PhongShader: public Shader {
    public:
      PhongShader(const Color &color);
      PhongShader(const PhongShader &);
      PhongShader& operator=(const PhongShader &);
      Color shade(const geometry::DifferentialGeometry &dg);

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
