#ifndef __RAY_H__
#define __RAY_H__
#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/math/Vector.h"
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class Ray {
    public:
      Ray(); // default constructor
      Ray(const geometry::Point &origin, const math::Vector &direction);
      const geometry::Point origin() const;
      const math::Vector dir() const;
      const double mint();
      void setMint(const double);
      const double maxt();
      void setMaxt(const double);
      const geometry::Point operator()(const float t) const;
      friend std::ostream& operator<<(std::ostream &os, const Ray &ray);

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}
#endif // __RAY_H__
