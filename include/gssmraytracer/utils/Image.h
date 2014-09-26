#ifndef __IMAGE_H__
#define __IMAGE_H__
#include <memory>
#include "Color.h"
namespace gssmraytracer {
namespace utils {

class Image {
public:
  Image();
  Image(const int width, const int height, const int numChannels=4);
  Image(const char *imagename);
  Image(const Image &image);

  Image& operator=(const Image &other);

  void read(const char *imagename);
  void write(const char *imagename);

  const float* getPixelBuffer() const;
  const int getWidth() const;
  const int getHeight() const;
  const int getNumChannels() const;

  void setPixel(const int row, const int column, const Color &value);

private:
  class Impl;
  std::shared_ptr<Impl> mImpl;

};
}
}
#endif // __IMAGE_H__
