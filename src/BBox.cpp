#include <limits>
#include "grayt/geometry/Point.h"
#include "grayt/geometry/BBox.h"

namespace grayt {
  namespace geometry {
    class BBox::Impl {
    public:
      Impl(): pMin(Point(std::numeric_limits<float>::infinity(),
                         std::numeric_limits<float>::infinity(),
                         std::numeric_limits<float>::infinity())),
              pMax(Point(-std::numeric_limits<float>::infinity(),
                         -std::numeric_limits<float>::infinity(),
                         -std::numeric_limits<float>::infinity()))
              {}
      Point pMin;
      Point pMax;
    };
    BBox::BBox() : mImpl(new Impl){}

    BBox::BBox(const Point &p) : mImpl(new Impl) {
      mImpl->pMin = p;
      mImpl->pMax = p;
    }
    BBox::BBox(const BBox &b) : mImpl(new Impl) {
      mImpl->pMin = b.mImpl->pMin;
      mImpl->pMax = b.mImpl->pMax;
    }
    BBox::BBox(const Point &p1, const Point &p2) : mImpl(new Impl) {
      mImpl->pMin = Point(std::min(p1.x(), p2.x()), std::min(p1.y(), p2.y()), std::min(p1.z(), p2.z()));
      mImpl->pMax = Point(std::max(p1.x(), p2.x()), std::max(p1.y(), p2.y()), std::max(p1.z(), p2.z()));
    }
    const Point BBox::centroid() const {
      return (mImpl->pMin + mImpl->pMax)*0.5;

    }
    const int BBox::maximumExtent() const {
      math::Vector diag = mImpl->pMax - mImpl->pMin;
      if (diag.x() > diag.y() && diag.x() > diag.z())
        return 0;
      else if (diag.y() > diag.z())
        return 1;
      else
        return 2;
    }
    BBox& BBox::operator=(const BBox &other) {
      if (this != &other) {

        mImpl->pMin = other.mImpl->pMin;
        mImpl->pMax = other.mImpl->pMax;

      }
      return *this;
    }
    std::ostream& operator<<(std::ostream &os, const BBox &bbox) {
      os << "min = " << bbox.min() << " max = " << bbox.max();
      return os;
    }
    const Point BBox::min() const {
      return mImpl->pMin;
    }
    const Point BBox::max() const {
      return mImpl->pMax;
    }
    const BBox BBox::combine(const BBox &bbox) const {
      BBox ret;

      ret.mImpl->pMin.x(std::min(mImpl->pMin.x(), bbox.mImpl->pMin.x()));

      ret.mImpl->pMin.y(std::min(mImpl->pMin.y(), bbox.mImpl->pMin.y()));
      ret.mImpl->pMin.z(std::min(mImpl->pMin.z(), bbox.mImpl->pMin.z()));

      ret.mImpl->pMax.x(std::max(mImpl->pMax.x(), bbox.mImpl->pMax.x()));
      ret.mImpl->pMax.y(std::max(mImpl->pMax.y(), bbox.mImpl->pMax.y()));
      ret.mImpl->pMax.z(std::max(mImpl->pMax.z(), bbox.mImpl->pMax.z()));
    return ret;
    }
    const BBox BBox::combine(const Point &p) const {
      BBox ret;

      ret.mImpl->pMin.x(std::min(mImpl->pMin.x(), p.x()));

      ret.mImpl->pMin.y(std::min(mImpl->pMin.y(), p.y()));
      ret.mImpl->pMin.z(std::min(mImpl->pMin.z(), p.z()));

      ret.mImpl->pMax.x(std::max(mImpl->pMax.x(), p.x()));
      ret.mImpl->pMax.y(std::max(mImpl->pMax.y(), p.y()));
      ret.mImpl->pMax.z(std::max(mImpl->pMax.z(), p.z()));
    return ret;
    }
    const float BBox::surfaceArea() const {
      math::Vector d = mImpl->pMax - mImpl->pMin;
      return 2.f * (d.x()*d.y() + d.x()*d.z()+d.y()*d.z());

    }

    const geometry::Point& BBox::operator[](int i) const {
      if (i == 0) return mImpl->pMin;
      else return mImpl->pMax;
    }
    geometry::Point& BBox::operator[](int i) {
  if (i == 0) return mImpl->pMin;
      else return mImpl->pMax;

    }


    bool BBox::intersect(const utils::Ray &ray, float *hitt0, float *hitt1) const {

      float t0 = ray.mint(), t1 = ray.maxt();
      for (int i = 0; i < 3; ++i) {
        float invRayDir = 1.f/ray.dir()[i];
        float tNear = (mImpl->pMin[i] - ray.origin()[i]) * invRayDir;
        float tFar = (mImpl->pMax[i] - ray.origin()[i]) * invRayDir;
        if (tNear > tFar) std::swap(tNear, tFar);
        t0 = tNear > t0 ? tNear: t0;
        t1 = tFar < t1 ? tFar : t1;
        if (t0 > t1) return false;
      }
      if (hitt0) *hitt0 = t0;
      if (hitt1) *hitt1 = t1;
      return true;

    }
  }
}
