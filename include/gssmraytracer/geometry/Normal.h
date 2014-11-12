#ifndef __NORMAL_H__
#define __NORMAL_H__
#include <memory>
#include "gssmraytracer/math/Vector.h"
namespace gssmraytracer {
  namespace geometry {
    class Normal {
    public:
      Normal();
      explicit Normal(const math::Vector &vec);
      Normal(const float x, const float y, const float z);
      Normal(const Normal &normal);
      Normal& operator=(const Normal &normal);
      void normalize();
      const Normal normalized() const;
      const float x() const;
      const float y() const;
      const float z() const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
    std::ostream& operator<<(std::ostream &os, const Normal &normal);
  }
}
#endif // __NORMAL_H__
