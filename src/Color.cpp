#include "grayt/utils/Color.h"

namespace grayt {
  namespace utils {
    Color::Color() : red(0), green(0), blue(0), alpha(0) {}
    Color::Color(const float r,const float g,const float b,const float a) :
                red(r), green(g), blue(b), alpha(a)
                {}

    Color& Color::operator=(const Color &color) {
      if (this != &color) {
        red = color.red;
        green = color.green;
        blue = color.blue;
        alpha = color.alpha;
      }

      return *this;
    }

    const Color Color::operator+(const Color &c) const {
      return Color(red + c.red, green + c.green, blue + c.blue, alpha + c.alpha);
    }

    Color& Color::operator+=(const Color &c) {
      red = red + c.red;
      green = green + c.green;
      blue = blue + c.blue;
      alpha = alpha + c.alpha;
      return *this;
    }

    const Color Color::operator*(const float s) const {
      return Color(red * s, green * s, blue * s, alpha);
    }
    Color& Color::operator*=(const float s) {
      red *= s;
      green *=s;
      blue *=s;
      return *this;
    }
    const Color Color::operator*(const Color &c) const {
      return Color(red * c.red, green * c.green, blue * c.blue, alpha * c.alpha);
    }

    const Color operator*(const float s, const Color &color) {
      return color * s;
    }
  }
}
