#include <gssmraytracer/utils/Camera.h>

using namespace gssmraytracer::utils;

void main()
{
 // Create a default camera
 Camera cam;

 // Set the eye, view and up
 cam.setEyeViewUp(Point(-5,0,40),Vector(0,0,-1),Vector(0,1,0));

 // Set the aspect ratio
 cam.setAspectRatio(16./9.);


}
