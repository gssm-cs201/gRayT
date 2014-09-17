#ifndef __SCENE_H__
#define __SCENE_H__
#include <memory>
#include <vector>
#include "gssmraytracer/geometry/Shape.h"

namespace gssmraytracer {
  namespace utils {
    class Scene {
    public:
      static Scene * Instance();
      void addShape(const geometry::Shape *);
      ~Scene();
    private:
      Scene();
      Scene(const Scene&);
      Scene& operator=(const Scene&);
      class Impl;
      std::shared_ptr<Impl> mImpl;
      static Scene *m_pInstance;


    };
  }
}

#endif // __SCENE_H__
