#include "gssmraytracer/utils/Shape.h"
#include "gssmraytracer/utils/Shader.h"
namespace gssmraytracer {
  namespace utils {
    class Shape::Impl {
    public:
      Imath::Vec3<float> position;
      Shader shader;
    };
    Shape::Shape(const Imath::Vec3<float> &position, const Shader &shader) :
      mImpl(new Impl) {
        mImpl->position = position;
        mImpl->shader = shader;
    }


    Shape::Shape(const Shape& shape) : mImpl(new Impl) {
      mImpl->position = shape.mImpl->position;
      mImpl->shader = shape.mImpl->shader;
    }
    Shape::~Shape() {

    }
  }
}
