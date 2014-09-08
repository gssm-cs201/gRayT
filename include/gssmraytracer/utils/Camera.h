#include <OpenEXR/ImathVec.h>
#include <memory>

namespace gssmraytracer {
namespace utils {
    class Camera {
    public:
    // Default Constructor
    Camera();
    // Set eye, view and up vectors
    Camera(const Imath::Vec3<float> &eye, const Imath::Vec3<float> &view, const Imath::Vec3<float> &up);

    ~Camera();

    private:
    class Impl;
    std::shared_ptr<Impl> mImpl;

    };
}

}
