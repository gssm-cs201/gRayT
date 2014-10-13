#include <gssmraytracer/utils/Shader.h>
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Image.h>
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class ImageShader: public Shader {
    public:
      ImageShader(const Image &image);
      ImageShader& operator=(const ImageShader &);
      Color shade(const geometry::DifferentialGeometry &dg);

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
