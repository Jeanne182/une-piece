#ifndef ERROR_UP_HPP__
#define ERROR_UP_HPP__

#include <exception>
#include <string>

#define AT __FILE__, __LINE__, __func__

class Error : public std::exception {  
  public:
    Error();
    Error(const std::string &message, const char* file, const unsigned int line, const char* function);
    ~Error();
    const char* what() const noexcept;    
  
  private:
    const std::string _message;
    const char* _file;
    const unsigned int _line;
    const char* _function;
};

#endif