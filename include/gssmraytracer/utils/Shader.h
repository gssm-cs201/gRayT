#ifndef __SHADER_H__
#define __SHADER_H__

#include <OpenEXR/ImathVec.h>
#include "gssmraytracer/utils/Color.h"

namespace gssmraytracer {
  namespace utils {
    class Shader {
    public:
      virtual Color shade(const Imath::Vec3<float> &hitpoint,
                          const Imath::Vec3<float> &normal
                     ) = 0;
    };
  }
}
#endif //__SHADER_H__
