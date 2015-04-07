#include <grayt/utils/Shader.h>
#include <memory>

namespace grayt {
  namespace utils {
    class NoiseShader: public Shader {
    public:
      NoiseShader();
      NoiseShader& operator=(const NoiseShader &);
      Color shade(const Ray &view, const geometry::DifferentialGeometry &dg, const int bounce_count = 0) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
