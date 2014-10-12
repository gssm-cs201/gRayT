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
      Vector operator*(const float s) const;
      Vector& operator*=(const float s);
      Vector cross(const Vector &other) const;
      const float dot(const Vector &other) const;
      const float length() const;
      const Vector direction() const;
      void normalize();
      const Vector normalized() const;
      friend std::ostream& operator<<(std::ostream &os, const Vector &vec);
      const float x() const;
      const float y() const;
      const float z() const;
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
    Vector operator*(const float s, const Vector &vec);
  }
}
#endif // __VECTOR_H__
