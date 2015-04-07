#include "grayt/utils/PointLight.h"
using namespace grayt::math;
using namespace grayt::geometry;
namespace grayt {
  namespace utils {
    class PointLight::Impl {
    public:
      Color color;
      float intensity;
    };
    PointLight::PointLight(const Transform &light2world, const Color &color, const float intensity): Light(light2world), mImpl(new Impl) {
      mImpl->color = color;
      mImpl->intensity = intensity;
    }

    const Color PointLight::intensity(const DifferentialGeometry &dg) const {
      Point lightPos(0,0,0);
      lightPos = lightToWorldSpace()(lightPos);
      Vector uLS = (dg.p - lightPos).normalized();
      Color color = mImpl->color * (-uLS.dot(dg.nn));

      return color;
    }

    const Point PointLight::position() const {
      return lightToWorldSpace()(Point(0,0,0));
    }

  }
}
