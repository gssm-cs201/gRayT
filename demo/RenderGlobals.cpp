#include "RenderGlobals.h"
#include "gssmraytracer/utils/Shape.h"
#include <vector>
namespace gssmraytracer {
  namespace utils {
    RenderGlobals& RenderGlobals::getInstance() {
      static RenderGlobals instance;
      return instance;
    }
    class RenderGlobals::Impl {
    public:
      Impl() : shapes(), image() {}

      std::vector<Shape> shapes;
      Image image;

    };
    RenderGlobals::RenderGlobals() : mImpl(new Impl){}

    void RenderGlobals::addShape(const Shape& shape) {
      mImpl->shapes.push_back(shape);
    }

    void RenderGlobals::setImage(const Image& image) {
      mImpl->image = image;
    }

    const Image& RenderGlobals::getImage() {
      return mImpl->image;
    }


    RenderGlobals& RenderGlobals::operator=(const RenderGlobals& other) {
      if (this != &other) {
        mImpl->shapes = other.mImpl->shapes;
      }
      return *this;
    }


  }
}
