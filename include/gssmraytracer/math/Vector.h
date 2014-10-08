#ifndef __VECTOR_H__
#define __VECTOR_H__
#include <memory>

namespace gssmraytracer {
  namespace math {
    class Vector {
    public:
      Vector();
      Vector(const float x, const float y, const float z);
      Vector(const Vector &vector);
      Vector& operator=(const Vector &other);
      Vector operator+(const Vector &v) const;
      Vector& operator+=(const Vector &v);
      Vector operator-(const Vector &v) const;
      Vector& operator-=(const Vector &v);
      Vector cross(const Vector &other) const;
      const float dot(const Vector &other) const;
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}
#endif // __VECTOR_H__
