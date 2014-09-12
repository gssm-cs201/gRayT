#ifndef __RENDERGLOBALS_H__
#define __RENDERGLOBALS_H__

#include <memory>
#include "Image.h"
#include <OpenEXR/ImathVec.h>
namespace gssmraytracer {
  namespace utils {
    class Shape; // forward declaration
    class Ray; // forward declaration
    class RenderGlobals {
    public:
      static RenderGlobals& getInstance();
      void addShape(Shape* shape);
      void setImage(const Image& image);
      const Image getImage() const;
      bool hit(const Ray &ws_ray, float &t0, float &t1,
              Imath::Vec3<float> &hitpoint,
              Imath::Vec3<float> &normal);
      const Color shade(const Ray &ws_ray) const;

    private:
      RenderGlobals(); // default constructor
      RenderGlobals(const RenderGlobals&); // copy constructor
      RenderGlobals& operator=(const RenderGlobals&); // assignment operator
      class Impl;
      std::shared_ptr<Impl> mImpl;

    };
  }
}
#endif // __RENDERGLOBALS_H__
