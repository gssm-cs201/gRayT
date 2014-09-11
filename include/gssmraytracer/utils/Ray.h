#include <OpenEXR/ImathVec.h>
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class Ray {
    public:
      Ray(); // default constructor
      Ray(const Imath::Vec3<float> &origin, const Imath::Vec3<float> &direction);
      const Imath::Vec3<float> origin();
      const Imath::Vec3<float> dir();
      const double mint();
      void setMint(const double);
      const double maxt();
      void setMaxt(const double);
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}
