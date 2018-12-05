#ifndef STATIC_IMAGE_LOADER_UP_HPP__
#define STATIC_IMAGE_LOADER_UP_HPP__

#pragma once

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

  /**
   * @brief Construct a new Image Loader:: Image Loader object
   * 
   * @param appPath 
   */
  StaticImageLoader(const FilePath &appPath);
  
  /**
   * @brief Destroy the Image Loader:: Image Loader object
   * 
   */
  ~StaticImageLoader();

  /// Methods
  
  /**
   * @brief Add an image to the Loader
   * 
   * @param filename
   * @param x
   * @param y
   * @param scale
   */
  void addImage(const std::string &filename, const float &x=0.f, const float &y=0.f, const float &scale=1.0f);
  
  /**
   * @brief Display 1 image
   * 
   * @param imageName
   */
  void displayImage(const std::string &imageName);

  /**
   * @brief Send VBO to GPU
   * 
   */
  void sendVertexBuffer();
  
private:
  
  /**
   * @brief Construct a new Image Loader:: Image Loader object
   * DO NOT USE 
   */
  StaticImageLoader();
    
  /// Methods
  
  /**
   * @brief Compute the final matrix to be used for the GPU
   * 
   * @param imageName
   */
  void computeMatrix(const std::string &imageName);
  
  /**
   * @brief Set the Scaling Vector to use far a loaded image
   *
   * @param imageName
   * @param scale
   */
  void setScaleVector(const std::string& imageName, const float& scale);
  
  /**
   * @brief Set the Translate Vector to use far a loaded image
   *
   * @param imageName
   * @param x
   * @param y
   */
  void setTranslateVector(const std::string& imageName, const float x, const float y);
  
  
protected:  
  /// Methods
  /**
   * @brief Setup the Square, and update the IBO
   * 
   * @param filename
   * @param x
   * @param y
   * @param scale
   */
  void setupImage(const std::string &filename, const float &x, const float &y, const float &scale, StaticImage* img);
  
  /// Attributes
  FilePath _appPath;
  StaticImageProgram _program;
  std::map<const std::string, StaticImage *> _images;
  std::map<const std::string, StaticImage *>::iterator _it;
  GLuint _vbo, _vao, _ibo;
  
};
  
} // namespace UP

#endif