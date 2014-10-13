#include <gssmraytracer/utils/Shader.h>
#include <gssmraytracer/utils/Color.h>
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class NormalShader: public Shader {
    public:
      NormalShader();
      NormalShader& operator=(const NormalShader &);
      Color shade(const geometry::DifferentialGeometry &dg);

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
