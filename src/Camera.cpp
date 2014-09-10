#include "gssmraytracer/utils/Camera.h"
#include <OpenEXR/ImathVec.h>
#include "gssmraytracer/utils/RenderGlobals.h"
#include "gssmraytracer/utils/Color.h"

namespace gssmraytracer {
namespace utils {

  class Camera::Impl {
  public:
    Imath::Vec3<float> eye;
    Imath::Vec3<float> view;
    Imath::Vec3<float> up;

  };

Camera::Camera(): mImpl(new Impl) {
    mImpl->eye = Imath::Vec3<float>(0,0,0);
    mImpl->view = Imath::Vec3<float>(0,0,1);
    mImpl->up = Imath::Vec3<float>(0,1,0);

}

Camera::Camera(const Imath::Vec3<float> &eye,
               const Imath::Vec3<float> &view,
               const Imath::Vec3<float> &up
              ) : mImpl(new Impl) {
    mImpl->eye = eye;
    mImpl->view = view;
    mImpl->up = up;

}

Camera::~Camera() {

}

void Camera::render(RenderGlobals &renderGlobals) const {
  // try to get image from render globals
  Image image = renderGlobals.getImage();
//  const Scene scene = renderGlobals.getScene();
  for (int r =0; r< image.getHeight(); ++r) {
    for (int c = 0; c < image.getWidth(); ++c) {
      Color color;
//      Ray ray(eye, direction);
//      color = scene.getShade(ray);
      image.setPixel(r,c,color);

    }
  }
  renderGlobals.setImage(image);


}
}
}
