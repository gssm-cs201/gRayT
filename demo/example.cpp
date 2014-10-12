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
#include <iostream>

#include "ConstantShader.h"

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
    Camera camera(Point(-5,0,-40),Vector(0,0,1),Vector(0,1,0));
    camera.setAspectRatio(16./9.);
    checker(image, 10, Color(0,0,1,1), Color(1,1,1,1));
    image.write("checker.png");
    stripes(image, 9, Color(1,0,0,1), Color(1,1,1,1));
    image.write("stripes.png");
    image.read("checker.png");
    Transform transform1, transform2;
    Vector position(0.0,0.0,0.0);
    Vector position2(10.,0.0,0.0);
    transform1.translate(position);
    transform2.translate(position2);


    std::shared_ptr<Shader> shader(new ConstantShader(Color(1,0,0,1)));
    std::shared_ptr<Shader> shader2(new ConstantShader(Color(1,1,0,1)));
    Sphere *sphere = new Sphere(transform1, shader, 10.0f, -10.0f, 10.0f, 360.0f);
    Sphere *sphere2 = new Sphere(transform2, shader2, 10.0f, -10.0f, 10.0f, 360.0f);
    RenderGlobals::getInstance().setImage(image);
    RenderGlobals::getInstance().addShape(sphere);
    RenderGlobals::getInstance().addShape(sphere2);
    camera.render(RenderGlobals::getInstance());


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
