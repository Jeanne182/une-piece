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
  
ButtonLoader::ButtonLoader(const FilePath &appPath)
  : StaticImageLoader(appPath)
{
}

ButtonLoader::~ButtonLoader()
{
}
  

void ButtonLoader::mouseHover(const SDL_Event &e) {
  std::cout << "M [" << e.motion.x << " | " << e.motion.y << "]" << std::endl;
}
  
}