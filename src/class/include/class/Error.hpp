#ifndef ERROR_UP_HPP__
#define ERROR_UP_HPP__

#pragma once

#include <exception>
#include <string>

#define AT __FILE__, __LINE__, __func__

class Error : public std::exception {  
  public:
    /**
     * @brief Construct a new Error object
     * 
     */
    Error();
    /**
     * @brief Construct a new Error object
     * 
     * @param message 
     * @param file 
     * @param line 
     * @param function 
     */
    Error(const std::string &message, const char* file, const unsigned int line, const char* function);
    /**
     * @brief Destroy the Error object
     * 
     */
    ~Error();
    /**
     * @brief Common expressor for the exception
     * 
     * @return const char* 
     */
    const char* what() const noexcept;    
  
  private:
    const std::string _message;
    const char* _file;
    const unsigned int _line;
    const char* _function;
};

#endif