#include "ConstantShader.h"
#include <gssmraytracer/utils/Color.h>

using namespace gssmraytracer::geometry;
namespace gssmraytracer {
  namespace utils {
    class ConstantShader::Impl {
    public:
      Impl() : color(0,0,0,0) {}
      Impl(const Color &c) : color(c) {}
      Color color;
    };

    ConstantShader::ConstantShader(const Color &color) : mImpl(new Impl(color)) {
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
    Color ConstantShader::shade(const geometry::DifferentialGeometry &dg) {
                     return mImpl->color;
                   }
  }
}
