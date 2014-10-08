#include "gssmraytracer/math/Transform.h"
#include "gssmraytracer/utils/Ray.h"
namespace gssmraytracer {
  namespace math {
    class Transform::Impl {
    public:
      Imath::Matrix44<float> mat;
    };

    Transform::Transform() : mImpl(new Impl) {}

    Transform::Transform(const Transform &transform) : mImpl(new Impl) {
      mImpl->mat = transform.mImpl->mat;
    }
    Transform& Transform::operator=(const Transform &other) {
      if (this != &other) {
          mImpl->mat = other.mImpl->mat;
      }
      return *this;
    }

    Transform::Transform(const Imath::Matrix44<float> mat) :
                         mImpl(new Impl) {
      mImpl->mat = mat;
    }


    Transform Transform::inverse() {
      return Transform(mImpl->mat.inverse());
    }

    void Transform::translate(Imath::Vec3<float> translation) {
      mImpl->mat.translate(translation);
    }
    void Transform::rotate(Imath::Vec3<float> rotation) {
      mImpl->mat.rotate(rotation);
    }
    void Transform::scale(Imath::Vec3<float> scale) {
      mImpl->mat.scale(scale);
    }

    utils::Ray Transform::transform(const utils::Ray &ray) {
        Imath::Vec3<float> new_origin, new_direction;
        mImpl->mat.multVecMatrix(ray.origin(), new_origin );
        mImpl->mat.multDirMatrix(ray.dir(), new_direction );
        return utils::Ray(new_origin, new_direction);
    }



  }
}
