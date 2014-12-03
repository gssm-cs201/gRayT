#include "gssmraytracer/geometry/Triangle.h"
using namespace gssmraytracer::math;
namespace gssmraytracer {
	namespace geometry {
		class Triangle::Impl {
		public:
			Impl(const TriangleMesh *m, const int n) : mesh(m), v() {
				v = mesh->getVertexIndex(n*3);

			}
			const TriangleMesh *mesh;
			int *v;
		};

		void CoordinateSystem(const Vector &v1, Vector *v2, Vector *v3) {
			if (fabs(v1.x() > fabs(v1.y()))) {
				float invLen = 1.f/sqrt(v1.y() * v1.y() + v1.z() * v1.z());
				*v2 = Vector(0.f, v1.z() * invLen, -v1.y() * invLen);
			}
			else {
				float invLen = 1.f / sqrtf(v1.y() * v1.y() + v1.z() * v1.z());
				*v2 = Vector(0.f, v1.z() * invLen, -v1.y() * invLen);
			}
			*v3 = v1.cross(*v2);
		}

		Triangle::Triangle(const Transform &transform, 
						   const TriangleMesh *mesh, 
						   const int n) : Shape(transform), mImpl(new Impl(mesh, n)) {}

		bool Triangle::hit(const utils::Ray &ws_ray, float &tHit) const {
			std::shared_ptr<DifferentialGeometry> dg;

			return hit(ws_ray, tHit, dg);
		}

      
	    bool Triangle::hit(const utils::Ray &ws_ray, float &tHit,
	                        std::shared_ptr<DifferentialGeometry> &dg) const {

	    	const Point &p1 = mImpl->mesh->getVertexPositionArray(mImpl->v[0]);
	    	const Point &p2 = mImpl->mesh->getVertexPositionArray(mImpl->v[1]);
	    	const Point &p3 = mImpl->mesh->getVertexPositionArray(mImpl->v[2]);
	    	// get triangle vertices in p1, p2, and p3

	    	Vector e1 = p2 - p1;
	    	Vector e2 = p3 - p1;
	    	Vector s1 = ws_ray.dir().cross(e2);
	    	float divisor = s1.dot(e1);

	    	if (divisor == 0.)
	    		return false;
	    	float invDivisor = 1.f / divisor;

	    	// compute first barycentric coordinate
	    	Vector d = ws_ray.origin() - p1;
	    	float b1 = d.dot(s1) * invDivisor;
	    	if (b1 < 0. || b1 > 1.)
	    		return false;

	    	// compute second barycentric coordinate
	    	Vector s2 = d.cross(e1);
	    	float b2 = ws_ray.dir().dot(s2) * invDivisor;

	    	if (b2 < 0. || b1 + b2 > 1.)
	    		return false;

	    	// Compute t to intersection point
	    	float t = e2.dot(s2) * invDivisor;
	    	if (t < ws_ray.mint() || t > ws_ray.maxt())
	    		return false;

	    	// compute triangle partial derivative
	    	Vector dpdu, dpdv;
	    	float uvs[3][2];
	    	getUVs(uvs);

	    	// compute deltas for triangle partial derivatives
	    	float du1 = uvs[0][0] - uvs[2][0];
	    	float du2 = uvs[1][0] - uvs[2][0];
	    	float dv1 = uvs[0][1] - uvs[2][1];
	    	float dv2 = uvs[1][1] - uvs[2][1];
	    	Vector dp1 = p1 - p3, dp2 = p2 - p3;

	    	float determinant = du1 * dv2 - dv1 * du2;
	    	if (determinant == 0.f) {
	    		// handle zero determinants for triangle partial derivative matrix
	    	}
	    	else {
	    		float invdet = 1.f/determinant;
	    		dpdu = (dv2 * dp1 - dv1 * dp2) * invdet;
	    		dpdv = (-du2 * dp1 + du1 * dp2) * invdet;
	    	}

	    	

	    	CoordinateSystem(e2.cross(e1).normalized(), &dpdu, &dpdv);

	    	// interpolate (u,v) triangle parametric coordinates
	    	float b0 = 1 - b1 - b2;
	    	float tu = b0 * uvs[0][0] + b1*uvs[1][0] + b2*uvs[2][0];
	    	float tv = b0 * uvs[0][1] + b1*uvs[1][1] + b2*uvs[2][1];

	    	tHit = t;
	    	std::shared_ptr<DifferentialGeometry> dg_temp(new DifferentialGeometry(ws_ray(t), dpdu, dpdv, Normal(0,0,0), Normal(0,0,0),
	    		tu, tv, this));

	    	dg = dg_temp;
	    	return true;

	    }

	    void Triangle::getUVs(float uv[3][2]) const {
	    	if (mImpl->mesh->getUVs()) {
	    		uv[0][0] = mImpl->mesh->getUVs()[2 * mImpl->v[0]];
	    		uv[0][1] = mImpl->mesh->getUVs()[2 * mImpl->v[0] + 1];
	    		uv[1][0] = mImpl->mesh->getUVs()[2 * mImpl->v[1]];
	    		uv[1][1] = mImpl->mesh->getUVs()[2 * mImpl->v[1] + 1];
	    		uv[2][0] = mImpl->mesh->getUVs()[2 * mImpl->v[2]];
	    		uv[2][1] = mImpl->mesh->getUVs()[2 * mImpl->v[2] + 1];
	    	}
	    	else {
	    		uv[0][0] = 0.; uv[0][1] = 0.;
	    		uv[1][0] = 1.; uv[1][1] = 0.;
	    		uv[2][0] = 1.; uv[2][1] = 1.;
	    	}
	    }

		      //! returns the bounding box of the shape in world space
		    const BBox Triangle::worldBB() const {
		    	const Point &p1 = mImpl->mesh->getVertexPositionArray(mImpl->v[0]);
		    	const Point &p2 = mImpl->mesh->getVertexPositionArray(mImpl->v[1]);
		    	const Point &p3 = mImpl->mesh->getVertexPositionArray(mImpl->v[2]);

		    	BBox bbox(p1, p2);
		    	bbox.combine(p3);

		    	return bbox;
		    }

		      //! returns the bounding box of the shape in object space
		    const BBox Triangle::objectBB() const {
		    	const Point &p1 = mImpl->mesh->getVertexPositionArray(mImpl->v[0]);
		    	const Point &p2 = mImpl->mesh->getVertexPositionArray(mImpl->v[1]);
		    	const Point &p3 = mImpl->mesh->getVertexPositionArray(mImpl->v[2]);

		    	BBox bbox(worldToObjectSpace()(p1), worldToObjectSpace()(p2));
		    	bbox.combine(worldToObjectSpace()(p3));


		    	return bbox;
		    }

		    const bool Triangle::canIntersect() const {
		    	return true;
		    }
	}
}