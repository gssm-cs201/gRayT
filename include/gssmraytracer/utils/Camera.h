#include <OpenEXR/ImathVec.h>
#include <memory>

namespace gssmraytracer {
namespace utils {
    class RenderGlobals; // forward declaration
    class Camera {
    public:
    // Default Constructor
    Camera();
    // Set eye, view and up vectors
    Camera(const Imath::Vec3<float> &eye, const Imath::Vec3<float> &view, const Imath::Vec3<float> &up);
    ~Camera();
    void render(const RenderGlobals &renderGlobals);

    private:
    class Impl;
    std::shared_ptr<Impl> mImpl;

    };
}

}
