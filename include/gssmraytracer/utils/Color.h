#ifndef __COLOR_H__
#define __COLOR_H__

namespace gssmraytracer {
  namespace utils {
    class Color {
    public:
      //! Initializes a Color set to (0,0,0,0)
      Color();

      //! Sets the Color r,g,b,a
      Color(const float red,
            const float green,
            const float blue,
            const float alpha
           );

    float red;
    float green;
    float blue;
    float alpha;
  };
  }
}
#endif // __COLOR_H__
