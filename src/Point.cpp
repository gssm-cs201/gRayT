#include "gssmraytracer/geometry/Point.h"
namespace gssmraytracer {
  namespace geometry {
    class Point::Impl {
    public:
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
    Point::Point(const math::Vector &vec) {
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

    const math::Vector Point::operator-(const Point &other) const {
      return math::Vector(x() - other.x(), y() - other.y(), z() - other.z());
    }

    std::ostream& operator<<(std::ostream &os, const Point &point) {
      os << "(" << point.mImpl->vec << ")" << std::endl;
      return os;
    }

    const float Point::operator[](const float index) const {
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
