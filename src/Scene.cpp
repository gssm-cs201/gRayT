#include <vector>
#include "gssmraytracer/utils/Scene.h"
#include "gssmraytracer/utils/BVHAccel.h"
#include <limits>

namespace gssmraytracer {
  namespace utils {
    class Scene::Impl {
    public:
      Impl() : primitives(), bvh() {}
      std::vector<std::shared_ptr<geometry::Primitive> > primitives;
      std::shared_ptr<BVHAccel> bvh;


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

    bool Scene::hit(const Ray &ws_ray) const {
      float thit = std::numeric_limits<float>::infinity();
      for (std::vector<std::shared_ptr<geometry::Primitive> >::const_iterator iter =
        mImpl->primitives.begin(); iter != mImpl->primitives.end(); ++iter) {

          if ((*iter)->hit(ws_ray, thit)) {
            return true;
          }
        }

        return false;

    }

    bool Scene::hit(const Ray &ws_ray, float &hit_time) const {
      float closest_t = std::numeric_limits<float>::infinity();
      std::shared_ptr<geometry::Primitive> candidate_prim;
      for (std::vector<std::shared_ptr<geometry::Primitive> >::const_iterator iter =
        mImpl->primitives.begin(); iter != mImpl->primitives.end(); ++iter) {
          float thit = std::numeric_limits<float>::infinity();
          // If we hit the shape, record the t value and a pointer to the shape
          // as a candidate

          if ((*iter)->hit(ws_ray, thit)) {
            if (thit < closest_t) {
              closest_t = thit;
              candidate_prim = *iter;
            }
          }
        }
        if (candidate_prim != nullptr) {
          hit_time = closest_t;
          return true;
        }
        return false;

    }
    bool Scene::hit(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg) const {
      std::shared_ptr<geometry::Primitive> prim;
      return hit(ws_ray, hit_time, dg, prim);
    }
    bool Scene::hit(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg,
      std::shared_ptr<geometry::Primitive> &prim) const {
        // lazy instantiation
        if (!mImpl->bvh) {
            std::shared_ptr<BVHAccel> bvh(new BVHAccel(mImpl->primitives, 1));
            mImpl->bvh = bvh;

        }
//        float closest_t = std::numeric_limits<float>::infinity();
//        std::shared_ptr<geometry::Primitive> candidate_prim;

        return mImpl->bvh->intersect(ws_ray, hit_time, dg, prim);
/*
        for (std::vector<std::shared_ptr<geometry::Primitive> >::const_iterator iter =
          mImpl->primitives.begin(); iter != mImpl->primitives.end(); ++iter) {
            float thit = std::numeric_limits<float>::infinity();
            // If we hit the shape, record the t value and a pointer to the shape
            // as a candidate

            if ((*iter)->hit(ws_ray, thit)) {
              if (thit < closest_t) {
                closest_t = thit;
                candidate_prim = *iter;
              }
            }
          }
          if (candidate_prim != nullptr) {
            candidate_prim->hit(ws_ray, hit_time, dg);
            prim = candidate_prim;
            return true;
          }
          return false;
*/
      }


  }
}
