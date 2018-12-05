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
}

void ButtonLoader::mouseClick() 
{
  for(_it=_images.begin(); _it!=_images.end(); _it++) 
  {
    _it->second->_isClicked = _it->second->_isHovered;
  }  
}
  
void ButtonLoader::addImage(const std::string &filename, const float &x, const float &y, const float &scale)
{
  Button *img = new Button;

  // Load Basic Image
  img->_texture = nullptr;
  img->_filename = filename;
  img->_imgPtr = loadImage(_appPath.dirPath() + "../../src/assets/textures" + (img->_filename + ".png"));
  
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
  
  // Setup the Square, and update the IBO
  StaticImageLoader::setupImage(filename, x, y, scale, img);  
}
  
  
void StaticImageLoader::displayImage(const std::string &imageName)
{
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
}
  
} // END namespace UP