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
      virtual bool hit(const Ray &ray, float &time);
      virtual ~Shape();
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;
    };

  }
}

#endif // __SHAPE_H__
