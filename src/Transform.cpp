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


    const Transform Transform::inverse() const {
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

    const utils::Ray Transform::operator()(const utils::Ray &ray) const {
        Imath::Vec3<float> new_origin, new_direction;
        mImpl->mat.multVecMatrix(Imath::Vec3<float>(ray.origin().x(), ray.origin().y(), ray.origin().z()), new_origin );
        mImpl->mat.multDirMatrix(Imath::Vec3<float>(ray.dir().x(), ray.dir().y(), ray.dir().z()), new_direction );
        return utils::Ray(geometry::Point(new_origin.x, new_origin.y, new_origin.z), math::Vector(new_direction.x, new_direction.y, new_direction.z));
    }
    const geometry::Point Transform::operator()(const geometry::Point &point) const {
      Imath::Vec3<float> new_point;
      mImpl->mat.multVecMatrix(Imath::Vec3<float>(point.x(), point.y(), point.z()), new_point);
      return geometry::Point(new_point.x, new_point.y, new_point.z);

    }
    const math::Vector Transform::operator()(const math::Vector &vector) const {
      Imath::Vec3<float> new_vector;
      mImpl->mat.multDirMatrix(Imath::Vec3<float>(vector.x(), vector.y(), vector.z()), new_vector);
      return math::Vector(new_vector.x, new_vector.y, new_vector.z);
    }
    const geometry::Normal Transform::operator()(const geometry::Normal &normal) const {
      Imath::Vec3<float> new_normal;
      mImpl->mat.inverse().transpose().multDirMatrix(Imath::Vec3<float>(normal.x(), normal.y(), normal.z()), new_normal);
      return geometry::Normal(new_normal.x, new_normal.y, new_normal.z);
    }



  }
}
