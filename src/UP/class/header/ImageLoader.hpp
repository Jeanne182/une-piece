#ifndef UP_IMAGE_LOADER_HPP__
#define UP_IMAGE_LOADER_HPP__

namespace UP {
  class ImageLoader {
      ImageLoader();
      ImageLoader(const FilePath& appPath,
                  unsigned int& width,
                  unsigned int& height);
      ~ImageLoader();
    private:
      FilePath _appPath;
      StaticImageProgram _program;
      std::unique_ptr<Image> _imgPtr;
      GLuint _texture;
      unsigned int _width;
      unsigned int _height;
  }
}

#endif