#ifndef __SHAPE_H__
#define __SHAPE_H__

#include <memory>
#include <OpenEXR/ImathVec.h>
#include "Shader.h"

namespace gssmraytracer {
  namespace utils {

    class Ray; // forward declaration

    class Shape {
    public:
      Shape(const Imath::Vec3<float> &position, const std::shared_ptr<Shader> shader);
      Shape(const Shape&);
      virtual ~Shape();
      virtual bool hit(const Ray &ws_ray, float &t0, float &t1,
                        Imath::Vec3<float> &hitpoint,
                        Imath::Vec3<float> &normal) const = 0;

      const std::shared_ptr<Shader> getShader() const;
      virtual const Color getShade(const Ray &ws_ray) const = 0;
      
      const Ray worldToObjectSpace(const Ray &ws_ray) const;
      const Ray objectToWorldSpace(const Ray &os_ray) const;

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };

  }
}

#endif // __SHAPE_H__
