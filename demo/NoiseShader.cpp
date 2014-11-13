#include "NoiseShader.h"
#include <gssmraytracer/noise/PerlinNoise.h>
#include <gssmraytracer/utils/gssmraytracer.h>
#include <gssmraytracer/utils/Scene.h>


using namespace gssmraytracer::geometry;
using namespace gssmraytracer::noise;
namespace gssmraytracer {
  namespace utils {
	class NoiseShader::Impl {
	public:
    Impl() : noise() {}
    Impl(const PerlinNoise &n) : noise(n) {}
	 PerlinNoise noise;
	};


    NoiseShader::NoiseShader() : Shader(), mImpl(new Impl) {
    }

    Color NoiseShader::shade(const geometry::DifferentialGeometry &dg) {

		     return Color(Clamp(fabs(mImpl->noise.eval(dg.p.x())), 0., 1.), Clamp(mImpl->noise.eval(dg.p.y()), 0., 1.), Clamp(mImpl->noise.eval(dg.p.z()), 0., 1.), 1.f);

                   }
  }
}
