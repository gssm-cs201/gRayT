#ifndef __POINT_H__
#define __POINT_H__
#include <memory>
namespace gssmraytracer {
  namespace geometry {
    class Point {
    public:
      Point();
      Point(const float x, const float y, const float z);
      Point(const Point &);
      Point& operator=(const Point &);
      const float x() const;
      const float y() const;
      const float z() const;
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
#endif //__POINT_H__
