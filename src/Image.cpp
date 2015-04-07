#include "grayt/utils/Image.h"
#include <OpenImageIO/imageio.h>
#include <OpenImageIO/imagebuf.h>
#include <OpenImageIO/imagebufalgo.h>

namespace grayt {
namespace utils {
class Image::Impl {
public:
  Impl() : width(0), height(0), nchannels(4), pixels() {}
  int width;
  int height;
  int nchannels;
  std::vector<float> pixels;
};

Image::Image() : mImpl(new Impl) {

}

Image::Image(const char *imagename) : mImpl(new Impl) {

  read(imagename);

}

Image::Image(const Image &image) : mImpl(new Impl) {
  mImpl->pixels = image.mImpl->pixels;
  mImpl->width = image.mImpl->width;
  mImpl->height = image.mImpl->height;
  mImpl->nchannels = image.mImpl->nchannels;

}

Image::Image(const int width, const int height, const int numChannels) : mImpl(new Impl) {
  mImpl->width = width;
  mImpl->height = height;
  mImpl->nchannels = numChannels;
  mImpl->pixels.resize(mImpl->width * mImpl->height * mImpl->nchannels);

}

Image& Image::operator=(const Image &other) {
  if (this != &other) {
    mImpl->pixels = other.mImpl->pixels;
    mImpl->width = other.mImpl->width;
    mImpl->height = other.mImpl->height;
    mImpl->nchannels = other.mImpl->nchannels;
  }

  return *this;
}

void Image::read(const char *imagename) {
  OpenImageIO::ImageInput *input = OpenImageIO::ImageInput::open(imagename);
  if (!input) {
    std::cout << "Cannot load image " << imagename << std::endl;
    return;
  }
  const OpenImageIO::ImageSpec &spec = input->spec();
  mImpl->width = spec.width;
  mImpl->height = spec.height;
  mImpl->nchannels = spec.nchannels;
  std::vector<float> pixels
                    (mImpl->width * mImpl->height * mImpl->nchannels);
  input->read_image(OpenImageIO::TypeDesc::FLOAT, &pixels[0]);
  input->close();
  delete input;

  mImpl->pixels = pixels;

}

void Image::write(const char *imagename) {


  OpenImageIO::ImageSpec spec(mImpl->width, mImpl->height,
                              mImpl->nchannels, OpenImageIO::TypeDesc::FLOAT);



  float *buffer = mImpl->pixels.data();
  OpenImageIO::ImageBuf buf(spec, buffer);
  OpenImageIO::ImageBuf out;
  OpenImageIO::ImageBufAlgo::flip(out, buf);
  out.write(std::string(imagename));

}
const float* Image::getPixelBuffer() const {

  return mImpl->pixels.data();
}

const int Image::getWidth() const {
  return mImpl->width;
}

const int Image::getHeight() const {
  return mImpl->height;
}

const int Image::getNumChannels() const {
  return mImpl->nchannels;
}

void Image::setPixel(const int row, const int column, const Color &pixel) {
  mImpl->pixels[mImpl->nchannels*(row * mImpl->width + column)] = pixel.red;
  mImpl->pixels[mImpl->nchannels*(row * mImpl->width + column) + 1] = pixel.green;
  mImpl->pixels[mImpl->nchannels*(row * mImpl->width + column) + 2] = pixel.blue;
  if (mImpl->nchannels == 4)
   mImpl->pixels[mImpl->nchannels*(row * mImpl->width + column) + 3] = pixel.alpha;

}

const Color Image::getPixel(const int row, const int column) const {
  Color result;
  float red, green, blue, alpha;
  red = mImpl->pixels[mImpl->nchannels *(row *mImpl->width + column)];
  green = mImpl->pixels[mImpl->nchannels *(row *mImpl->width + column) + 1];
  blue = mImpl->pixels[mImpl->nchannels *(row *mImpl->width + column) + 2];
  alpha = 1.0;
  if (mImpl->nchannels == 4)
    alpha = mImpl->pixels[mImpl->nchannels *(row *mImpl->width + column) + 3];

  result = Color(red, green, blue, alpha);

  return result;

}

}
}
