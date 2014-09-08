#ifndef __SHADER_H__
#define __SHADER_H__

#include <OpenEXR/ImathVec.h>

namespace gssmraytracer {
  namespace utils {
    class Point; // forward declaration
    class Color; // forward declaration
    class Shader {
    public:
      virtual Color shade(const Point &hitpoint,
                     const Imath::Vec3<float> &normal
                     );
    };
  }
}
#endif //__SHADER_H__
