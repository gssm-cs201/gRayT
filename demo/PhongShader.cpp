#include "PhongShader.h"
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Scene.h>

using namespace gssmraytracer::geometry;
namespace gssmraytracer {
  namespace utils {
    class PhongShader::Impl {
    public:
      Color color;
    };

    PhongShader::PhongShader(const Color &color) : mImpl(new Impl) {
      mImpl->color = color;
    }
    PhongShader::PhongShader(const PhongShader &other) :
                                            Shader(),
                                            mImpl(new Impl) {
      mImpl->color = other.mImpl->color;
    }

    PhongShader& PhongShader::operator=(const PhongShader &other) {
      if (this != &other) {
        mImpl->color = other.mImpl->color;
      }
      return *this;
    }
    Color PhongShader::shade(const geometry::DifferentialGeometry &dg) {

      // initialize the return color for the shader to black
      Color shadeColor(0,0,0,1);

      /************************************************************************/
      // hardcoded light info in the shader
      // this implementation should be done in the light object
      Point light_pos(0,10, 0);
      float intensity = 1.f;

      math::Vector light_vec = light_pos - dg.p;

      // no light falloff based on distance
      float distanceVal_no_falloff = 1.0f;

      // linear light falloff based on distance
//      float distanceVal_linear = (light_vec.length());

      // quadratic light falloff based on distance
//      float distanceVal_quadratic = (light_vec.length() * light_vec.length());

      Ray light_ray(dg.p, light_vec.normalized());
      /************************************************************************/


      // ambient lighting - faking global illumination with constant
      // low color value
      shadeColor.red = mImpl->color.red * 0.1f;
      shadeColor.green = mImpl->color.green * 0.1f;
      shadeColor.blue = mImpl->color.blue * 0.1f;

      // This implementation uses the singleton of the scene to see if we
      // hit any objects.  Note that we do not need to pass in the Scene as
      // an argument since a singleton is in the global namespace,
      // essentially, a global class where there is only one instance)
      if (!Scene::getInstance().hit(light_ray)) { // if no objects in the way, do lighting

        // this computes the cosine of the angle between the light vector
        // and the geometry normal
        float shadeAngle = light_vec.normalized().dot(dg.nn);
          // if the angle is greater than 0, do the lambertian shading

          if (shadeAngle > 0) {
            // add the diffuse (matte) lighting to the ambient lighting based on
            // the intensity and the falloff factor based on the distance
            float factor = shadeAngle*intensity/distanceVal_no_falloff;
            shadeColor.red += mImpl->color.red*factor;
            shadeColor.green += mImpl->color.green*factor;
            shadeColor.blue += mImpl->color.blue*factor;

            // specular
            // ...
            math::Vector R = light_vec.normalized() - 2*shadeAngle*math::Vector(dg.nn.x(), dg.nn.y(), dg.nn.z());
            R.normalize();

            float spec = pow(R.dot(dg.view.dir()), 400);
            shadeColor.red += spec;
            shadeColor.green += spec;
            shadeColor.blue += spec;

          }
      }

       return shadeColor;
    }
  }
}
