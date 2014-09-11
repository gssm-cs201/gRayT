#include "gssmraytracer/utils/RenderGlobals.h"
#include "gssmraytracer/utils/Shape.h"
#include "gssmraytracer/utils/Ray.h"
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

      std::vector<Shape*> shapes;
      Image image;

    };
    RenderGlobals::RenderGlobals() : mImpl(new Impl){}

    void RenderGlobals::addShape(Shape* shape) {
      mImpl->shapes.push_back(shape);
    }

    void RenderGlobals::setImage(const Image& image) {
      mImpl->image = image;
    }

    const Image RenderGlobals::getImage() const {
      return mImpl->image;
    }


    RenderGlobals& RenderGlobals::operator=(const RenderGlobals& other) {
      if (this != &other) {
        mImpl->shapes = other.mImpl->shapes;
      }
      return *this;
    }
    bool RenderGlobals::hit(const Ray &ws_ray, float &t0, float &t1) {
      for (std::vector<Shape*>::iterator iter = mImpl->shapes.begin();
          iter != mImpl->shapes.end(); ++iter) {
            if ((*iter)->hit(ws_ray, t0, t1)) {
              return true;
            }
          }
          return false;
    }


  }
}
