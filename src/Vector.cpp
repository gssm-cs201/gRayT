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
    Vector Vector::cross(const Vector &other) const {
      Vector newVector;
      newVector.mImpl->vec = mImpl->vec.cross(other.mImpl->vec);
      return newVector;

    }
    const float Vector::dot(const Vector &other) const {
      return mImpl->vec.dot(other.mImpl->vec);
    }

  }
}
