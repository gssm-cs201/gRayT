#include "grayt/geometry/DifferentialGeometry.h"
namespace grayt {
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
