#include "gssmraytracer/geometry/DifferentialGeometry.h"
namespace gssmraytracer {
  namespace geometry {
    struct Intersection {
      DifferentialGeometry dg;
      const Primitive *primitive;
      Transform worldToObject, objectToWorld;
      uint_32_t shapeId, primitiveId;
      float rayEpsilon;
    };
  }
}
