#ifndef UTILS_UP_HPP__
#define UTILS_UP_HPP__

#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <random>
#include <chrono>

/**
 * @brief HELPER function to Test my glGetError()
 * 
 * @param file 
 * @param line 
 * @return GLenum 
 */
GLenum glCheckError_(const char *file, int line);
#define glCheckError() glCheckError_(__FILE__, __LINE__)

namespace Utils
{

// select seed from time
//static const unsigned seed = 0;
static unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::mt19937_64 generator(seed);

void setSeed();
int rBatchSize();

} // namespace Utils

#endif