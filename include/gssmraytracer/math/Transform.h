#include <OpenEXR/ImathMatrix.h>
#include <memory>
#include "gssmraytracer/utils/Ray.h"
namespace gssmraytracer {
  namespace math {
    class Transform {
    public:
      Transform(); // default constructor
      Transform(const Transform &); // copy constructor
      Transform& operator=(const Transform &); // assignment operator

      Transform(const Imath::Matrix44<float> transformMatrix);

      Transform inverse();

      void translate(Imath::Vec3<float> translate);
      void rotate(Imath::Vec3<float> rotate);
      void scale(Imath::Vec3<float> scale);

      utils::Ray transform(const utils::Ray &ray);
    private:
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
