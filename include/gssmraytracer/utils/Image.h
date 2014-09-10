#ifndef __IMAGE_H__
#define __IMAGE_H__




namespace gssmraytracer {
namespace utils {
class Color; // forward declaration
class Image {
public:
  Image();
  Image(const int w, const int h);
  ~Image();
  Image(const Image &image);
  Image & operator=(const Image &other);

  const int getWidth() const;

  const int getHeight() const;

  void setPixel(int r, int c, const Color color);

  const Color getPixel(int r, int c) const;

  void read(const char* filename);
  void write(const char* filename);
  const unsigned char* getPixelBuffer() const;

private:
  void resizeBuffer(const int size);

  int width;
  int height;
  Color *buffer;


};
}
}
#endif // __IMAGE_H__
