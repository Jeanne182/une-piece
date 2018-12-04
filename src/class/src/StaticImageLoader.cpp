#include <class/StaticImageLoader.hpp>
#include <class/Error.hpp>
#include <glimac/Program.hpp>
#include <glimac/common.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <map>
#include <string>
#include <iostream>
#include <exception>

namespace UP
{

glm::mat3 translate(const float tx, const float ty) {
  return glm::mat3(
    glm::vec3(1, 0, 0),
    glm::vec3(0, 1, 0),
    glm::vec3(tx, ty, 1)
  );
}
glm::mat3 scale(const float sx, const float sy) {
  return glm::mat3(
    glm::vec3(sx, 0, 0),
    glm::vec3(0, sy, 0),
    glm::vec3(0, 0, 1)
  );
}
glm::mat3 rotate(const float a) {
  return glm::mat3(
    glm::vec3(cos(a), sin(a), 0),
    glm::vec3(-sin(a), cos(a), 0),
    glm::vec3(0, 0, 1)    
  );
}

StaticImageLoader::StaticImageLoader()
{
  throw Error("ERROR at creating StaticImageLoader object: No argument Given", AT);
}
  
StaticImageLoader::StaticImageLoader(const FilePath &appPath)
    : _appPath(appPath)
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

  // Création du programme
  _program._Program = glimac::loadProgram(
      appPath.dirPath() + "shaders/tex2D.vs.glsl",
      appPath.dirPath() + "shaders/tex2D.fs.glsl");
  _program._uTexture = glGetUniformLocation(_program._Program.getGLId(), "uTexture");
  _program._uModelMatrix = glGetUniformLocation(_program._Program.getGLId(), "uModelMatrix");
}

StaticImageLoader::~StaticImageLoader()
{
  for (_it=_images.begin(); _it!=_images.end(); ++_it) {
    delete _it->second->_texture;
    delete _it->second;
  }
}

void StaticImageLoader::addImage(const std::string &filename, const float x, const float y, const float scale)
{
  StaticImage *img = new StaticImage;

  // Load Image
  img->_filename = filename;
  img->_imgPtr = loadImage(_appPath.dirPath() + "../../src/assets/textures" + (img->_filename + ".png"));
  assert(img->_imgPtr != nullptr);

  // Add the coord
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

  // Create the matching square
  img->_vertices.push_back(Vertex2DUV(glm::vec2(1.f, 1.f), glm::vec2(1.0f, 1.f)));
  img->_vertices.push_back(Vertex2DUV(glm::vec2(0.f, 1.f), glm::vec2(0.0f, 1.f)));
  img->_vertices.push_back(Vertex2DUV(glm::vec2(1.f, 0.f), glm::vec2(1.0f, 0.f)));
  img->_vertices.push_back(Vertex2DUV(glm::vec2(0.f, 0.f), glm::vec2(0.0f, 0.f)));

  // Create the matrix
  float ratio = float(img->_imgPtr->getHeight()) / float(img->_imgPtr->getWidth());
  //std::cout << "Ratio: " << ratio << std::endl;
  img->_modelMatrix = glm::mat3(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / ratio, -1.0f, 1.0f)));

  // Add the new image
  _images.insert(std::pair<std::string, StaticImage *>(img->_filename, img));

  // Compute the matrix
  computeMatrix(filename);

  // Update the IBO
  int indices[6] = {3, 1, 2, 0, 1, 2};
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               6 * sizeof(int),
               indices,
               GL_STATIC_DRAW);
  glBindVertexArray(_vao);
  // => On bind l'IBO sur GL_ELEMENT_ARRAY_BUFFER; puisqu'un VAO est actuellement bindé,
  // cela a pour effet d'enregistrer l'IBO dans le VAO
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

  // Unbind
  glBindVertexArray(0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
  
void StaticImageLoader::sendVertexBuffer()
{

  glBindBuffer(GL_ARRAY_BUFFER, _vbo);

  // On compte le nombre d'objets
  std::vector<Vertex2DUV> vertices;
  for (_it = _images.begin(); _it != _images.end(); ++_it)
  {
    vertices.insert(vertices.end(), _it->second->_vertices.begin(), _it->second->_vertices.end());
  }

  glBufferData(GL_ARRAY_BUFFER,
               vertices.size() * sizeof(Vertex2DUV),
               vertices.data(),
               GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void StaticImageLoader::displayImage(const std::string &imageName)
{
  _it = _images.find(imageName);
  if (_it == _images.end())
  {
    throw Error(std::string("imageName given not in records"), AT);
  }

  _program._Program.use();
  StaticImage *img = _it->second;

  // On charge la bonne texture
  glBindTexture(GL_TEXTURE_2D, *(img->_texture));
  glUniform1i(_program._uTexture, 0);
  //modelMatrix = rotate(time) * translate(0.5f, 0.5f) * rotate(-time) * scale(0.25f, 0.25f);
  glUniformMatrix3fv(_program._uModelMatrix, 1, GL_FALSE, glm::value_ptr(img->_computedMatrix));

  // => On utilise glDrawElements à la place de glDrawArrays
  // Cela indique à OpenGL qu'il doit utiliser l'IBO enregistré dans le VAO
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glBindTexture(GL_TEXTURE_2D, 0);
  _it = _images.begin();
}

void StaticImageLoader::setScaleVector(const std::string &imageName, const float &scale)
{
  _it = _images.find(imageName);
  if (_it == _images.end())
    throw Error(std::string("imageName given not in records"), AT);
  _it->second->_scale = scale;
  computeMatrix(imageName);
}

void StaticImageLoader::setTranslateVector(const std::string &imageName, const float x, const float y)
{
  _it = _images.find(imageName);
  if (_it == _images.end())
    throw Error(std::string("imageName given not in records"), AT);

  _it->second->_x = x;
  _it->second->_y = y;
  computeMatrix(imageName);
}

void StaticImageLoader::computeMatrix(const std::string &imageName)
{
  StaticImage *img = _images.find(imageName)->second;
  img->_computedMatrix = translate(img->_x, img->_y) * scale(img->_scale, img->_scale) * img->_modelMatrix;
}



} // namespace UP
