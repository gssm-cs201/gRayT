#include "gssmraytracer/geometry/TriangleMesh.h"
#include <cstring>
#include "gssmraytracer/geometry/Triangle.h"
#include <assert.h>

using namespace gssmraytracer::math;

namespace gssmraytracer {
	namespace geometry {
		class TriangleMesh::Impl {
		public:
			Impl(const int numTriangles, 
				const int numVertices, 
				const int *vertexIndices, 
				const Point *P,
				const bool ro) : ntris(numTriangles), nverts(numVertices), p(nullptr), n(nullptr), s(nullptr), uvs(nullptr), reverseOrientation(ro) {
				vertexIndex = new int[3 * ntris];
				for (int i = 0; i < 3 * ntris; ++i) {
					vertexIndex[i] = vertexIndices[i];
				}
			}
			~Impl() {
				delete [] vertexIndex;
				delete [] p;
			}
			int ntris, nverts;
			int *vertexIndex;
			Point *p;
			Normal *n;
			Vector *s;
			float *uvs;
			bool reverseOrientation;

		};

		TriangleMesh::TriangleMesh(const Transform &transform,
									const bool reverseOrientation,
									const int numTriangles,
									const int numVertices,
									const int *vertexIndices,
									const Point *P,
									const Normal *N,
									const Vector *S,
									const float *uv) : Shape(transform, reverseOrientation), mImpl(new Impl(numTriangles, numVertices, vertexIndices, P, reverseOrientation)) {

			// copy uv, N and S vertex data if present

			// transform vertices to world space
			mImpl->p = new Point[mImpl->nverts];
			for (int i = 0; i < mImpl->nverts; ++i) {
					mImpl->p[i] = objectToWorldSpace()(P[i]);
				}
			if (N) {
				mImpl->n = new Normal[mImpl->ntris * 3];
				for (int i = 0; i < mImpl->ntris * 3; ++i) {
					mImpl->n[i] = objectToWorldSpace()(N[i]);
				}
			}
			if (S) {
				mImpl->s = new Vector[mImpl->ntris * 3];
				for (int i = 0; i < mImpl->ntris * 3; ++i) {
					mImpl->s[i] = objectToWorldSpace()(S[i]);
				}
			}

		}

		bool TriangleMesh::hit(const utils::Ray &ws_ray, float &tHit) const { return false;}

      /* \brief virtual function for hit with DifferentialGeometry
       *
       * Does what the hit above describes plus also returns a smart pointer
       * to a DifferentialGeometry object
       */
      bool TriangleMesh::hit(const utils::Ray &ws_ray, float &tHit,
                        std::shared_ptr<DifferentialGeometry> &dg) const { return false;}

		const BBox TriangleMesh::worldBB() const {
			BBox worldBounds;
			for (int i = 0; i < mImpl->nverts; ++i) {
				worldBounds = worldBounds.combine(mImpl->p[i]);
			}
			return worldBounds;
		}

		const BBox TriangleMesh::objectBB() const {
			BBox objectBounds;

			for (int i = 0; i < mImpl->nverts; ++i) {
				objectBounds = objectBounds.combine(worldToObjectSpace()(mImpl->p[i]));
			}

			return objectBounds;
		}

		void TriangleMesh::refine(std::vector<std::shared_ptr<Shape> > &refined) const {

			for (int i = 0; i < mImpl->ntris; ++i) {
				
				std::shared_ptr<Triangle> triangle(new Triangle(objectToWorldSpace(), mImpl->reverseOrientation, this, i));
				refined.push_back(triangle);
			}
		}

		const bool TriangleMesh::canIntersect() const { return false;}

		int* TriangleMesh::getVertexIndex(const int n) const {
			if (n < 0 && n >= 3*mImpl->ntris) {
				std::cout << "Invalid vertex index!" << std::endl;
			}
			assert(n >= 0 && n < 3*mImpl->ntris);
			return &mImpl->vertexIndex[n];
		}

		const Point& TriangleMesh::getVertexPositionArray(const int n) const {

			return mImpl->p[n];

		}

		const float* TriangleMesh::getUVs() const {
			return mImpl->uvs;
		}

		const Normal* TriangleMesh::n() const {
			return mImpl->n;
		}
		
		const Vector* TriangleMesh::s() const {
			return mImpl->s;
		}	
			


	}
}