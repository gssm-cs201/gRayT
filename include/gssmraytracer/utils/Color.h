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

    Color& operator=(const Color &color);

    //! scale a color by a scalar
    const Color operator*(const float s) const;

    Color& operator*=(const float s);

    //! multiply two colors together
    const Color operator*(const Color &c) const;

    //! add two colors together
    const Color operator+(const Color &c) const;

    Color& operator+=(const Color &c);

    float red;
    float green;
    float blue;
    float alpha;
  };

  //! scale a color by a scalar
//  const Color operator*(const float s, const Color &color);
  }
}
#endif // __COLOR_H__
