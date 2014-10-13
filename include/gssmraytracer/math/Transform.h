#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__
#include <OpenEXR/ImathMatrix.h>
#include <memory>
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/math/Vector.h"
#include "gssmraytracer/geometry/Normal.h"
#include "gssmraytracer/geometry/Point.h"

namespace gssmraytracer {
  namespace math {
    class Transform {
    public:
      Transform(); // default constructor
      Transform(const Transform &); // copy constructor
      Transform& operator=(const Transform &); // assignment operator

      Transform(const Imath::Matrix44<float> transformMatrix);

      Transform inverse() const;

      void translate(const Vector &translate);
      void rotate(const Vector &rotate);
      void scale(const Vector &scale);

      utils::Ray operator()(const utils::Ray &ray);
      geometry::Point operator()(const geometry::Point &point);
      math::Vector operator()(const math::Vector &vector);
      geometry::Normal operator()(const geometry::Normal &normal);
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
#endif // __TRANSFORM_H__
