#ifndef STATIC_IMAGE_LOADER_UP_HPP__
#define STATIC_IMAGE_LOADER_UP_HPP__

#pragma once

#include <map>
#include <string>

#include <glimac/Program.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

#include <class/Program.hpp>
#include <class/common.hpp>


using namespace glimac;

namespace UP
{

/**
 * @brief Data Structure for an Image
 * 
 */
struct StaticImage
{
  std::string _filename;
  std::unique_ptr<Image> _imgPtr;
  GLuint *_texture;
  std::vector<Vertex2DUV> _vertices;
  glm::mat3 _modelMatrix;
  glm::mat3 _computedMatrix;
  float _x, _y, _scale;
};

/**
 * @brief StaticImageLoader class Helper
 * @brief 1: Search for the asset image
 * @brief 2: Create the texture
 * @brief 3: Create the matching size square
 * @brief 4: Apply the correct Image
 * @brief 5: Display the image
 */
class StaticImageLoader
{
public:
  /// Constructor and destructor

  /**
   * @brief Construct a new Image Loader:: Image Loader object
   */
  StaticImageLoader();

  /**
   * @brief Destroy the Image Loader:: Image Loader object
   * 
   */
  ~StaticImageLoader();

  /// Methods

  /**
   * @brief Check if an image is in the records
   * 
   * @param imageName 
   * @return true 
   * @return false 
   */
  inline bool hasImage(const std::string &imageName) const { return _images.find(imageName) != _images.end(); };

  /**
   * @brief Get an Image object
   * 
   * @param imageName 
   * @return StaticImage* 
   */
  StaticImage *getStaticImage(const std::string &imageName, const char *file, const unsigned int line, const char *function);

  /**
   * @brief Get an const Image object
   * 
   * @param imageName 
   * @return StaticImage* 
   */
  StaticImage *getStaticImage(const std::string &imageName, const char *file, const unsigned int line, const char *function) const;

  /**
   * @brief Add an image to the Loader
   * 
   * @param filename
   * @param x
   * @param y
   * @param scale
   */
  void addImage(const std::string &filename, const float &x = 0.f, const float &y = 0.f, const float &scale = 1.0f);

  /**
   * @brief Display 1 image
   * 
   * @param imageName
   */
  void displayImage(const std::string &imageName) const;

  /**
   * @brief Send VBO to GPU
   * 
   */
  void sendVertexBuffer() const;

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
  void setupImage(const std::string &filename, StaticImage *img);

  /**
   * @brief Set the Scaling Vector to use far a loaded image
   *
   * @param imageName
   * @param scale
   */
  void setScaleVector(const std::string &imageName, const float &scale) const;

  /**
   * @brief Set the Translate Vector to use far a loaded image
   *
   * @param imageName
   * @param x
   * @param y
   */
  void setTranslateVector(const std::string &imageName, const float x, const float y) const;

  /**
   * @brief Compute the final matrix to be used for the GPU
   * 
   * @param imageName
   */
  void computeMatrix(const std::string &imageName) const;
  void computeMatrix(StaticImage *img) const;

  /// Attributes
  std::map<const std::string, StaticImage *> _images;
  GLuint _vbo, _vao, _ibo;
};

} // namespace UP

#endif