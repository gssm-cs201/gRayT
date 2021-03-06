#ifndef __SHADER_H__
#define __SHADER_H__

#include <OpenEXR/ImathVec.h>
#include "gssmraytracer/utils/Color.h"
#include "gssmraytracer/geometry/DifferentialGeometry.h"
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class Shader {
    public:
      Shader();
      virtual Color shade(const Ray &view, const geometry::DifferentialGeometry &dg, const int bounce_count) const = 0;
      const float reflectivity() const;
      void reflectivity(const float reflectivity);
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };
  }
}
#endif //__SHADER_H__
