#ifndef __RAY_H__
#define __RAY_H__
#include <OpenEXR/ImathVec.h>
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class Ray {
    public:
      Ray(); // default constructor
      Ray(const Imath::Vec3<float> &origin, const Imath::Vec3<float> &direction);
      const Imath::Vec3<float> origin() const;
      const Imath::Vec3<float> dir() const;
      const double mint();
      void setMint(const double);
      const double maxt();
      void setMaxt(const double);
      friend std::ostream& operator<<(std::ostream &os, const Ray &ray);
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}
#endif // __RAY_H__
