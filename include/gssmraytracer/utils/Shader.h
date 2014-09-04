#ifndef __SHADER_H__
#define __SHADER_H__

#include "Point.h"
#include "Scene.h"

#include "Color.h"
namespace gssmraytracer {
  namespace utils {
    class Shader {
    public:
      virtual Color shade(const Point &hitpoint,
                     const Imath::Vec3<float> &normal
                     );
    };
  }
}
#endif //__SHADER_H__
