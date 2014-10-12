#include "gssmraytracer/math/Vector.h"
#include <OpenEXR/ImathVec.h>
namespace gssmraytracer {
  namespace math {
    class Vector::Impl {
    public:
      Imath::Vec3<float> vec;
    };

    Vector::Vector() : mImpl(new Impl) {}

    Vector::Vector(const float x, const float y, const float z) : mImpl(new Impl) {
      mImpl->vec.x = x;
      mImpl->vec.y = y;
      mImpl->vec.z = z;
    }

    Vector Vector::operator+(const Vector &v) const {
      Vector newVector;
      newVector.mImpl->vec = mImpl->vec + v.mImpl->vec;
      return newVector;
    }
    Vector& Vector::operator=(const Vector &other) {
      if (this != &other) {
        mImpl->vec = other.mImpl->vec;
      }
      return *this;
    }
    std::ostream& operator<<(std::ostream &os, const Vector &vec) {
      os << "(" << vec.mImpl->vec << ")" << std::endl;
      return os;
    }
    Vector& Vector::operator+=(const Vector &other) {
      if (this != &other) {
        mImpl->vec += other.mImpl->vec;
      }
      return *this;
    }
    Vector Vector::operator-(const Vector &v) const {
      Vector newVector;
      newVector.mImpl->vec = mImpl->vec - v.mImpl->vec;
      return newVector;
    }

    Vector& Vector::operator-=(const Vector &other) {
      if (this != &other) {
        mImpl->vec -= other.mImpl->vec;
      }
      return *this;
    }
    Vector Vector::operator*(const float s) const {
      return Vector(mImpl->vec.x * s, mImpl->vec.y * s, mImpl->vec.z * s);
    }
    Vector operator*(const float s, const Vector &vec) {
      return vec * s;
    }
    Vector& Vector::operator*=(const float s) {
      mImpl->vec *= s;
      return *this;

    }
    Vector Vector::cross(const Vector &other) const {
      Vector newVector;
      newVector.mImpl->vec = mImpl->vec.cross(other.mImpl->vec);
      return newVector;

    }
    const float Vector::dot(const Vector &other) const {
      return mImpl->vec.dot(other.mImpl->vec);
    }
    const float Vector::length() const {return mImpl->vec.length();}
    const Vector Vector::direction() const { Imath::Vec3<float> temp = mImpl->vec.normalized();
                                              return Vector(temp.x, temp.y, temp.z);}


    const float Vector::x() const { return mImpl->vec.x;}
    const float Vector::y() const { return mImpl->vec.y;}
    const float Vector::z() const { return mImpl->vec.z;}

    void Vector::normalize() { mImpl->vec.normalize();}
    const Vector Vector::normalized() const {
      Vector temp;
      temp.mImpl->vec = mImpl->vec;
      temp.mImpl->vec.normalize();
      return temp;}
  }
}
