#include <limits>
#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/geometry/BBox.h"
namespace gssmraytracer {
  namespace geometry {
    class BBox::Impl {
    public:
      Point pMin;
      Point pMax;
    };
    BBox::BBox() : mImpl(new Impl){
      mImpl->pMin = Point(std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity());
      mImpl->pMax = Point(-std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity());
    }

    BBox::BBox(const Point &p) : mImpl(new Impl) {
      mImpl->pMin = p;
      mImpl->pMax = p;
    }
    BBox::BBox(const Point &p1, const Point &p2) : mImpl(new Impl) {
      mImpl->pMin = Point(std::min(p1.x(), p2.x()), std::min(p1.y(), p2.y()), std::min(p1.z(), p2.z()));
      mImpl->pMax = Point(std::max(p1.x(), p2.x()), std::max(p1.y(), p2.y()), std::max(p1.z(), p2.z()));
    }
  }
}
