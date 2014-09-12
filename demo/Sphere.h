#include <gssmraytracer/utils/Shape.h>
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class Sphere : public Shape {
    public:
      Sphere (const Imath::Vec3<float> &position,
                          const std::shared_ptr<Shader> shader,
                          const double radius);
      bool hit(const Ray &ws_ray, float &t0, float &t1,
               Imath::Vec3<float> &hitpoint,
               Imath::Vec3<float> &normal) const;
      const Color getShade(const Ray &ws_ray) const;
      virtual ~Sphere();
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
