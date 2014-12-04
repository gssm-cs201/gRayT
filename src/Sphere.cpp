#include "gssmraytracer/utils/Ray.h"
#include "gssmraytracer/math/Transform.h"
#include "gssmraytracer/utils/Color.h"
#include "gssmraytracer/utils/gssmraytracer.h"
#include "gssmraytracer/geometry/Sphere.h"
#include <algorithm>

using namespace gssmraytracer::math;
using namespace gssmraytracer::utils;
namespace gssmraytracer {
  namespace geometry {

    class Sphere::Impl {
    public:
      float radius;
      float phiMax;
      float zmin, zmax;
      float thetaMin, thetaMax;
      BBox obbox;
      BBox wbbox;

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
                  const bool reverseOrientation,
                 const float radius) : Shape(transform, reverseOrientation), mImpl(new Impl) {
                   mImpl->radius = radius;
                   mImpl->zmin = -radius;
                   mImpl->zmax = radius;
                   mImpl->thetaMin = -1.f;
                   mImpl->thetaMax = 1.f;
                   mImpl->phiMax = 360.0f;
                   mImpl->obbox = objectBB();
                   mImpl->wbbox = worldBB();

    }

    Sphere::Sphere(const Transform &transform,
                  const bool reverseOrientation,
                 const float radius, float z0, float z1, float pm) : Shape(transform, reverseOrientation), mImpl(new Impl) {
                   mImpl->radius = radius;
                   mImpl->zmin = Clamp(fmin(z0,z1), -radius, radius);
                   mImpl->zmax = Clamp(fmax(z0,z1), -radius, radius);
                   mImpl->thetaMin = acosf(Clamp(mImpl->zmin/radius, -1.f, 1.f));
                   mImpl->thetaMax = acosf(Clamp(mImpl->zmax/radius, -1.f, 1.f));
                   mImpl->phiMax = Radians(Clamp(pm, 0.0f, 360.0f));
                   mImpl->obbox = objectBB();
                   mImpl->wbbox = worldBB();

    }
    Sphere::~Sphere() {}

