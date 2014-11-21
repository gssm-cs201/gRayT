#include "gssmraytracer/geometry/Primitive.h"
namespace gssmraytracer {
  namespace geometry {
    class Primitive::Impl {
    public:
      std::shared_ptr<Shape> shape;
      std::shared_ptr<utils::Shader> shader;

    };

    Primitive::Primitive(const std::shared_ptr<Shape> &shape,
      const std::shared_ptr<utils::Shader> &shader) : mImpl(new Impl) {
        mImpl->shape = shape;
        mImpl->shader = shader;
      }

    bool Primitive::hit(const utils::Ray &ws_ray) const {
      float thit;
      return hit(ws_ray, thit);
    }
    bool Primitive::hit(const utils::Ray &ws_ray, float &hit_time) const {
      return mImpl->shape->hit(ws_ray, hit_time);
    }

    bool Primitive::hit(const utils::Ray &ws_ray, float &hit_time,
                        std::shared_ptr<DifferentialGeometry> &dg) const {
      return mImpl->shape->hit(ws_ray, hit_time, dg);
    }

    const utils::Color Primitive::shade(const utils::Ray &view, const std::shared_ptr<DifferentialGeometry> &dg, const int bounce_count) const {
      return mImpl->shader->shade(view, *dg, bounce_count);
    }

    const BBox Primitive::worldBound() const {
      return mImpl->shape->worldBB();
    }


  }
}
