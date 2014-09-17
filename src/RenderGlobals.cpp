#include "gssmraytracer/utils/RenderGlobals.h"
#include "gssmraytracer/geometry/Shape.h"
#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/utils/Color.h"
#include <vector>

using namespace gssmraytracer::geometry;

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
    bool RenderGlobals::hit(const Ray &ws_ray, float &t0, float &t1,
            Imath::Vec3<float> &hitpoint,
            Imath::Vec3<float> &normal) {
      for (std::vector<Shape*>::iterator iter = mImpl->shapes.begin();
          iter != mImpl->shapes.end(); ++iter) {
            if ((*iter)->hit(ws_ray, t0, t1, hitpoint, normal)) {
              return true;
            }
          }
          return false;
    }

    const Color RenderGlobals::shade(const Ray &ws_ray) const {
      Color color;
      float t0, t1;
      Imath::Vec3<float> hitpoint, normal;
      for (std::vector<Shape*>::iterator iter = mImpl->shapes.begin();
          iter != mImpl->shapes.end(); ++iter) {
            if ((*iter)->hit(ws_ray, t0, t1, hitpoint, normal)) {
              return (*iter)->getShade(ws_ray);
            }
          }
          return color;
    }



  }
}
