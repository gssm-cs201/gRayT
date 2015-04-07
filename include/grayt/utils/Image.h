#ifndef __IMAGE_H__
#define __IMAGE_H__
#include <memory>
#include "Color.h"
namespace grayt {
namespace utils {

class Image {
public:
  //! Creates an image with width, height and the number of channels set to 0.
  Image();

  /*! \brief creates image with provided width, height and number of channels.
   *
   * Creates an image with the provided width, height and number of channels.
   * If the number of channels are not provided, it defaults to 4.
   */
  Image(const int width, const int height, const int numChannels=4);

  /*! \brief initialized class with an image file.
   * Initializes the width, height and number of channels based on the
   * input image.
   */
  Image(const char *imagename);

  //! Copy Constructor for Image class.
  Image(const Image &image);

  //! Assignment operator for Image class.
  Image& operator=(const Image &other);

  /*! \brief reads a file to load an Image.
   */
  void read(const char *imagename);

  /*! \brief writes the Image to a file.
   *
   * Writes an Image to disk based on the filename and extension.
   */
  void write(const char *imagename);

  /* \brief returns the raw pixel data as a 1D array.
   */
  const float* getPixelBuffer() const;

  //! get Image width.
  const int getWidth() const;

  //! get Image height.
  const int getHeight() const;

  //! get the number of color channels in the Image.
  const int getNumChannels() const;

  //! set a certain pixel to a Color.
  void setPixel(const int row, const int column, const Color &value);

  //! get a Color from a pixel.
  const Color getPixel(const int row, const int column) const;

private:
  class Impl;
  std::shared_ptr<Impl> mImpl;

};
}
}
#endif // __IMAGE_H__
