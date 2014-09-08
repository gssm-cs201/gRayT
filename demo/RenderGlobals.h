#ifndef __RENDERGLOBALS_H__
#define __RENDERGLOBALS_H__

#include <memory>
#include "Image.h"
namespace gssmraytracer {
  namespace utils {
    class Shape; // forward declaration
    class RenderGlobals {
    public:
      static RenderGlobals& getInstance();
      void addShape(const Shape& shape);
      void setImage(const Image& image);
      const Image& getImage();
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
