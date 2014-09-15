#ifndef __POINT_H__
#define __POINT_H__
namespace gssmraytracer {
  namespace geometry {
    class Point {
    public:
      Point();
      Point(const float x, const float y, const float z);
      Point(const Point &);
      Point& operator=(const Point &);

      float x;
      float y;
      float z;

    };
  }
}
#endif //__POINT_H__
