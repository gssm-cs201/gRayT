#ifndef __RENDERGLOBALS_H__
#define __RENDERGLOBALS_H__

#include <memory>
#include "Image.h"
#include <OpenEXR/ImathVec.h>
#include "gssmraytracer/geometry/Shape.h"
namespace gssmraytracer {
  namespace utils {
    class Ray; // forward declaration
    class RenderGlobals {
    public:
      //! Gets an instance of the Singleton
      static RenderGlobals& getInstance();

      //! Adds a shape to RenderGlobals
      void addShape(geometry::Shape* shape);

      //! passes an image to RenderGlobals
      void setImage(const Image& image);

      //! retrieves the image held by RenderGlobals
      const Image getImage() const;

      /*! \brief determines if a ray hits an object in the scene
       *
       * If a ray hits an object, it returns true, as well as sets
       * thit to the hit time for the ws_ray and returns DifferentialGeometry
       * information for shading.
       */
      bool hit(const Ray &ws_ray, float &thit,
                      std::shared_ptr<geometry::DifferentialGeometry> &dg);

      //! Returns a color based on the ray hit position from shading.
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
