#include "grayt/utils/Color.h"
#include "grayt/utils/Light.h"
namespace grayt {
  namespace utils {
    class PointLight: public Light {
    public:
      PointLight(const math::Transform &light2world, const Color &color, const float intensity);
      const Color intensity(const geometry::DifferentialGeometry &dg) const;
      const geometry::Point position() const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}
