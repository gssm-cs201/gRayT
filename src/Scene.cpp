#include <vector>
#include "gssmraytracer/utils/Scene.h"
#include "gssmraytracer/utils/Shape.h"

namespace gssmraytracer {
  namespace utils {
    class Scene::Impl {
    public:

      std::vector<const Shape*> shapes;


    };
    Scene::Scene() : mImpl(new Impl) {}

    Scene::~Scene() {
      for (std::vector<const Shape*>::iterator iter = mImpl->shapes.begin();
        iter != mImpl->shapes.end(); ++iter) {
          delete *iter;
        }

    }

    Scene * Scene::Instance() {
      if (!m_pInstance)
        m_pInstance = new Scene;
      return m_pInstance;
    }

    void Scene::addShape(const Shape *shape) {

      mImpl->shapes.push_back(shape);
    }
    Scene *Scene::m_pInstance = NULL;

  }
}
