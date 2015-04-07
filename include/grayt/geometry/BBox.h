#ifndef __BBOX_H__
#define __BBOX_H__
#include "grayt/geometry/Point.h"
#include "grayt/utils/Ray.h"
#include  <memory>

namespace grayt {
  namespace geometry {
    class BBox {
    public:
      BBox();
      explicit BBox(const Point &p);
      BBox(const BBox &b);
      BBox(const Point &p1, const Point &p2);
      BBox& operator=(const BBox &other);
      const Point min() const;
      const Point max() const;
      const Point centroid() const;
      bool intersect(const utils::Ray &ray, float *hitt0=nullptr, float *hitt1=nullptr) const;
      const BBox combine(const BBox &bbox) const;
      const BBox combine(const Point &point) const;
      const float surfaceArea() const;
      const int maximumExtent() const;
      const geometry::Point &operator[](int i) const;
      geometry::Point &operator[](int i);


    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
    std::ostream& operator<<(std::ostream &os, const BBox &bbox);
  }
}
#endif // __BBOX_H__
