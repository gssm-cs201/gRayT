#include <vector>
#include "gssmraytracer/utils/Scene.h"
#include "gssmraytracer/geometry/Shape.h"

namespace gssmraytracer {
  namespace utils {
    class Scene::Impl {
    public:

      std::vector<const geometry::Shape*> shapes;


    };
    Scene::Scene() : mImpl(new Impl) {}

    Scene::~Scene() {
      for (std::vector<const geometry::Shape*>::iterator iter = mImpl->shapes.begin();
        iter != mImpl->shapes.end(); ++iter) {
          delete *iter;
        }

    }

    Scene * Scene::Instance() {
      if (!m_pInstance)
        m_pInstance = new Scene;
      return m_pInstance;
    }

    void Scene::addShape(const geometry::Shape *shape) {

      mImpl->shapes.push_back(shape);
    }
    Scene *Scene::m_pInstance = NULL;

  }
}
