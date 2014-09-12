#include "gssmraytracer/utils/Shader.h"
#include "gssmraytracer/utils/Point.h"
#include "gssmraytracer/utils/Scene.h"

#include "gssmraytracer/utils/Color.h"

namespace gssmraytracer {
  namespace utils {
    Color Shader::shade(const Point &hitpoint,
                        const Imath::Vec3<float> &normal
                        ) {
                          return Color(0,0,0,0);
                        }
  }
}
