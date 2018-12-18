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
static unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
static std::mt19937_64 generator(seed);
static unsigned int pMax;

void setSeed();

/**
 * @brief Return a randum number between min and max
 * 
 * @param min 
 * @param max 
 * @return int 
 */
int dicei(const int min, const int max);
/**
 * @brief Return a randum number between min and max
 * 
 * @param min 
 * @param max 
 * @return int 
 */
float dicef(const float min, const float max);

/**
 * @brief 
 * 
 * @param p 
 * @return true 
 * @return false 
 */
bool maybe(const float p);
int rBatchSize();

} // namespace Utils

#endif