    bool Sphere::hit(const utils::Ray &ws_ray, float &thit) const {
      if (!mImpl->wbbox.intersect(ws_ray)) return false;

      float phi;
      Point phit;

      // Transform the ray into object space
      Ray os_ray = worldToObjectSpace()(ws_ray);

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

      thit = t0;
      if (t0 < os_ray.mint()) {
        thit = t1;
        if (thit > os_ray.maxt()) return false;
      }


      // Compute sphere hit position and phi
      phit = os_ray(thit);

      if (phit.x() == 0.f && phit.y() == 0.f) phit.x(1e-5f * mImpl->radius);

      phi = atan2f(phit.y(), phit.x());

      if (phi < 0.) phi += 2.f*M_PI;

      // Test against clipping parameters
      if ((mImpl->zmin > -mImpl->radius && phit.z() < mImpl->zmin) ||
        (mImpl->zmax < mImpl->radius && phit.z() > mImpl->zmax) ||
         phi > mImpl->phiMax) {
           if (thit == t1) return false;
           thit = t1;

           if ((mImpl->zmin > -mImpl->radius && phit.z() < mImpl->zmin) ||
             (mImpl->zmax < mImpl->radius && phit.z() > mImpl->zmax) ||
             phi > mImpl->phiMax)
             return false;
         }


      return true;

    }
    bool Sphere::hit(const Ray &ws_ray, float &thit,
                      std::shared_ptr<DifferentialGeometry> &dg) const {
      if (!mImpl->wbbox.intersect(ws_ray)) return false;
      float phi;
      Point phit;

      // Transform the ray into object space
      Ray os_ray = worldToObjectSpace()(ws_ray);



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

      thit = t0;
      if (t0 < os_ray.mint()) {
        thit = t1;
        if (thit > os_ray.maxt()) return false;
      }


      // Compute sphere hit position and phi
      phit = os_ray(thit);

      if (phit.x() == 0.f && phit.y() == 0.f) phit.x(1e-5f * mImpl->radius);

      phi = atan2f(phit.y(), phit.x());

      if (phi < 0.) phi += 2.f*M_PI;

      // Test against clipping parameters
      if ((mImpl->zmin > -mImpl->radius && phit.z() < mImpl->zmin) ||
        (mImpl->zmax < mImpl->radius && phit.z() > mImpl->zmax) ||
         phi > mImpl->phiMax) {
           if (thit == t1) return false;
           thit = t1;

           if ((mImpl->zmin > -mImpl->radius && phit.z() < mImpl->zmin) ||
             (mImpl->zmax < mImpl->radius && phit.z() > mImpl->zmax) ||
             phi > mImpl->phiMax)
             return false;
         }

         // find parametric representation of sphere
         float u = phi/mImpl->phiMax;

         float theta = acosf(Clamp(phit.z()/mImpl->radius, -1.f, 1.f));

         float v = (theta - mImpl->thetaMin) / (mImpl->thetaMax - mImpl->thetaMin);
         float zradius = sqrtf(phit.x() * phit.x() + phit.y() * phit.y());
         float invzradius = 1.f / zradius;
         float cosphi = phit.x() * invzradius;
         float sinphi = phit.y() * invzradius;
         Vector dpdu(-mImpl->phiMax * phit.y(), mImpl->phiMax * phit.x(), 0);
         Vector dpdv = (mImpl->thetaMax - mImpl->thetaMin) *
                Vector(phit.z() * cosphi, phit.z() * sinphi,
                      -mImpl->radius * sinf(theta));

        Vector d2Pduu = -mImpl->phiMax * mImpl->phiMax * Vector(phit.x(), phit.y(), 0.0f);
        Vector d2Pduv = (mImpl->thetaMax - mImpl->thetaMin) * phit.z() * mImpl->phiMax * Vector(-sinphi, cosphi, 0.0f);
        Vector d2Pdvv = -(mImpl->thetaMax - mImpl->thetaMin) * (mImpl->thetaMax - mImpl->thetaMin) * Vector(phit.x(), phit.y(), phit.z());

        float E = dpdu.dot(dpdu);
        float F = dpdu.dot(dpdv);
        float G = dpdv.dot(dpdv);
        Vector N = dpdu.cross(dpdv).normalized();
        float e = N.dot(d2Pduu);
        float f = N.dot(d2Pduv);
        float g = N.dot(d2Pdvv);

        float invEGF2 = 1.f/(E * G - F * F);
        Normal dndu = Normal((f * F - e * G) * invEGF2 * dpdu +
                            (e * F - f * E) * invEGF2 * dpdv);
        Normal dndv = Normal((g * F - f * G) * invEGF2 * dpdu +
                            (f*F - g * E) * invEGF2 * dpdv);




      // if the ray intersects the sphere return true
      std::shared_ptr<DifferentialGeometry> dg_temp(new DifferentialGeometry(ws_ray(thit),
                                objectToWorldSpace()(dpdu),
                                objectToWorldSpace()(dpdv),
                                objectToWorldSpace()(dndu),
                                objectToWorldSpace()(dndv),
                                u, v, this));
      dg = dg_temp;

       return true;

    }
    const BBox Sphere::objectBB() const {
      return BBox(Point(-mImpl->radius, -mImpl->radius, mImpl->zmin),
                  Point(mImpl->radius, mImpl->radius, mImpl->zmax));

    }
    const BBox Sphere::worldBB() const {
      return BBox(objectToWorldSpace()(Point(-mImpl->radius, -mImpl->radius, mImpl->zmin)),
                  objectToWorldSpace()(Point(mImpl->radius, mImpl->radius, mImpl->zmax)));

    }

    const bool Sphere::canIntersect() const {
          return true;
        }


  }
}
