#include <grayt/utils/Shader.h>
#include <grayt/utils/Color.h>
#include <grayt/utils/Image.h>
#include <memory>

namespace grayt {
  namespace utils {
    class ImageShader: public Shader {
    public:
      ImageShader(const Image &image);
      ImageShader& operator=(const ImageShader &);
      Color shade(const Ray &view, const geometry::DifferentialGeometry &dg, const int bounce_count = 0) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
