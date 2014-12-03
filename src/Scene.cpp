#include <vector>
#include "gssmraytracer/utils/Scene.h"
#include "gssmraytracer/utils/BVHAccel.h"
#include <limits>

namespace gssmraytracer {
  namespace utils {
    class Scene::Impl {
    public:
      Impl() : primitives(), bvh(), max_bounce_count(0) {}
      std::vector<std::shared_ptr<geometry::Primitive> > primitives;
      std::shared_ptr<BVHAccel> bvh;
      int max_bounce_count;


    };
    Scene::Scene() : mImpl(new Impl) {}

    Scene::~Scene() {

    }

    Scene& Scene::getInstance() {
      static Scene instance;
      return instance;
    }

    void Scene::addPrimitive(const std::shared_ptr<geometry::Primitive> &primitive) {

      mImpl->primitives.push_back(primitive);

    }

    void Scene::init() {
      if (!mImpl->bvh) {
        uint32_t var = 1;
          std::shared_ptr<BVHAccel> bvh(new BVHAccel(mImpl->primitives, var));
          mImpl->bvh = bvh;

      }

    }

    bool Scene::hit(const Ray &ws_ray) const {
      std::shared_ptr<geometry::DifferentialGeometry> dg;
      std::shared_ptr<geometry::Primitive> prim;
      float hit_time;
      return hit(ws_ray, hit_time, dg, prim);

    }

    bool Scene::hit(const Ray &ws_ray, float &hit_time) const {
      std::shared_ptr<geometry::DifferentialGeometry> dg;
      std::shared_ptr<geometry::Primitive> prim;

      return hit(ws_ray, hit_time, dg, prim);


    }
    bool Scene::hit(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg) const {
      std::shared_ptr<geometry::Primitive> prim;
      return hit(ws_ray, hit_time, dg, prim);
    }

    bool Scene::hit(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg,
      std::shared_ptr<geometry::Primitive> &prim) const {
      
        bool result = mImpl->bvh->intersect(ws_ray, hit_time, dg, prim);

        return result;

      }

      const int Scene::maxBounceCount() const {
        return mImpl->max_bounce_count;
      }
      void Scene::maxBounceCount(const int max_bounce_count) {
        mImpl->max_bounce_count = max_bounce_count;
      }


  }
}
