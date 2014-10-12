#include <gssmraytracer/utils/Ray.h>
#include <gssmraytracer/math/Transform.h>
#include <gssmraytracer/utils/Color.h>
#include "Sphere.h"
#include <algorithm>
#include <iostream>

using namespace gssmraytracer::math;
using namespace gssmraytracer::utils;
namespace gssmraytracer {
  namespace geometry {

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

    };

    Sphere::Sphere(const Transform &transform,
                 const std::shared_ptr<Shader> shader,
                 const double radius) : Shape(transform, shader), mImpl(new Impl) {
                   mImpl->radius = radius;

    }
    Sphere::~Sphere() {}
    bool Sphere::hit(const Ray &ws_ray, float *thit,
                      DifferentialGeometry *dg) const {
      float phi;
      Point phit;

      // Transform the ray into object space
      Ray os_ray = worldToObjectSpace(ws_ray);

      // Do ray-sphere intersection in object space
      // Compute quadratic sphere coefficients

      float A = os_ray.dir().x() * os_ray.dir().x() +
                os_ray.dir().y() * os_ray.dir().y() +
                os_ray.dir().z() * os_ray.dir().z();
      float B = 2.0 * (os_ray.dir().x() * os_ray.origin().x() +
                     os_ray.dir().y() * os_ray.origin().y() +
                     os_ray.dir().z() * os_ray.origin().z());
      float C = os_ray.origin().x() * os_ray.origin().x() +
                os_ray.origin().y() * os_ray.origin().y() +
                os_ray.origin().z() * os_ray.origin().z() -
                mImpl->radius * mImpl->radius;


      // Solve quadratic equation for t values
      float t0, t1;
      if (!mImpl->Quadratic(A,B,C, &t0, &t1)) return false;
      // compute intersection distance along ray
      if (t0 > os_ray.maxt() || t1 < os_ray.mint())
        return false;

      thit = &t0;
      if (t0 < os_ray.mint()) {
        thit = &t1;
        if (*thit > os_ray.maxt()) return false;
      }

      /*
      // Compute sphere hit position and phi
      phit = ray(thit);
      if (phit.x == 0.f && phit.y == 0.f) phit.x = 1e-5f * radius;
      phi = atan2f(phit.y, phit.x);
      if (phi < 0.) phi += 2.f*M_PI;
      // Test against clipping parameters
      if ((zmin > -radius && phit.z < zmin) ||
        (zmax < radius && phit.z > zmax) ||
         phi > phiMax) {
           if (this == t1) return false;
           thit = t1;

           if ((zmin > -radius && phit.z < zmin) ||
             (zmax < radius && phit.z > zmax) ||
             phi > phiMax)
             return false;
         }

         // find parametric representation of sphere
         float u = phi/phiMax;
         float theta = acosf(Clamp(phit.z/radius, -1.f, 1.f));
         float v = (theta - thetaMin) / (thetaMax - thetaMin);
         float zradius = sqrtf(phit.x * phit.x + phit.y * phit.y);
         float invzradius = 1.f / zradius;
         float cosphi = phit.x * invradius;
         float sinphi = phit.y * invradius;
         Vector dpdu(-phiMax * phit.y, phiMax * phit.x, 0);
         Vector dpdv = (thetaMax - thetaMin) *
                Vector(phit.z * cosphi, phit.z * sinphi,
                      -radius * sinf(theta));

                      */


      // if the ray intersects the sphere return true
      dg->p = Point(os_ray.point(*thit));
    //  dp->nn = hitpoint.normalize();
       return true;
    }

    const utils::Color Sphere::getShade(const Ray &ws_ray) const {
      float thit;
      utils::Color color;
      DifferentialGeometry dg;

      if (hit(ws_ray, &thit, &dg))
        color =  (getShader())->shade(Imath::Vec3<float>(dg.p.x(), dg.p.y(), dg.p.z()), Normal(dg.nn.x(), dg.nn.y(), dg.nn.z()));

      return color;


    }

  }
}
