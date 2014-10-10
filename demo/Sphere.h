#include <gssmraytracer/geometry/Shape.h>
#include <memory>

namespace gssmraytracer {
  namespace geometry {
    class Sphere : public Shape {
    public:
      Sphere (const Imath::Vec3<float> &position,
                          const std::shared_ptr<utils::Shader> shader,
                          const double radius);
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
