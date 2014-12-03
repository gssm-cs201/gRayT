#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__
#include "gssmraytracer/geometry/TriangleMesh.h"
namespace gssmraytracer {
	namespace geometry {
		class Triangle : public Shape {
		public:
			Triangle(const math::Transform &transform, 
						   const TriangleMesh *mesh, 
						   const int n);

			bool hit(const utils::Ray &ws_ray, float &tHit) const;

      
		    bool hit(const utils::Ray &ws_ray, float &tHit,
		                        std::shared_ptr<DifferentialGeometry> &dg) const;

		    void getUVs(float uv[3][2]) const;

		      //! returns the bounding box of the shape in world space
		    const BBox worldBB() const;

		      //! returns the bounding box of the shape in object space
		    const BBox objectBB() const;

		    const bool canIntersect() const;

		private:
			class Impl;
			std::shared_ptr<Impl> mImpl;
			Triangle& operator=(const Triangle &);
			Triangle(const Triangle &);
		};
	}
}
#endif // __TRIANGLE_H__