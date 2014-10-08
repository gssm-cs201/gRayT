#include <OpenEXR/ImathVec.h>
#include <memory>

namespace gssmraytracer {
  namespace geometry {
    class Normal {
    public:
      explicit Normal(const Imath::Vec3<float> &vec);
      Normal(const float x, const float y, const float z);
      const float x() const;
      const float y() const;
      const float z() const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
