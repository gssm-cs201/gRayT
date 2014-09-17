#include "gssmraytracer/geometry/Shape.h"
#include "gssmraytracer/utils/Shader.h"
#include "gssmraytracer/math/Transform.h"
using namespace gssmraytracer::utils;
namespace gssmraytracer {
  namespace geometry {
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

    const utils::Ray Shape::worldToObjectSpace(const utils::Ray &ws_ray) const{
      utils::Ray os_ray = mImpl->transform.transform(ws_ray);

      return os_ray;

    }
    const utils::Ray Shape::objectToWorldSpace(const utils::Ray &os_ray) const{
      utils::Ray ws_ray = mImpl->transform.inverse().transform(os_ray);

      return ws_ray;

    }
    const std::shared_ptr<Shader> Shape::getShader() const {
      return mImpl->shader;
    }
  }
}
