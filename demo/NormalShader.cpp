#include "NormalShader.h"
#include <gssmraytracer/utils/Color.h>

using namespace gssmraytracer::geometry;
namespace gssmraytracer {
  namespace utils {

    class NormalShader::Impl {

    };


    NormalShader::NormalShader() : Shader(), mImpl(new Impl) {}

    Color NormalShader::shade(const geometry::DifferentialGeometry &dg) {
                     return Color(dg.nn.x(), dg.nn.y(), dg.nn.z(), 1);
                   }
  }
}
