#include <grayt/utils/Shader.h>
#include <grayt/utils/Color.h>
#include <memory>

namespace grayt {
  namespace utils {
    class NormalShader: public Shader {
    public:
      NormalShader();
      NormalShader& operator=(const NormalShader &);
      Color shade(const Ray &view, const geometry::DifferentialGeometry &dg, const int bounce_count = 0) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
