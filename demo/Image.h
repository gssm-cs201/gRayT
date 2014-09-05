#include <iostream>
#include <fstream>
#include <gssmraytracer/utils/Color.h>
#include <stdlib.h>
#include <string>

using namespace gssmraytracer::utils;
class Image {
public:
  Image(int w, int h) : width(w), height(h) {
    buffer = new Color[width * height];
  }
  ~Image() {
    delete [] buffer;
  }
  void setPixel(int r, int c, const Color color) {
    buffer[(r * width) + c] = color;
  }
  Color getPixel(int r, int c) {
    return buffer[(r*width) + c];
  }
  void resizeBuffer(const int size) {
    delete [] buffer;
    buffer = new Color[size];
  }
  void read(const char* filename) {
    std::ifstream file(filename, std::ios::in);
    if (file.is_open()) {
      std::string word;
      file >> word; // P3
      file >> word; // width
      width = std::stoi(word);
      std::cout << width << std::endl;
      file >> word; // height
      height = std::stoi(word);
      std::cout << height << std::endl;
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
  void write(const char* filename) {
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
private:
  int width;
  int height;
  Color *buffer;


};
