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
      Shape(const Imath::Vec3<float> &position, const Shader &shader);
      Shape(const Shape&);
      virtual ~Shape();
      virtual bool hit(const Ray &ws_ray, float &t0, float &t1) = 0;
      const Ray worldToObjectSpace(const Ray &ws_ray);
      const Ray objectToWorldSpace(const Ray &os_ray);

    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };

  }
}

#endif // __SHAPE_H__
