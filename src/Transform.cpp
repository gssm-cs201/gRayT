#include "gssmraytracer/math/Transform.h"
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/geometry/Point.h"
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

    void Transform::translate(const Vector &translation) {
      Imath::Vec3<float> temp;
      temp.x = translation.x();
      temp.y = translation.y();
      temp.z = translation.z();
      mImpl->mat.translate(temp);
    }
    void Transform::rotate(const Vector &rotation) {
      Imath::Vec3<float> temp;
      temp.x = rotation.x();
      temp.y = rotation.y();
      temp.z = rotation.z();
      mImpl->mat.rotate(Imath::Vec3<float>(
                        rotation.x(),
                        rotation.y(),
                        rotation.z())
                       );
    }
    void Transform::scale(const Vector &scale) {
      mImpl->mat.scale(Imath::Vec3<float>(scale.x(), scale.y(), scale.z()));
    }

    utils::Ray Transform::transform(const utils::Ray &ray) {
        Imath::Vec3<float> new_origin, new_direction;
        mImpl->mat.multVecMatrix(Imath::Vec3<float>(ray.origin().x(), ray.origin().y(), ray.origin().z()), new_origin );
        mImpl->mat.multDirMatrix(Imath::Vec3<float>(ray.dir().x(), ray.dir().y(), ray.dir().z()), new_direction );
        return utils::Ray(geometry::Point(new_origin.x, new_origin.y, new_origin.z), math::Vector(new_direction.x, new_direction.y, new_direction.z));
    }



  }
}
