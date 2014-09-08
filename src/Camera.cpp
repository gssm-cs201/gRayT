#include "gssmraytracer/utils/Camera.h"
#include <OpenEXR/ImathVec.h>

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


}
}
