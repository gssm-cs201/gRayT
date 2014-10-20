#ifndef __BBOX_H__
#define __BBOX_H__
#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/utils/Ray.h"
#include  <memory>

namespace gssmraytracer {
  namespace geometry {
    class Point; // forward declaration
    class BBox {
    public:
      BBox();
      BBox(const Point &p);
      BBox(const Point &p1, const Point &p2);
      BBox& operator=(const BBox &other);
      const Point min() const;
      const Point max() const;
      bool intersect(const utils::Ray &ray, float *hitt0=nullptr, float *hitt1=nullptr) const;
      const BBox combine(const BBox &bbox) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}
#endif // __BBOX_H__
