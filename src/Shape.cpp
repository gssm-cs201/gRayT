#include "gssmraytracer/geometry/Shape.h"
#include "gssmraytracer/utils/Shader.h"
#include "gssmraytracer/math/Transform.h"
using namespace gssmraytracer::utils;
namespace gssmraytracer {
  namespace geometry {
    class Shape::Impl {
    public:
      math::Transform transform;
    };
    Shape::Shape(const math::Transform &transform) :
      mImpl(new Impl) {
        mImpl->transform = transform;
    }


    Shape::Shape(const Shape& shape) : mImpl(new Impl) {
      mImpl->transform = shape.mImpl->transform;
    }
    Shape::~Shape() {

    }

    const utils::Ray Shape::worldToObjectSpace(const utils::Ray &ws_ray) const{
      utils::Ray os_ray = mImpl->transform(ws_ray);

      return os_ray;

    }
    const utils::Ray Shape::objectToWorldSpace(const utils::Ray &os_ray) const{
      utils::Ray ws_ray = mImpl->transform.inverse()(os_ray);

      return ws_ray;

    }



  }
}
