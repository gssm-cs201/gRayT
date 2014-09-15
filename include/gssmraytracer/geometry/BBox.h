#include "gssmraytracer/geometry/Point.h"
#include  <memory>

namespace gssmraytracer {
  namespace geometry {
    class Point; // forward declaration
    class BBox {
    public:
      BBox();
      BBox(const Point &p);
      BBox(const Point &p1, const Point &p2);

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}
