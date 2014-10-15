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
      //! Creates a new Transform set to the identity
      Transform();

      //! Copy Constructor
      Transform(const Transform &);

      //! Assignment operator
      Transform& operator=(const Transform &);


      //! Initializes a Transform based on an OpenEXR 4x4 Matrix
      Transform(const Imath::Matrix44<float> transformMatrix);

      //! Returns a new inverse Transform object, based on the inverse of this one.
      Transform inverse() const;

      //! Sets the translation component.
      void translate(const Vector &translate);

      //! Sets the rotation component.
      void rotate(const Vector &rotate);

      //! Sets the scale component.
      void scale(const Vector &scale);

      //! Returns a new Ray transformed by this Transform
      utils::Ray operator()(const utils::Ray &ray);

      //! Returns a new Point transformed by this Transform
      geometry::Point operator()(const geometry::Point &point);

      //! Returns a new Vector transformed by this Transform
      math::Vector operator()(const math::Vector &vector);

      //! Returns a new Normal transformed by this Transform
      geometry::Normal operator()(const geometry::Normal &normal);
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
#endif // __TRANSFORM_H__
