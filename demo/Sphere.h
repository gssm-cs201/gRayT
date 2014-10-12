#include <gssmraytracer/geometry/Shape.h>
#include <gssmraytracer/math/Transform.h>
#include <memory>

namespace gssmraytracer {
  namespace geometry {
    class Sphere : public Shape {
    public:
      Sphere (const math::Transform &transform,
                          const std::shared_ptr<utils::Shader> shader,
                          const float radius, float z0, float z1, float pm=360.0f);
      bool hit(const utils::Ray &ws_ray, float *tHit,
               DifferentialGeometry *dg) const;
      const utils::Color getShade(const utils::Ray &ws_ray) const;
      virtual ~Sphere();
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
