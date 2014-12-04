#include <gssmraytracer/utils/Camera.h>
#include <gssmraytracer/utils/Scene.h>
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Shader.h>
#include <gssmraytracer/math/Vector.h>
#include <memory>
#include <gssmraytracer/geometry/Sphere.h>
#include <gssmraytracer/geometry/TriangleMesh.h>
#ifdef _OPENMP
#  include <omp.h>
#endif


#ifdef __APPLE__
#  include <GLUT/glut.h>
#else
#  include <GL/glut.h>
#endif


#include <gssmraytracer/utils/Image.h>
#include <gssmraytracer/utils/RenderGlobals.h>
#include <gssmraytracer/utils/Color.h>
#include <gssmraytracer/utils/Scene.h>
#include <gssmraytracer/utils/CmdLineFind.h>
#include <iostream>

#include "ConstantShader.h"
#include "NormalShader.h"
#include "ImageShader.h"
#include "NoiseShader.h"
#include "LambertianShader.h"
#include "PhongShader.h"

#include <iostream>

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

void test(const Point *P) {
  std::cout << P[0] << std::endl;
}

int main(int argc, char* argv[]) {
    // Use the default constructor
    CmdLineFind clf(argc, argv);

    int width  = clf.find( "-NX", 640, "Image width");
    int height = clf.find( "-NY", 360, "Image height");
    int num_width_samples = clf.find("-SX", 1, "Width Samples");
    int num_height_samples = clf.find("-SY", 1, "Height Samples");
    std::string filename = clf.find( "-name", "demo.exr", "Name of output image file" );
    int num_threads = clf.find("-threads", omp_get_max_threads(), "Max number of threads");
    int num_frames = clf.find("-nframes", 200, "Maximum number of frames for turntable");
    int frame = clf.find("-frame", 0, "Render frame");
    float radius = clf.find("-radius", 25, "Radius distance from center"); 
    bool display_image = clf.find("-display", 0, "Display the image");
    float cx = clf.find("-CX", 0.f, "Center x");
    float cy = clf.find("-CY", 2.5f, "Center y");
    float cz = clf.find("-CZ", 0.f,"Center z");
    clf.printFinds();
    clf.usage("-h");
    omp_set_num_threads((num_threads > 0) ? num_threads : 1 );
    Image image(width, height);

    Point center(cx,cy,cz);
    float theta = float(frame)/float(num_frames) * 2.0 * M_PI;
    float x_pos = center.x() + radius * cos(theta);
    float z_pos = center.z() + radius * sin(theta);
    float x_view = -cos(theta);
    float z_view = -sin(theta);

//    Camera camera(Point(-5,2.5,25),Vector(0,0,-1),Vector(0,1,0));
    Camera camera(Point(x_pos,center.y(),z_pos),Vector(x_view,0,z_view),Vector(0,1,0));

    Image image2("fractal3.png");
    Scene &scene = Scene::getInstance();
    scene.maxBounceCount(5);
    Transform transform1, transform2, transform3, transform4, transform5, transform6;
    Vector position(-16.0,2.0,0.0);
    Vector position2(-3.0,-3.0,-8.0);
    Vector position3(-1.0,5.0,-3.0);
    Vector position4(0.0,-1.0,0.0);
    Vector position5(1.0,4.0,8.0);
    Vector position6(0.0,0.0,0.0);
    transform1.translate(position);
    transform2.translate(position2);
    transform3.translate(position3);
    transform4.translate(position4);
    transform5.translate(position5);
    transform5.translate(position6);

    Point points[8];
    int v_indices[12*3];
    Normal v_normals[12*3];
    points[0] = Point(-0.5,-0.5,0.5);
    points[1] = Point(0.5,-0.5,0.5);
    points[2] = Point(-0.5,0.5,0.5);
    points[3] = Point(0.5,0.5,0.5);
    points[4] = Point(-0.5,0.5,-0.5);
    points[5] = Point(0.5,0.5,-0.5);
    points[6] = Point(-0.5,-0.5,-0.5);
    points[7] = Point(0.5,-0.5,-0.5);

    v_indices[0] = 0;
    v_indices[1] = 1;
    v_indices[2] = 2;

    v_indices[3] = 2;
    v_indices[4] = 1;
    v_indices[5] = 3;

    v_indices[6] = 2;
    v_indices[7] = 3;
    v_indices[8] = 4;

    v_indices[9] = 4;
    v_indices[10] = 3;
    v_indices[11] = 5;

    v_indices[12] = 4;
    v_indices[13] = 5;
    v_indices[14] = 6;

    v_indices[15] = 6;
    v_indices[16] = 5;
    v_indices[17] = 7;

    v_indices[18] = 6;
    v_indices[19] = 7;
    v_indices[20] = 0;

    v_indices[21] = 0;
    v_indices[22] = 7;
    v_indices[23] = 1;

    v_indices[24] = 1;
    v_indices[25] = 7;
    v_indices[26] = 3;

    v_indices[27] = 3;
    v_indices[28] = 7;
    v_indices[29] = 5;

    v_indices[30] = 6;
    v_indices[31] = 0;
    v_indices[32] = 4;

    v_indices[33] = 4;
    v_indices[34] = 0;
    v_indices[35] = 2;
    int numTriangles = 12;
    int numVertices = 8;

    v_normals[0] = Normal(0,0,1);
    v_normals[1] = Normal(0,0,1);
    v_normals[2] = Normal(0,0,1);

    v_normals[3] = Normal(0,0,1);
    v_normals[4] = Normal(0,0,1);
    v_normals[5] = Normal(0,0,1);

    v_normals[6] = Normal(0,1,0);
    v_normals[7] = Normal(0,1,0);
    v_normals[8] = Normal(0,1,0);

    v_normals[9] = Normal(0,1,0);
    v_normals[10] = Normal(0,1,0);
    v_normals[11] = Normal(0,1,0);

    v_normals[12] = Normal(0,0,-1);
    v_normals[13] = Normal(0,0,-1);
    v_normals[14] = Normal(0,0,-1);

    v_normals[15] = Normal(0,0,-1);
    v_normals[16] = Normal(0,0,-1);
    v_normals[17] = Normal(0,0,-1);

    v_normals[18] = Normal(0,-1,0);
    v_normals[19] = Normal(0,-1,0);
    v_normals[20] = Normal(0,-1,0);

    v_normals[21] = Normal(0,-1,0);
    v_normals[22] = Normal(0,-1,0);
    v_normals[23] = Normal(0,-1,0);

    v_normals[24] = Normal(1,0,0);
    v_normals[25] = Normal(1,0,0);
    v_normals[26] = Normal(1,0,0);

    v_normals[27] = Normal(1,0,0);
    v_normals[28] = Normal(1,0,0);
    v_normals[29] = Normal(1,0,0);

    v_normals[30] = Normal(-1,0,0);
    v_normals[31] = Normal(-1,0,0);
    v_normals[32] = Normal(-1,0,0);

    v_normals[33] = Normal(-1,0,0);
    v_normals[34] = Normal(-1,0,0);
    v_normals[35] = Normal(-1,0,0);



    std::shared_ptr<Shader> shader(new PhongShader(Color(0,1,0,1)));
    shader->reflectivity(0.5);
    std::shared_ptr<Shader> shader2(new PhongShader(Color(1,0,0,1)));
    shader2->reflectivity(0.5);
    std::shared_ptr<Shader> shader3(new PhongShader(Color(1,1,0,1)));
    shader3->reflectivity(0.5);
    std::shared_ptr<Shader> shader4(new PhongShader(Color(0,0,1,1)));
    shader4->reflectivity(0.5);
    std::shared_ptr<Shader> shader5(new PhongShader(Color(0,1,0,1)));
    shader5->reflectivity(0.5);
    std::shared_ptr<Shader> shader6(new PhongShader(Color(1,0.3,0,1)));
    shader6->reflectivity(0.5);
    BBox bbox;
    std::shared_ptr<Sphere> sphere(new Sphere(transform1, false, 4.0f, -10.0f, 10.0f, 360.0f));

    std::shared_ptr<Sphere> sphere2(new Sphere(transform2, false, 2.0f, -10.0f, 10.0f, 360.0f));
    std::shared_ptr<Sphere> sphere3(new Sphere(transform3, false, 2.0f, -10.0f, 10.0f, 360.0f));
    std::shared_ptr<Sphere> sphere4(new Sphere(transform4, false, 3.0f, -10.0f, 10.0f, 360.0f));
    std::shared_ptr<Sphere> sphere5(new Sphere(transform5, false, 2.0f, -10.0f, 10.0f, 360.0f));

    std::shared_ptr<Shape> mesh(new TriangleMesh(transform6, false, numTriangles, numVertices, v_indices, points, v_normals));

    std::shared_ptr<Primitive> prim (new Primitive(sphere, shader));
    std::shared_ptr<Primitive> prim2(new Primitive(sphere2, shader2));
    std::shared_ptr<Primitive> prim3(new Primitive(sphere3, shader3));
    std::shared_ptr<Primitive> prim4(new Primitive(sphere4, shader4));
    std::shared_ptr<Primitive> prim5(new Primitive(sphere5, shader5));
    std::shared_ptr<Primitive> prim6(new Primitive(mesh, shader6));

    //scene.addPrimitive(prim);
    //scene.addPrimitive(prim2);
    //scene.addPrimitive(prim3);
    //scene.addPrimitive(prim4);
    //scene.addPrimitive(prim5);
    scene.addPrimitive(prim6);
    scene.init();
    camera.render(scene, image, num_width_samples, num_height_samples);
    image.write(filename.c_str());
    RenderGlobals::getInstance().setImage(image);

    if (display_image) {
    // start up the glut utilities
    glutInit(&argc, argv);

    // create the graphics window, giving width, height, and title text
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);


    glutInitWindowSize(width, height);

    glutCreateWindow("Image");

    glutDisplayFunc(display_picture);

    glutKeyboardFunc(handle_key);

    glutMainLoop();
    }

    return 0;

}
