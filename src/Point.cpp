#include "gssmraytracer/geometry/Point.h"
namespace gssmraytracer {
  namespace geometry {

    Point::Point() : x(0), y(0), z(0) {}

    Point::Point(const float xx, const float yy, const float zz) :
      x(xx), y(yy), z(zz) {}

    Point::Point(const Point &p) : x(p.x), y(p.y), z(p.z) {}

    Point& Point::operator=(const Point &other) {
      if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
      }
      return *this;
    }

  }
}
