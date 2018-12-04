#ifndef UTILS_UP_HPP__
#define UTILS_UP_HPP__

#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>

GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

#endif