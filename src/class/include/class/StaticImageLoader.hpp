#ifndef STATIC_IMAGE_LOADER_UP_HPP__
#define STATIC_IMAGE_LOADER_UP_HPP__

#include <glimac/Program.hpp>
#include <glimac/common.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <map>
#include <string>

using namespace glimac;

namespace UP
{

struct StaticImage
{
  std::string _filename;
  std::unique_ptr<Image> _imgPtr;
  GLuint* _texture;
  std::vector<Vertex2DUV> _vertices;
  glm::mat3 _modelMatrix;
  glm::mat3 _computedMatrix;
  float _x, _y, _scale;  
};

struct StaticImageProgram
{
  Program _Program;
  GLuint _uTexture;
  GLuint _uModelMatrix;
};

/**
 * @brief StaticImageLoader class Helper
 * 1: Search for the asset image
 * 2: Create the texture
 * 3: Create the matching size square
 * 4: Apply the correct Image
 * 5: Display the image
 */
class StaticImageLoader
{
public:
  /// Constructor and destructor
  StaticImageLoader();
  StaticImageLoader(const FilePath &appPath);
  ~StaticImageLoader();

  /// Methods
  void addImage(const std::string &filename, const float x=0.f, const float y=0.f, const float scale=1.0f);
  void sendVertexBuffer();
  void displayImage(const std::string &imageName);
  void setScaleVector(const std::string& imageName, const float& scale);
  void setTranslateVector(const std::string& imageName, const float x, const float y);
  void computeMatrix(const std::string &imageName);
  
private:
  FilePath _appPath;
  StaticImageProgram _program;
  std::map<const std::string, StaticImage *> _images;
  std::map<const std::string, StaticImage *>::iterator _it;
  GLuint _vbo;
  GLuint _vao;
  GLuint _ibo;
};
} // namespace UP

#endif