#include "grayt/geometry/Primitive.h"
namespace grayt {
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

    Primitive::Primitive(const Primitive &other) : mImpl(new Impl) {
      mImpl->shape = other.mImpl->shape;
      mImpl->shader = other.mImpl->shader;

    }
    Primitive& Primitive::operator=(const Primitive &other) {
      if (this != &other) {
        mImpl->shape = other.mImpl->shape;
        mImpl->shader = other.mImpl->shader;
      }
      return *this;
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

    const bool Primitive::canIntersect() const {
      return  mImpl->shape->canIntersect();
    }

    void Primitive::refine(std::vector<std::shared_ptr<geometry::Primitive> > &refined) const {
      if (!mImpl->shape->canIntersect()) {
        std::vector<std::shared_ptr<Shape> > refine_shape;
        mImpl->shape->refine(refine_shape);
       
        for (std::vector<std::shared_ptr<Shape> >::iterator iter = refine_shape.begin(); iter != refine_shape.end(); ++iter) {
          std::shared_ptr<geometry::Primitive> prim(new Primitive((*iter), mImpl->shader));
          refined.push_back(prim);
        }
      }
    }


  }
}
