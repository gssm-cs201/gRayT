#include <gssmraytracer/utils/Shader.h>
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class NoiseShader: public Shader {
    public:
      NoiseShader();
      NoiseShader& operator=(const NoiseShader &);
      Color shade(const geometry::DifferentialGeometry &dg, const int bounce_count = 0) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
