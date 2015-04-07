#include <grayt/utils/Shader.h>
#include <grayt/utils/Color.h>
#include <memory>

namespace grayt {
  namespace utils {
    class ConstantShader: public Shader {
    public:
      ConstantShader(const Color &color);
      ConstantShader(const ConstantShader &);
      ConstantShader& operator=(const ConstantShader &);
      Color shade(const Ray &view, const geometry::DifferentialGeometry &dg, const int bounce_count = 0) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
