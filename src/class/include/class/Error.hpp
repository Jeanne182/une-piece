#ifndef ERROR_UP_HPP__
#define ERROR_UP_HPP__

#include <exception>
#include <string>

namespace UP
{

class Error : public std::exception
{
public:
  Error();
  Error(const int &level, const int &code, const std::string &message);
  inline int getLevel() const { return _level; };
  inline int getCode() const { return _code; };
  const char *what() const noexcept;

private:
  int _level;
  int _code;
  std::string _message;
};

} // namespace UP
#endif