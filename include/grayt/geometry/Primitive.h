#ifndef __PRIMITIVE_H__
#define __PRIMITIVE_H__
#include "grayt/utils/Color.h"
#include "grayt/utils/Ray.h"
#include "grayt/geometry/Shape.h"
#include "grayt/utils/Shader.h"

namespace grayt {
  namespace geometry {

    class Primitive {
    public:
      Primitive(const std::shared_ptr<Shape> &shape,
                const std::shared_ptr<utils::Shader> &shader);
      Primitive(const Primitive &);
      Primitive& operator=(const Primitive &);
      bool hit(const utils::Ray &ws_ray) const;
      bool hit(const utils::Ray &ws_ray, float &hit_time) const;
      bool hit(const utils::Ray &ws_ray, float &hit_time,
                std::shared_ptr<DifferentialGeometry> &dg) const;
      const utils::Color shade(const utils::Ray &view, const std::shared_ptr<DifferentialGeometry> &dg, const int bounce_count = 0) const;
      const BBox worldBound() const;

      const bool canIntersect() const;
      
      void refine(std::vector<std::shared_ptr<geometry::Primitive> > &refined) const;


    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };

  }
}
#endif // __PRIMITIVE_H__
