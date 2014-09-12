#include "gssmraytracer/utils/Shape.h"
#include "gssmraytracer/utils/Shader.h"
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/math/Transform.h"
namespace gssmraytracer {
  namespace utils {
    class Shape::Impl {
    public:
      Imath::Vec3<float> position;
      std::shared_ptr<Shader> shader;
      math::Transform transform;
    };
    Shape::Shape(const Imath::Vec3<float> &position, const std::shared_ptr<Shader> shader) :
      mImpl(new Impl) {
        mImpl->transform.translate(position);
        mImpl->shader = shader;
    }


    Shape::Shape(const Shape& shape) : mImpl(new Impl) {
      mImpl->position = shape.mImpl->position;
      mImpl->shader = shape.mImpl->shader;
    }
    Shape::~Shape() {

    }

    const Ray Shape::worldToObjectSpace(const Ray &ws_ray) const{
      Ray os_ray = mImpl->transform.transform(ws_ray);

      return os_ray;

    }
    const Ray Shape::objectToWorldSpace(const Ray &os_ray) const{
      Ray ws_ray = mImpl->transform.inverse().transform(os_ray);

      return ws_ray;

    }
    const std::shared_ptr<Shader> Shape::getShader() const {
      return mImpl->shader;
    }
  }
}
