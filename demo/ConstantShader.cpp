#include "ConstantShader.h"
#include <gssmraytracer/utils/Color.h>
namespace gssmraytracer {
  namespace utils {
    class ConstantShader::Impl {
    public:
      Color color;
    };

    ConstantShader::ConstantShader(const Color &color) : mImpl(new Impl) {
      mImpl->color = color;
    }
    ConstantShader::ConstantShader(const ConstantShader &other) : Shader(), mImpl(new Impl) {
      mImpl->color = other.mImpl->color;

    }
    ConstantShader& ConstantShader::operator=(const ConstantShader &other) {
      if (this != &other) {
        mImpl->color = other.mImpl->color;
      }
      return *this;
    }
    Color ConstantShader::shade(const Imath::Vec3<float> &hitpoint,
                   const Imath::Vec3<float> &normal) {
                     return mImpl->color;
                   }
  }
}
