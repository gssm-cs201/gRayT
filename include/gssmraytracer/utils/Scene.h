#ifndef __SCENE_H__
#define __SCENE_H__
#include <memory>
#include <vector>
#include "gssmraytracer/geometry/Shape.h"
#include "gssmraytracer/geometry/DifferentialGeometry.h"

namespace gssmraytracer {
  namespace utils {
    class Scene {
    public:
      static Scene& getInstance();
      void addShape(const std::shared_ptr<geometry::Shape> &);
      bool hit(const Ray &ws_ray) const;
      bool hit(const Ray &ws_ray, float &hit_time) const;
      bool hit(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg) const;
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
