#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__
#include "gssmraytracer/utils/Color.h"
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/geometry/Shape.h"
#include "gssmraytracer/utils/Shader.h"

namespace gssmraytracer {
  namespace geometry {

    class Primitive {
    public:
      Primitive(const std::shared_ptr<Shape> &shape,
                const std::shared_ptr<utils::Shader> &shader);
      bool hit(const utils::Ray &ws_ray) const;
      bool hit(const utils::Ray &ws_ray, float &hit_time) const;
      bool hit(const utils::Ray &ws_ray, float &hit_time,
                std::shared_ptr<DifferentialGeometry> &dg) const;
      const utils::Color shade(const std::shared_ptr<DifferentialGeometry> &dg) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };

  }
}
#endif // __PRIMITIVE_H__
