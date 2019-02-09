#include <map>
#include <string>
#include <iostream>
#include <exception>
#include <cassert>

#include <glimac/Program.hpp>
#include <glimac/common.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

#include <class/common.hpp>
#include <class/AssetManager.hpp>
#include <class/StaticImageLoader.hpp>
#include <class/Error.hpp>
#include <class/Utils.hpp>

namespace UP
{

StaticImageLoader::StaticImageLoader()
{
  // Creation des données
  glGenBuffers(1, &_vbo);
  glGenBuffers(1, &_ibo);
  glGenVertexArrays(1, &_vao);

  // Modification du VAO
  glBindVertexArray(_vao);

  const GLuint VERTEX_ATTR_POSITION = 0;
  const GLuint VERTEX_ATTR_COORDINATES = 1;
  glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
  glEnableVertexAttribArray(VERTEX_ATTR_COORDINATES);

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid *)offsetof(Vertex2DUV, position));
  glVertexAttribPointer(VERTEX_ATTR_COORDINATES, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2DUV), (const GLvoid *)offsetof(Vertex2DUV, coord));
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

}

StaticImageLoader::~StaticImageLoader()
{
  std::map<const std::string, StaticImage *>::const_iterator it;
  for (it = _images.begin(); it != _images.end(); ++it)
  {
    glDeleteTextures(1, it->second->_texture);
    delete it->second->_texture;
    delete it->second;
  }

  _images.clear();

  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_ibo);
  glDeleteVertexArrays(1, &_vao);
}

StaticImage *StaticImageLoader::getStaticImage(const std::string &imageName, const char *file, const unsigned int line, const char *function)
{
  if (!hasImage(imageName))
    throw Error(std::string("imageName given " + imageName + ":  not in records"), file, line, function);
  else
    return (StaticImage *)_images.find(imageName)->second;
}

StaticImage *StaticImageLoader::getStaticImage(const std::string &imageName, const char *file, const unsigned int line, const char *function) const
{
  if (!hasImage(imageName))
    throw Error(std::string("imageName given " + imageName + ":  not in records"), file, line, function);
  else
    return (StaticImage *)_images.find(imageName)->second;
}

void StaticImageLoader::addImage(const std::string &filename, const float &x, const float &y, const float &scale)
{
  // If there is already this image, just move it
  if (hasImage(filename))
  {
    StaticImage *img = getStaticImage(filename, AT);
    img->_x = x;
    img->_y = y;
    img->_scale = scale;
    computeMatrix(img);
    return;
  }

  // Else create it

  StaticImage *img = new StaticImage;

  
  glCheckError();

  // Load Image
  img->_filename = filename;
  img->_imgPtr = loadImage(AssetManager::Get()->textureFile((img->_filename + ".png")));
  assert(img->_imgPtr != nullptr);
  img->_x = x;
  img->_y = y;
  img->_scale = scale;

  // Create and bind the Texture
  img->_texture = new GLuint;
  glGenTextures(1, img->_texture);
  glBindTexture(GL_TEXTURE_2D, *(img->_texture));
  glTexImage2D(GL_TEXTURE_2D,             // Target
               0,                         // Mipmap level
               GL_RGBA,                   // Internal Format
               img->_imgPtr->getWidth(),  // Width
               img->_imgPtr->getHeight(), // Height
               0,                         // Border
               GL_RGBA,                   // Format
               GL_FLOAT,                  // Type
               img->_imgPtr->getPixels()  // Value
  );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);
  
  glCheckError();

  // Setup the Square, and update the IBO
  setupImage(filename, img);
}

void StaticImageLoader::setupImage(const std::string &filename, StaticImage *img)
{

  // Create the matching square
  img->_vertices.push_back(Vertex2DUV(glm::vec2(1.f, 1.f), glm::vec2(1.0f, 1.f)));
  img->_vertices.push_back(Vertex2DUV(glm::vec2(0.f, 1.f), glm::vec2(0.0f, 1.f)));
  img->_vertices.push_back(Vertex2DUV(glm::vec2(1.f, 0.f), glm::vec2(1.0f, 0.f)));
  img->_vertices.push_back(Vertex2DUV(glm::vec2(0.f, 0.f), glm::vec2(0.0f, 0.f)));

  // Create the matrix
  float ratio = float(img->_imgPtr->getHeight()) / float(img->_imgPtr->getWidth());
  img->_modelMatrix = glm::mat3(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / ratio, -1.0f, 1.0f)));

  // Add the new image
  _images.insert(std::pair<std::string, StaticImage *>(img->_filename, img));

  // Compute the matrix
  computeMatrix(img);

  // Update the IBO
  int indices[6] = {3, 1, 2, 0, 1, 2};
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), indices, GL_STATIC_DRAW);

  glBindVertexArray(_vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
  glBindVertexArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void StaticImageLoader::sendVertexBuffer() const
{

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);

  // On compte le nombre d'objets
  std::vector<Vertex2DUV> vertices;
  std::map<const std::string, StaticImage *>::const_iterator it;
  for (it = _images.begin(); it != _images.end(); ++it)
  {
    vertices.insert(vertices.end(), it->second->_vertices.begin(), it->second->_vertices.end());
  }

  glBufferData(GL_ARRAY_BUFFER,
               vertices.size() * sizeof(Vertex2DUV),
               vertices.data(),
               GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void StaticImageLoader::displayImage(const std::string &imageName) const
{
  StaticImage *img = getStaticImage(imageName, AT);

  // On charge la bonne texture
  glBindTexture(GL_TEXTURE_2D, *(img->_texture));
  glUniform1i(AssetManager::Get()->staticImageProgram()._uTexture, 0);
  glUniformMatrix3fv(AssetManager::Get()->staticImageProgram()._uModelMatrix, 1, GL_FALSE, glm::value_ptr(img->_computedMatrix));

  // DRAWING
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glBindTexture(GL_TEXTURE_2D, 0);
}

void StaticImageLoader::setScaleVector(const std::string &imageName, const float &scale) const
{
  StaticImage *img = getStaticImage(imageName, AT);
  img->_scale = scale;
  computeMatrix(img);
}

void StaticImageLoader::setTranslateVector(const std::string &imageName, const float x, const float y) const
{
  StaticImage *img = getStaticImage(imageName, AT);
  img->_x = x;
  img->_y = y;
  computeMatrix(img);
}

void StaticImageLoader::computeMatrix(const std::string &imageName) const
{
  computeMatrix(getStaticImage(imageName, AT));
}

void StaticImageLoader::computeMatrix(StaticImage *img) const
{
  glm::mat3 T = glm::mat3(
      glm::vec3(1, 0, 0),
      glm::vec3(0, 1, 0),
      glm::vec3(img->_x, img->_y, 1));
  glm::mat3 S = glm::mat3(
      glm::vec3(img->_scale, 0, 0),
      glm::vec3(0, img->_scale, 0),
      glm::vec3(0, 0, 1));
  img->_computedMatrix = T * S * img->_modelMatrix;
}

} // namespace UP
