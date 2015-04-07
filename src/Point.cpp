#include "grayt/geometry/Point.h"
namespace grayt {
  namespace geometry {
    class Point::Impl {
    public:
      Impl(): vec(0.f,0.f,0.f) {}
      Imath::Vec3<float> vec;
    };

    Point::Point() : mImpl(new Impl) {}

    Point::Point(const float x, const float y, const float z) :
      mImpl(new Impl) {
        mImpl->vec.x = x;
        mImpl->vec.y = y;
        mImpl->vec.z = z;
      }
    Point::Point(const Imath::Vec3<float> &vec) : mImpl(new Impl) {
      mImpl->vec = vec;
    }

    Point::Point(const Point &p) : mImpl(new Impl) {
      mImpl->vec = p.mImpl->vec;
    }
    Point::Point(const math::Vector &vec): mImpl(new Impl) {
      mImpl->vec = Imath::Vec3<float>(vec.x(),vec.y(),vec.z());

    }

    Point& Point::operator=(const Point &other) {
      if (this != &other) {
        mImpl->vec = other.mImpl->vec;
      }
      return *this;
    }
    Point Point::operator+(const math::Vector &vec) const {
      return Point(vec.x() + mImpl->vec.x, vec.y() + mImpl->vec.y, vec.z() + mImpl->vec.z);
    }

    Point Point::operator+(const geometry::Point &other) const {
      return Point(x() + other.x(), y() + other.y(), z() + other.z());

    }

    const math::Vector Point::operator-(const Point &other) const {
      return math::Vector(x() - other.x(), y() - other.y(), z() - other.z());
    }

    Point Point::operator*(const float s) const {
      return Point(x() *s, y() * s, z() *s);
    }
    Point operator*(const float s, const Point &p) {
      return Point(p.x() *s, p.y() * s, p.z() *s);
    }

    std::ostream& operator<<(std::ostream &os, const Point &point) {
      os << "(" << point.mImpl->vec << ")";
      return os;
    }

    const float Point::operator[](const float index) const {
      return mImpl->vec[index];
    }

    float& Point::operator[](const float index) {
      return mImpl->vec[index];
    }
    const float Point::x() const {
      return mImpl->vec.x;
    }
    const float Point::y() const {
      return mImpl->vec.y;
    }
    const float Point::z() const {
      return mImpl->vec.z;
    }
    void Point::x(float xx) {
      mImpl->vec.x = xx;
    }
    void Point::y(float yy) {
      mImpl->vec.y = yy;
    }
    void Point::z(float zz) {
      mImpl->vec.z = zz;
    }

  }
}
