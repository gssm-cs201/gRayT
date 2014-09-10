
#include <iostream>
#include <fstream>
#include <gssmraytracer/utils/Color.h>
#include <stdlib.h>
#include <string>
#include <gssmraytracer/utils/Image.h>


namespace gssmraytracer {
namespace utils {
  Image::Image() : width(0), height(0), buffer() {}
  Image::Image(const int w, const int h) : width(w), height(h), buffer() {
    resizeBuffer(width * height);
  //  buffer = new Color[width * height];
  }
  Image::~Image() {
    delete [] buffer;
  }
  Image::Image(const Image &image) : width(image.width), height(image.height), buffer( new Color[width * height]) {

    for (int r = 0; r < height; ++r) {
      for (int c = 0; c < width; ++c) {
        buffer[(r*width) + c] = image.buffer[(r*width) + c];
      }
    }

  }
  Image & Image::operator=(const Image &other) {
    if (this != &other) {
      width = other.width;
      height = other.height;
      resizeBuffer(width * height);
      for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
          buffer[(r*width) + c] = other.buffer[(r*width) + c];
        }
      }
    }
    return *this;
  }

  const int Image::getWidth() const { return width;}

  const int Image::getHeight() const { return height;}

  void Image::setPixel(int r, int c, const Color color) {
    buffer[(r * width) + c] = color;
  }
  const Color Image::getPixel(int r, int c) const{
    return buffer[(r*width) + c];
  }

  void Image::read(const char* filename) {
    std::ifstream file(filename, std::ios::in);
    if (file.is_open()) {
      std::string word;
      file >> word; // P3
      file >> word; // width
      width = std::stoi(word);
      file >> word; // height
      height = std::stoi(word);
      file >> word; // 255

      resizeBuffer(width * height);
      for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
          file >> word;
          buffer[(r*width) + c].red = std::stoi(word);
          file >> word;
          buffer[(r*width) + c].green = std::stoi(word);
          file >> word;
          buffer[(r*width) + c].blue = std::stoi(word);
        }
      }

    }
    file.close();

  }
  void Image::write(const char* filename) {
    std::ofstream file(filename, std::ios::out);
    file << "P3\n" << width << " " << height << "\n" << "255\n";
    for (int r = 0; r < height; ++r) {
      for (int c = 0; c < width; ++c) {
        file << int(buffer[(r*width) + c].red) << " ";

        file << int(buffer[(r*width) + c].green) << " ";

        file << int(buffer[(r*width) + c].blue) << "\t";
      }
      file << "\n";
    }
    file.close();

  }
  const unsigned char* Image::getPixelBuffer() const {
    unsigned char* pixelbuffer = new unsigned char[width * height * 4];
    for (int r = 0; r < height; ++r) {
      for (int c = 0; c < width; ++c ) {

        pixelbuffer[((r*width*4) +c*4)] = (unsigned char)(buffer[(r*width) +c].red);


        pixelbuffer[((r*width*4) +c*4) + 1] = (unsigned char)(buffer[(r*width) +c].green);
        pixelbuffer[((r*width*4) +c*4) + 2] = (unsigned char)(buffer[(r*width) +c].blue);
        pixelbuffer[((r*width*4) +c*4) + 3] = (unsigned char)(buffer[(r*width) +c].alpha);
      }
    }


    return pixelbuffer;
  }
  void Image::resizeBuffer(const int size) {
    // delete the color buffer
    delete [] buffer;
    // create a new color buffer
    buffer = new Color[size];
  }
 }
}
