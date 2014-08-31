#include <gssmraytracer/utils/Camera.h>

int main(void) {
    // Use the default constructor
    gssmraytracer::utils::Camera cam;

    // Create three vectors for the eye, view and up
    const Imath::Vec3<float> eye(0,0,0);
    const Imath::Vec3<float> view(0,0,1);
    const Imath::Vec3<float> up(0,1,0);

    // Use the overloaded constructor
    gssmraytracer::utils::Camera cam2(eye, view, up);

    return 0;

}
