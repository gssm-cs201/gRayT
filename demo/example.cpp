#include <gssmraytracer/utils/Camera.h>
#include <gssmraytracer/utils/Scene.h>
#include <gssmraytracer/utils/Color.h>

#include "Image.h"

using namespace gssmraytracer::utils;




int main(void) {
    // Use the default constructor
    Camera cam;
    Scene *scene = gssmraytracer::utils::Scene::Instance();
    delete scene;
    // Create three vectors for the eye, view and up
    const Imath::Vec3<float> eye(0,0,0);
    const Imath::Vec3<float> view(0,0,1);
    const Imath::Vec3<float> up(0,1,0);

    // Use the overloaded constructor
    Camera cam2(eye, view, up);
    int width = 900;
    int height = 900;
    Image image(width, height);
    for (int row = 0; row < height; ++row) {
	for (int col = 0; col < width; ++col) {

		// If the camera hit the sphere, return true, else return false
		image.setPixel(row, col, Color(255,0,0,255));
	}
    }
    image.write("test.ppm");
    image.read("test.ppm");
    image.write("test2.ppm");
    return 0;

}
