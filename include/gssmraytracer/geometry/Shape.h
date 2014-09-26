#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <memory>
#include <OpenEXR/ImathVec.h>
#include "gssmraytracer/utils/Shader.h"
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/utils/Color.h"

namespace gssmraytracer {
  namespace geometry {


    class Shape {
    public:
      Shape(const Imath::Vec3<float> &position, const std::shared_ptr<utils::Shader> shader);
      Shape(const Shape&);
      virtual ~Shape();
      virtual bool hit(const utils::Ray &ws_ray, float &t0, float &t1,
                        Imath::Vec3<float> &hitpoint,
                        Imath::Vec3<float> &normal) const = 0;

      const std::shared_ptr<utils::Shader> getShader() const;
      virtual const utils::Color getShade(const utils::Ray &ws_ray) const = 0;

      const utils::Ray worldToObjectSpace(const utils::Ray &ws_ray) const;
      const utils::Ray objectToWorldSpace(const utils::Ray &os_ray) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };

  }
}

#endif // __SHAPE_H__
