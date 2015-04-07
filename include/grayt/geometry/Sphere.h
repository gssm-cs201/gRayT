#include <grayt/geometry/Shape.h>
#include <grayt/math/Transform.h>
#include <memory>

namespace grayt {
  namespace geometry {
    class Sphere : public Shape {
    public:
      Sphere(const math::Transform &transform, const bool reverseOrientation, const float radius);
      Sphere (const math::Transform &transform, const bool reverseOrientation,
                          const float radius, float z0, float z1, float pm=360.0f);
      bool hit(const utils::Ray &ws_ray, float &tHit) const;
      bool hit(const utils::Ray &ws_ray, float &tHit,
               std::shared_ptr<DifferentialGeometry> &dg) const;
      const BBox worldBB() const;
      const BBox objectBB() const;
      virtual ~Sphere();

      const bool canIntersect() const;
      
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}