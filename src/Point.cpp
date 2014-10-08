#include "gssmraytracer/geometry/Point.h"
#include <OpenEXR/ImathVec.h>
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

    Point::Point(const Point &p) : mImpl(new Impl) {
      mImpl->vec = p.mImpl->vec;
    }

    Point& Point::operator=(const Point &other) {
      if (this != &other) {
        mImpl->vec = other.mImpl->vec;
      }
      return *this;
    }

  }
}
