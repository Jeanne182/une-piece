#include <class/StaticImageLoader.hpp>
#include <class/ButtonLoader.hpp>
#include <class/Error.hpp>
#include <glimac/Program.hpp>
#include <glimac/common.hpp>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>
#include <map>
#include <string>
#include <iostream>
#include <exception>
#include <cassert>

namespace UP
{

ButtonLoader::ButtonLoader(const FilePath &appPath, const int &width, const int &height)
    : StaticImageLoader(appPath), _window_width(width), _window_height(height)
{
}

ButtonLoader::~ButtonLoader()
{
}

void ButtonLoader::mouseHover(const SDL_Event &e)
{
  /*
  for(_it=_images.begin(); _it!=_images.end(); _it++) 
  {
    const int startX = (_it->second->_x + 1.f) * _window_width / 2;
    const int startY = (_it->second->_y - 1.f) * _window_height / 2;
    const int endX = startX + _it->second->_imgPtr->getWidth();
    const int endY = startY + _it->second->_imgPtr->getHeight();
    
    _it->second->_isHovered = (e.motion.x >= startX &&
        e.motion.x <= endX &&
        e.motion.y >= startY &&
        e.motion.y <= endY);
  }
  */
}

void ButtonLoader::mouseClick()
{
  /*
  for(_it=_images.begin(); _it!=_images.end(); _it++) 
  {
    _it->second->_isClicked = _it->second->_isHovered;
  }  
  */
}

void ButtonLoader::addImage(const std::string &btn, const float &x, const float &y, const float &scale)
{

  Button *btn = new Button;

  // Create a Button
  btn->_filename = filename;
  btn->_imgPtr = loadImage(_appPath.dirPath() + "../../src/assets/textures" + (btn->_filename + ".png"));
  assert(btn->_imgPtr != nullptr);
  btn->_x = x;
  btn->_y = y;
  btn->_scale = scale;

  btn->_texture_hovered = new GLuint;
  btn->_texture_clicked = new GLuint;
  glGenTextures(1, btn->_texture_hovered);
  glGenTextures(1, btn->_texture_clicked);

  /*  
  // Load other Images
  std::unique_ptr<Image> hovered, clicked;
  hovered = loadImage(_appPath.dirPath() + "../../src/assets/textures" + (img->_filename + "_hovered.png"));
  clicked = loadImage(_appPath.dirPath() + "../../src/assets/textures" + (img->_filename + "_clicked.png"));
  
  
  // Verify errors
  assert(img->_imgPtr != nullptr);
  assert(hovered != nullptr);
  assert(clicked != nullptr);
  
  glGenTextures(3, img->_textures);
  
  // Setup Basic
  glBindTexture(GL_TEXTURE_2D, img->_textures[BUTTON_STATE_BASIC]);
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
  
  // Setup Hovered
  glBindTexture(GL_TEXTURE_2D, img->_textures[BUTTON_STATE_HOVERED]);
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

  // Setup Clicked
  glBindTexture(GL_TEXTURE_2D, img->_textures[BUTTON_STATE_CLICKED]);
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
  */
  
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
}

void ButtonLoader::displayImage(const std::string &imageName)
{

  /*
  _it = _images.find(imageName);
  if (_it == _images.end())
  {
    throw Error(std::string("imageName given not in records"), AT);
  }

  _program._Program.use();

  // On charge la bonne texture
  if ( _it->second->_isClicked )
    glBindTexture(GL_TEXTURE_2D, _it->second->_textures[BUTTON_STATE_CLICKED]);
  else if ( _it->second->_isHovered )
    glBindTexture(GL_TEXTURE_2D, _it->second->_textures[BUTTON_STATE_HOVERED]);
  else
    glBindTexture(GL_TEXTURE_2D, _it->second->_textures[BUTTON_STATE_BASIC]);

  glUniform1i(_program._uTexture, 0);
  glUniformMatrix3fv(_program._uModelMatrix, 1, GL_FALSE, glm::value_ptr(_it->second->_computedMatrix));
  // DRAWING
  glBindVertexArray(_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);

  glBindTexture(GL_TEXTURE_2D, 0);

  */
}

} // END namespace UP