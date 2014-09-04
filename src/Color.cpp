#include "gssmraytracer/utils/Color.h"

namespace gssmraytracer {
  namespace utils {
    Color::Color() : red(0), green(0), blue(0), alpha(0) {}
    Color::Color(const float r,const float g,const float b,const float a) :
                red(r), green(g), blue(b), alpha(a)
                {}
  }
}
