#ifndef __SCENE_H__
#define __SCENE_H__
#include <memory>
#include <vector>
#include "grayt/geometry/Primitive.h"
#include "grayt/geometry/DifferentialGeometry.h"

namespace grayt {
  namespace utils {
    class Scene {
    public:
      static Scene& getInstance();
      void addPrimitive(const std::shared_ptr<geometry::Primitive> &);
      void init();
      bool hit(const Ray &ws_ray) const;
      bool hit(const Ray &ws_ray, float &hit_time) const;
      bool hit(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg) const;
      bool hit(const Ray &ws_ray, float &hit_time, std::shared_ptr<geometry::DifferentialGeometry> & dg,
        std::shared_ptr<geometry::Primitive> &prim) const;
      ~Scene();
      const int maxBounceCount() const;
      void maxBounceCount(const int);
    private:
      Scene();
      Scene(const Scene&);
      Scene& operator=(const Scene&);
      class Impl;
      std::shared_ptr<Impl> mImpl;


    };
  }
}

#endif // __SCENE_H__
