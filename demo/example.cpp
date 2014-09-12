#include <gssmraytracer/utils/Camera.h>
#include <gssmraytracer/utils/Scene.h>
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Shader.h>
#include <memory>
#include "Sphere.h"



#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


#include <gssmraytracer/utils/Image.h>
#include <gssmraytracer/utils/RenderGlobals.h>
#include <iostream>

#include "ConstantShader.h"

using namespace gssmraytracer::utils;


void display_picture() {
  const Image image = RenderGlobals::getInstance().getImage();
  const unsigned char *pixmap = image.getPixelBuffer();
  glClearColor(0 , 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT);
  glDrawPixels(image.getWidth(), image.getHeight(), GL_RGBA, GL_UNSIGNED_BYTE, (void *)pixmap);
  glFlush();
  delete [] pixmap;


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
        image.setPixel(row, col, Color(sin(normalized*2 * M_PI) * 255,255,0,255));
    }
  }
}

int main(int argc, char* argv[]) {
    // Use the default constructor

    int width = 500;
    int height = 500;
    Image image(width, height);
    Camera camera(Imath::Vec3<float>(0,0,-40),Imath::Vec3<float>(0,0,1),Imath::Vec3<float>(0,1,0));
    camera.setAspectRatio(1.0);
    checker(image, 10, Color(0,0,255,255), Color(255,255,255,255));
    image.write("checker.ppm");
    stripes(image, 9, Color(255,0,0,255), Color(255,255,255,255));
    image.write("stripes.ppm");
    image.read("checker.ppm");
//    image.write("test2.ppm");
    Imath::Vec3<float> position(0.0,0.3,0.0);
    std::shared_ptr<Shader> shader(new ConstantShader(Color(255,255,0,255)));
    Sphere *sphere = new Sphere(position, shader, 3.0);
    RenderGlobals::getInstance().setImage(image);
    RenderGlobals::getInstance().addShape(sphere);
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
