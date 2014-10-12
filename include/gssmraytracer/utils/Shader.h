#ifndef __SHADER_H__
#define __SHADER_H__

#include <OpenEXR/ImathVec.h>
#include "gssmraytracer/utils/Color.h"
#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/geometry/Normal.h"

namespace gssmraytracer {
  namespace utils {
    class Shader {
    public:
      virtual Color shade(const geometry::Point &hitpoint,
                          const geometry::Normal &normal
                     ) = 0;
    };
  }
}
#endif //__SHADER_H__
