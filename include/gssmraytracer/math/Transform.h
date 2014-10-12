#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__
#include <OpenEXR/ImathMatrix.h>
#include <memory>
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/math/Vector.h"

namespace gssmraytracer {
  namespace math {
    class Transform {
    public:
      Transform(); // default constructor
      Transform(const Transform &); // copy constructor
      Transform& operator=(const Transform &); // assignment operator

      Transform(const Imath::Matrix44<float> transformMatrix);

      Transform inverse();

      void translate(const Vector &translate);
      void rotate(const Vector &rotate);
      void scale(const Vector &scale);

      utils::Ray transform(const utils::Ray &ray);
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
#endif // __TRANSFORM_H__
