#include <gssmraytracer/utils/Ray.h>
#include "Sphere.h"
#include <algorithm>

namespace gssmraytracer {
  namespace utils {

    class Sphere::Impl {
    public:
      double radius;
      inline bool Quadratic(const float A, const float B,
                            const float C, float *t0, float *t1) {
                              float discrim = B * B -4.f * A * C;
                              if (discrim <= 0.) return false;
                              float rootDiscrim = sqrtf(discrim);

                              float q;
                              if (B < 0) q = -0.5f * (B - rootDiscrim);
                              else       q = -0.5f * (B + rootDiscrim);
                              *t0 = q /A;
                              *t1 = C/q;

                              if (*t0 > *t1) std::swap(*t0, *t1);
                              return true;
                            }
      Ray worldToObjectSpace(const Ray &ray) {
        // TO-DO
        return ray;
      }
    };

    Sphere::Sphere(const Imath::Vec3<float> &position,
                 const Shader &shader,
                 const double radius) : Shape(position, shader), mImpl(new Impl) {
                   mImpl->radius = radius;

    }
    Sphere::~Sphere() {}
    bool Sphere::hit(const Ray &ws_ray, float &t0, float &t1) {
      Ray os_ray = mImpl->worldToObjectSpace(ws_ray);

      // Do ray-sphere intersection in object space
      // Compute quadratic sphere coefficients
      float A = os_ray.dir().x * os_ray.dir().x +
                os_ray.dir().y * os_ray.dir().y +
                os_ray.dir().z * os_ray.dir().z;
      float B = 2.0 * (os_ray.dir().x * os_ray.origin().x +
                     os_ray.dir().y * os_ray.origin().y +
                     os_ray.dir().z * os_ray.origin().z);
      float C = os_ray.origin().x * os_ray.origin().x +
                os_ray.origin().y * os_ray.origin().y +
                os_ray.origin().z * os_ray.origin().z -
                mImpl->radius * mImpl->radius;

      // Solve quadratic equation for t values
      if (!mImpl->Quadratic(A,B,C, &t0, &t1)) return false;
      // compute intersection distance along ray
      if (t0 > os_ray.maxt() || t1 < os_ray.mint())
        return false;
      float thit = t0;
      if (t0 < os_ray.mint()) {
        thit = t1;
        if (thit > os_ray.maxt()) return false;
      }
      // if the ray intersects the sphere return true
      t0 = thit;
       return true;
    }

  }
}
