#include <gssmraytracer/utils/Shape.h>
#include <memory>

namespace gssmraytracer {
  namespace utils {
    class Sphere : public Shape {
    public:
      Sphere (const Imath::Vec3<float> &position,
                          const Shader &shader,
                          const double radius);
      virtual bool hit(const Ray &ws_ray, float &t0, float &t1);
      virtual ~Sphere();
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
