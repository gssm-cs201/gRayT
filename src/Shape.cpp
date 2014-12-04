#include "gssmraytracer/geometry/Shape.h"
#include "gssmraytracer/utils/Shader.h"
#include "gssmraytracer/math/Transform.h"
using namespace gssmraytracer::utils;
namespace gssmraytracer {
  namespace geometry {
    class Shape::Impl {
    public:
      math::Transform o2w;
      math::Transform w2o;
      bool reverseOrientation;
    };
    Shape::Shape(const math::Transform &transform,
                const bool reverseOrientation) :
      mImpl(new Impl) {
        mImpl->o2w = transform;
        mImpl->w2o = transform.inverse();
        mImpl->reverseOrientation = reverseOrientation;
    }


    Shape::Shape(const Shape& shape) : mImpl(new Impl) {
      mImpl->o2w = shape.mImpl->o2w;
      mImpl->w2o = shape.mImpl->w2o;
    }
    Shape::~Shape() {

    }

    const math::Transform Shape::worldToObjectSpace() const{
      return mImpl->w2o;


    }
    const math::Transform Shape::objectToWorldSpace() const{
      return mImpl->o2w;
    }

    void Shape::refine(std::vector<std::shared_ptr<Shape> > &refined) const {
      // Default implementation does nothing
    }



  }
}
