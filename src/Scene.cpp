#include <vector>
#include "gssmraytracer/utils/Scene.h"
#include "gssmraytracer/geometry/Shape.h"
#include <limits>

namespace gssmraytracer {
  namespace utils {
    class Scene::Impl {
    public:

      std::vector<std::shared_ptr<geometry::Shape> > shapes;


    };
    Scene::Scene() : mImpl(new Impl) {}

    Scene::~Scene() {

    }

    Scene& Scene::getInstance() {
      static Scene instance;
      return instance;
    }

    void Scene::addShape(const std::shared_ptr<geometry::Shape> &shape) {

      mImpl->shapes.push_back(shape);
    }

    bool Scene::hit(const Ray &ws_ray) const {
      float thit = std::numeric_limits<float>::infinity();
      for (std::vector<std::shared_ptr<geometry::Shape> >::const_iterator iter =
        mImpl->shapes.begin(); iter != mImpl->shapes.end(); ++iter) {

          if ((*iter)->hit(ws_ray, thit)) {
            return true;
          }
        }

        return false;

    }

    bool Scene::hit(const Ray &ws_ray, float &hit_time) const {
      float closest_t = std::numeric_limits<float>::infinity();
      std::shared_ptr<geometry::Shape> candidate_shape;
      for (std::vector<std::shared_ptr<geometry::Shape> >::const_iterator iter =
        mImpl->shapes.begin(); iter != mImpl->shapes.end(); ++iter) {
          float thit = std::numeric_limits<float>::infinity();
          // If we hit the shape, record the t value and a pointer to the shape
          // as a candidate

          if ((*iter)->hit(ws_ray, thit)) {
            if (thit < closest_t) {
              closest_t = thit;
              candidate_shape = *iter;
            }
          }
        }
        if (candidate_shape != nullptr) {
          hit_time = closest_t;
          return true;
        }
        return false;

    }
    bool Scene::hit(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg) const {
      float closest_t = std::numeric_limits<float>::infinity();
      std::shared_ptr<geometry::Shape> candidate_shape;
      for (std::vector<std::shared_ptr<geometry::Shape> >::const_iterator iter =
        mImpl->shapes.begin(); iter != mImpl->shapes.end(); ++iter) {
          float thit = std::numeric_limits<float>::infinity();
          // If we hit the shape, record the t value and a pointer to the shape
          // as a candidate

          if ((*iter)->hit(ws_ray, thit)) {
            if (thit < closest_t) {
              closest_t = thit;
              candidate_shape = *iter;
            }
          }
        }
        if (candidate_shape != nullptr) {
          candidate_shape->hit(ws_ray, hit_time, dg);
          return true;
        }
        return false;



    }

    Scene *Scene::m_pInstance = NULL;

  }
}
