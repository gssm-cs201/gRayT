#include "grayt/geometry/Normal.h"
#include <OpenEXR/ImathVec.h>

namespace grayt {
  namespace geometry {
    class Normal::Impl {
    public:
      Impl(): vec(0,0,0) {}
      Imath::Vec3<float> vec;

    };

    Normal::Normal() : mImpl(new Impl){}

    Normal::Normal(const math::Vector &vec) : mImpl(new Impl) {
      mImpl->vec.x = vec.x();
      mImpl->vec.y = vec.y();
      mImpl->vec.z = vec.z();
    }
    Normal::Normal(const float x, const float y, const float z): mImpl(new Impl) {
      mImpl->vec.x = x;
      mImpl->vec.y = y;
      mImpl->vec.z = z;
    }
    Normal::Normal(const Normal &normal) : mImpl(new Impl) {
      mImpl->vec = normal.mImpl->vec;
    }

    const Normal Normal::operator+(const Normal &normal) const {
      return Normal(x() + normal.x(), y() + normal.y(), z() + normal.z());

    }

    Normal& Normal::operator=(const Normal &normal)  {
      if (this != &normal) {
        mImpl->vec = normal.mImpl->vec;
      }
      return *this;
    }
    void Normal::normalize() { mImpl->vec.normalize();}

    const Normal Normal::normalized() const {
      Normal new_normal = *this;
      new_normal.normalize();
      return new_normal;

    }

    const float Normal::x() const { return mImpl->vec.x;}
    const float Normal::y() const { return mImpl->vec.y;}
    const float Normal::z() const { return mImpl->vec.z;}

    std::ostream& operator<<(std::ostream &os, const Normal &normal) {
      os << "(" << normal.x() << ", " << normal.y() << ", " << normal.z() << ")" << std::endl;
      return os;
    }

    const Normal operator*(const float s, const Normal &normal) {
      return Normal(s * normal.x(), s * normal.y(), s * normal.z());
    }

    const Normal operator*(const Normal &normal, const float s) {
      return s * normal;
    }

  }


}
