#include "grayt/utils/RenderGlobals.h"
#include "grayt/geometry/Shape.h"
#include "grayt/utils/Ray.h"
#include "grayt/utils/Color.h"
#include <limits>
#include <vector>

using namespace grayt::geometry;

namespace grayt {
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
    bool RenderGlobals::hit(const Ray &ws_ray, float &thit,
            std::shared_ptr<DifferentialGeometry> &dg) {

              float t = std::numeric_limits<float>::infinity();
              Shape *target_shape = nullptr;
              BBox bbox;
              for (std::vector<Shape*>::iterator iter = mImpl->shapes.begin();
                  iter != mImpl->shapes.end(); ++iter) {
                    bbox = bbox.combine((*iter)->worldBB());
                  }
      if (bbox.intersect(ws_ray)) {
      for (std::vector<Shape*>::iterator iter = mImpl->shapes.begin();
          iter != mImpl->shapes.end(); ++iter) {

            if ((*iter)->hit(ws_ray, thit)) {
              if (thit < t) {
                target_shape = *iter;
                t = thit;
              }
            }
            if (target_shape != nullptr) {
              target_shape->hit(ws_ray, thit, dg);
              return true;
            }
          }
        }
          return false;
    }





  }
}
