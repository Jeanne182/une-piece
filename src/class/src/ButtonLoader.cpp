#include <map>
#include <string>
#include <iostream>
#include <exception>
#include <cassert>

#include <glimac/Program.hpp>
#include <glimac/common.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

#include <class/AssetManager.hpp>
#include <class/StaticImageLoader.hpp>
#include <class/ButtonLoader.hpp>
#include <class/common.hpp>
#include <class/Error.hpp>
#include <class/Utils.hpp>

namespace UP
{

ButtonLoader::~ButtonLoader()
{
  std::map<const std::string, StaticImage *>::const_iterator it;
  for (it = _images.begin(); it != _images.end(); ++it)
  {
    Button *btn = (Button *)it->second;
    glDeleteTextures(1, btn->_texture);
    delete btn->_texture_hovered;
    delete btn->_texture_clicked;
    delete btn->_texture;
    delete btn;
  }
  _images.clear();
}

Button *ButtonLoader::getButton(const std::string &buttonName, const char *file, const unsigned int line, const char *function)
{
  if (!hasImage(buttonName))
    throw Error(std::string("buttonName given " + buttonName + ":  not in records"), file, line, function);
  else
    return (Button *)_images.find(buttonName)->second;
}

Button *ButtonLoader::getButton(const std::string &buttonName, const char *file, const unsigned int line, const char *function) const
{
  if (!hasImage(buttonName))
    throw Error(std::string("buttonName given " + buttonName + ":  not in records"), file, line, function);
  else
    return (Button *)_images.find(buttonName)->second;
}

void ButtonLoader::disable() const
{
  std::map<const std::string, StaticImage *>::const_iterator it;
  for (it = _images.begin(); it != _images.end(); ++it)
  {
    Button *btn = (Button *)it->second;
    btn->_isHovered = false;
    btn->_isClicked = false;
    btn->_behavior = nullptr;
  }
}

void ButtonLoader::mouseHover(const SDL_Event &e) const
{
  std::map<const std::string, StaticImage *>::const_iterator it;
  for (it = _images.begin(); it != _images.end(); it++)
  {
    Button *btn = (Button *)it->second;

    const int startX = (btn->_x + 1.f) * WINDOW_WIDTH / 2;
    const int startY = (btn->_y - 1.f) * WINDOW_HEIGHT / -2;

    const int endX = startX + btn->_imgPtr->getWidth() * btn->_scale * 2.6;
    const int endY = startY + btn->_imgPtr->getHeight() * btn->_scale * 2.6;

    btn->_isHovered = e.motion.x >= startX &&
                      e.motion.x <= endX &&
                      e.motion.y >= startY &&
                      e.motion.y <= endY;

    // std::cout << startX << " < " << e.motion.x << " < " << endX << " | " << startY << " < " << e.motion.y << " < " << endY << " | " << btn->_scale << std::endl;
  }
}

void ButtonLoader::mouseClick() const
{
  std::map<const std::string, StaticImage *>::const_iterator it;
  for (it = _images.begin(); it != _images.end(); it++)
  {
    Button *btn = (Button *)it->second;
    btn->_isClicked = btn->_isHovered;
  }
}

void ButtonLoader::mouseUnclick() const
{
  std::map<const std::string, StaticImage *>::const_iterator it;
  for (it = _images.begin(); it != _images.end(); it++)
  {
    Button *btn = (Button *)it->second;
    if (btn->_isClicked && btn->_isHovered && btn->_behavior)
      btn->_behavior();
    btn->_isClicked = false;
  }
}

void ButtonLoader::addImage(const std::string &filename, const float &x, const float &y, const float &scale)
{
  // If there is already this image, just move it
  if (hasImage(filename))
  {
    Button *btn = getButton(filename, AT);
    btn->_x = x;
    btn->_y = y;
    btn->_scale = scale;
    computeMatrix(btn);
    return;
  }

  // Else create it
  Button *btn = new Button;

  // Create a Button
  btn->_filename = filename;
  btn->_x = x;
  btn->_y = y;
  btn->_scale = scale;

  // Loaded
  btn->_imgPtr = loadImage(AssetManager::Get()->textureFile(btn->_filename + ".png"));
  std::unique_ptr<Image> hovered, clicked;
  hovered = loadImage(AssetManager::Get()->textureFile(btn->_filename + "_hovered.png"));
  clicked = loadImage(AssetManager::Get()->textureFile(btn->_filename + "_clicked.png"));
  assert(btn->_imgPtr != nullptr);
  assert(hovered != nullptr);
  assert(clicked != nullptr);

  // Generating
  btn->_texture = new GLuint;
  btn->_texture_hovered = new GLuint;
  btn->_texture_clicked = new GLuint;
  glGenTextures(1, btn->_texture);
  glGenTextures(1, btn->_texture_hovered);
  glGenTextures(1, btn->_texture_clicked);

  // Setup Basic
  glBindTexture(GL_TEXTURE_2D, *(btn->_texture));
  glTexImage2D(GL_TEXTURE_2D,             // Target
               0,                         // Mipmap level
               GL_RGBA,                   // Internal Format
               btn->_imgPtr->getWidth(),  // Width
               btn->_imgPtr->getHeight(), // Height
               0,                         // Border
               GL_RGBA,                   // Format
               GL_FLOAT,                  // Type
               btn->_imgPtr->getPixels()  // Value
  );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  // Setup Hovered
  glBindTexture(GL_TEXTURE_2D, *(btn->_texture_hovered));
  glTexImage2D(GL_TEXTURE_2D,        // Target
               0,                    // Mipmap level
               GL_RGBA,              // Internal Format
               hovered->getWidth(),  // Width
               hovered->getHeight(), // Height
               0,                    // Border
               GL_RGBA,              // Format
               GL_FLOAT,             // Type
               hovered->getPixels()  // Value
  );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  // Setup Clicked
  glBindTexture(GL_TEXTURE_2D, *(btn->_texture_clicked));
  glTexImage2D(GL_TEXTURE_2D,        // Target
               0,                    // Mipmap level
               GL_RGBA,              // Internal Format
               clicked->getWidth(),  // Width
               clicked->getHeight(), // Height
               0,                    // Border
               GL_RGBA,              // Format
               GL_FLOAT,             // Type
               clicked->getPixels()  // Value
  );
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glBindTexture(GL_TEXTURE_2D, 0);

  glCheckError();

  // Setup the Square, and update the IBO
  setupImage(filename, x, y, scale, btn);
}
void ButtonLoader::setupImage(const std::string &filename, const float &x, const float &y, const float &scale, Button *btn)
{

  // Create the matching square
  btn->_vertices.push_back(Vertex2DUV(glm::vec2(1.f, 1.f), glm::vec2(1.0f, 1.f)));
  btn->_vertices.push_back(Vertex2DUV(glm::vec2(0.f, 1.f), glm::vec2(0.0f, 1.f)));
  btn->_vertices.push_back(Vertex2DUV(glm::vec2(1.f, 0.f), glm::vec2(1.0f, 0.f)));
  btn->_vertices.push_back(Vertex2DUV(glm::vec2(0.f, 0.f), glm::vec2(0.0f, 0.f)));

  // Create the matrix
  float ratio = float(btn->_imgPtr->getHeight()) / float(btn->_imgPtr->getWidth());
  btn->_modelMatrix = glm::mat3(glm::scale(glm::mat4(1.0f), glm::vec3(1.0f / ratio, -1.0f, 1.0f)));

  // Compute the matrix
  computeMatrix(btn);

  // Update the IBO
  int indices[6] = {3, 1, 2, 0, 1, 2};
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), indices, GL_STATIC_DRAW);

  glBindVertexArray(_vao);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
  glBindVertexArray(0);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // Insert
  _images.insert(std::pair<std::string, StaticImage *>(btn->_filename, btn));
}

void ButtonLoader::setBehavior(const std::string &imageName, const std::function<void()> &behavior) const
{
  getButton(imageName, AT)->_behavior = behavior;
}

void ButtonLoader::displayImage(const std::string &imageName) const
{
  Button *btn = getButton(imageName, AT);

  // On charge la bonne texture
  if (btn->_isClicked)
    glBindTexture(GL_TEXTURE_2D, *(btn->_texture_clicked));
  else if (btn->_isHovered)
    glBindTexture(GL_TEXTURE_2D, *(btn->_texture_hovered));
  else
    glBindTexture(GL_TEXTURE_2D, *(btn->_texture));

  glUniform1i(AssetManager::Get()->staticImageProgram()._uTexture, 0);
  glUniformMatrix3fv(AssetManager::Get()->staticImageProgram()._uModelMatrix, 1, GL_FALSE, glm::value_ptr(btn->_computedMatrix));
  // DRAWING
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glBindTexture(GL_TEXTURE_2D, 0);
}

} // END namespace UP