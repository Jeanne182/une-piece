#include "../include/class/Error.hpp"

#include <string>
#include <iostream>

Error::Error()
  : _message(""), _file(""), _line(0), _function("")
{};
Error::Error(const std::string &message, const char* file, const unsigned int line, const char* function)
  : _message(message), _file(file), _line(line), _function(function)
{};
Error::~Error() {};
const char* Error::what() const noexcept {
  std::string message = std::string( "Error At: " + std::string(_file) + ":" + std::to_string(_line) + "::" + std::string(_function) +"\n  Message: " + _message );
  std::cout << message << std::endl;
  return message.c_str();
};