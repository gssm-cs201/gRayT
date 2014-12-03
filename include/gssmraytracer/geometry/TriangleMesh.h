#ifndef __TRIANGLE_MESH_H__
#define __TRIANGLE_MESH_H__
#include <memory>
#include <vector>
#include "gssmraytracer/math/Vector.h"
#include "gssmraytracer/math/Transform.h"
#include "gssmraytracer/geometry/Point.h"
#include "gssmraytracer/geometry/Normal.h"
#include "gssmraytracer/geometry/Shape.h"
namespace gssmraytracer {
	namespace geometry {
	class TriangleMesh : public Shape {
	public:
		TriangleMesh(const math::Transform &t, 
						int numTriangles,
						int numVertices,
						const int *vertexIndices,
						const Point *P, // array of vertex positions
						const Normal *N = nullptr, // optional array of normal vectors (one per vertex)
						const math::Vector *S = nullptr, // optional array of tangent vectors (one per vertex)
						const float *uv = nullptr // optional array of u v values, one per vertex
					);


		//! hit will return false for TriangleMesh
		bool hit(const utils::Ray &ws_ray, float &tHit) const;

      	//! hit will return false for TriangleMesh
      	bool hit(const utils::Ray &ws_ray, float &tHit,
                        std::shared_ptr<DifferentialGeometry> &dg) const;

		//! returns the bounding box of the shape in world space
      const BBox worldBB() const;

      //! returns the bounding box of the shape in object space
      const BBox objectBB() const;

      const bool canIntersect() const;

      void refine(std::vector<std::shared_ptr<Shape> > &refined) const;

      int* getVertexIndex(const int n) const;

      const Point& getVertexPositionArray(const int n) const;

      const float* getUVs() const;

	private:
		class Impl;
		std::shared_ptr<Impl> mImpl;
		TriangleMesh(const TriangleMesh &);
		TriangleMesh& operator=(const TriangleMesh &);
	};
	}
}
#endif // __TRIANGLE_MESH_H__