#include <gssmraytracer/utils/Camera.h>
#include <gssmraytracer/utils/Scene.h>
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Shader.h>
#include <gssmraytracer/math/Vector.h>
#include <memory>
#include "Sphere.h"



#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


#include <gssmraytracer/utils/Image.h>
#include <gssmraytracer/utils/RenderGlobals.h>
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Scene.h>
#include <iostream>

#include "ConstantShader.h"
#include "NormalShader.h"
#include "ImageShader.h"
#include "NoiseShader.h"
#include "LambertianShader.h"
#include "PhongShader.h"

using namespace gssmraytracer::utils;
using namespace gssmraytracer::geometry;
using namespace gssmraytracer::math;

void display_picture() {
  const Image image = RenderGlobals::getInstance().getImage();
  const float *pixmap = image.getPixelBuffer();
  glClearColor(0 , 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(image.getWidth(), image.getHeight(), GL_RGBA, GL_FLOAT, (void *)pixmap);
  glFlush();


}

void handle_key(unsigned char key, int x, int y) {
   switch(key){
        case 'w':
        case 'W':
        //    writeimage();
            break;

        case 'r':
        case 'R':
      //      readImage();
      //      glutReshapeWindow(image.columns(), image.rows());
      //      glutPostRedisplay();
            break;

        case 'q':               // q - quit
        case 'Q':
        case 27:                // esc - quit
            exit(0);

        default:                // not a valid key -- just ignore it
            return;
    }


}

void checker(Image &image, const int num_squares, const Color color1, const Color color2) {

  int square_width = image.getWidth()/num_squares;
  for (int row = 0; row < image.getHeight(); ++row) {
    for (int col = 0; col < image.getWidth(); ++col) {
      if ((col/square_width + row/square_width) % 2 == 0) {
        image.setPixel(row, col, color1);
      }
      else {
        image.setPixel(row, col, color2);
      }

    }
  }
}

void stripes(Image &image, int num_stripes, Color color1, Color color2) {

  int stripe_width = image.getWidth()/num_stripes;
  for (int row = 0; row < image.getHeight(); ++row) {
    for (int col = 0; col < image.getWidth(); ++col) {
      if ((col/stripe_width) %2 == 0) {
        image.setPixel(row, col, color1);
      }
      else {
        image.setPixel(row, col, color2);
      }

    }
  }
}

void gradient(Image &image) {

  for (int row = 0; row < image.getHeight(); ++row) {
    for (int col = 0; col < image.getWidth(); ++col) {
      float normalized = (float)col/image.getWidth()/4.0;
        image.setPixel(row, col, Color(sin(normalized*2 * M_PI) * 1,1,0,1));
    }
  }
}

int main(int argc, char* argv[]) {
    // Use the default constructor

    int width = 640;
    int height = 360;
    Image image(width, height);
    Camera camera(Point(0,0,40),Vector(0,0,-1),Vector(0,1,0));

    Image image2("fractal3.png");
    Scene &scene = Scene::getInstance();
    Transform transform1, transform2, transform3;
    Vector position(-7.0,0.0,6.0);
    Vector position2(7.0,4.0,0.0);
    Vector position3(1.0,0.0,1.0);
    transform1.translate(position);
    transform2.translate(position2);
    transform3.translate(position3);


    std::shared_ptr<Shader> shader(new PhongShader(Color(0,1,0,1)));
    std::shared_ptr<Shader> shader2(new LambertianShader(Color(1,0,0,1)));
    std::shared_ptr<Shader> shader3(new LambertianShader(Color(1,1,0,1)));
    BBox bbox;
    std::shared_ptr<Sphere> sphere(new Sphere(transform1,5.0f, -10.0f, 10.0f, 360.0f));

    std::shared_ptr<Sphere> sphere2(new Sphere(transform2, 5.0f, -10.0f, 10.0f, 360.0f));
    std::shared_ptr<Sphere> sphere3(new Sphere(transform3, 5.0f, -10.0f, 10.0f, 360.0f));

    std::shared_ptr<Primitive> prim(new Primitive(sphere, shader));
    std::shared_ptr<Primitive> prim2(new Primitive(sphere2, shader2));
    std::shared_ptr<Primitive> prim3(new Primitive(sphere3, shader3));

    scene.addPrimitive(prim);
    scene.addPrimitive(prim2);
    scene.addPrimitive(prim3);
    camera.render(scene, image);
    image.write("lambertianShader.exr");
    RenderGlobals::getInstance().setImage(image);


    // start up the glut utilities
    glutInit(&argc, argv);

    // create the graphics window, giving width, height, and title text
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);


    glutInitWindowSize(width, height);

    glutCreateWindow("Image");

    glutDisplayFunc(display_picture);

    glutKeyboardFunc(handle_key);

    glutMainLoop();


    return 0;

}
