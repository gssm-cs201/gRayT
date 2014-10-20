#include <memory>
#include "gssmraytracer/math/Transform.h"
#include "gssmraytracer/utils/Color.h"
#include "gssmraytracer/geometry/DifferentialGeometry.h"

namespace gssmraytracer {
  namespace utils {
    class Light {
    public:
      Light(const math::Transform &l2w, int ns = 1);
      virtual const Color intensity(const geometry::DifferentialGeometry &) const = 0;

      const math::Transform lightToWorldSpace() const;
      const math::Transform worldToLightSpace() const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}
