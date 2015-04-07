#include <grayt/utils/Shader.h>
#include <grayt/utils/Color.h>
#include <memory>

namespace grayt {
  namespace utils {
    class PhongShader: public Shader {
    public:
      PhongShader(const Color &color);
      PhongShader(const PhongShader &);
      PhongShader& operator=(const PhongShader &);
      Color shade(const Ray &view, const geometry::DifferentialGeometry &dg, const int bounce_count = 0) const;


    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
