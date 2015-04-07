#include "ImageShader.h"
#include <grayt/utils/Color.h>

using namespace grayt::geometry;
namespace grayt {
  namespace utils {
    class ImageShader::Impl {
    public:
      Impl() : image() {}
      Impl(const Image &img) : image(img) {}
      Image image;
    };


    ImageShader::ImageShader(const Image &image) : Shader(), mImpl(new Impl(image)){}

    Color ImageShader::shade(const Ray &view, const geometry::DifferentialGeometry &dg, const int bounce_count) const {
                     return mImpl->image.getPixel(floor(dg.u * mImpl->image.getHeight()), floor(dg.v * mImpl->image.getWidth()));
                   }
  }
}
