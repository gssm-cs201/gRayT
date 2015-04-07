#include <memory>
#include "grayt/math/Transform.h"
#include "grayt/utils/Color.h"
#include "grayt/geometry/DifferentialGeometry.h"

namespace grayt {
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
