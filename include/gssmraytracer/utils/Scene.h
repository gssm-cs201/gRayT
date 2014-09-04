#ifndef __SCENE_H__
#define __SCENE_H__
#include <memory>
#include <vector>

namespace gssmraytracer {
  namespace utils {
    class Shape; // forward declaration
    class Scene {
    public:
      static Scene * Instance();
      void addShape(const Shape *);
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
