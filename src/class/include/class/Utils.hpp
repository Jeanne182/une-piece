#ifndef UTILS_UP_HPP__
#define UTILS_UP_HPP__

#pragma once

#include <GL/glew.h>

#include <glimac/glm.hpp>

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
 * @brief Return true with a probability of p
 *
 * @param p
 * @return true
 * @return false
 */
bool maybe(const float p);

/**
 * @brief Utils for the map batch size
 * 
 * @return int 
 */
int rBatchSize();

/**
 * @brief Custom made cast for our map system
 * 
 * @param f 
 * @return int 
 */
int cast(const float f);

/**
 * @brief Get the Directionnal Vector object
 * 
 * @param direction 
 * @return const glm::vec3& 
 */
const glm::vec3 &getDirectionnalVector(const unsigned int &direction);

/**
 * @brief Get the Opposite Directionnal Vector object
 * 
 * @param direction 
 * @return const glm::vec3& 
 */
const glm::vec3 &getOppositeDirectionnalVector(const unsigned int &direction);

/**
 * @brief Get the Bonus Model Name object
 * 
 * @param bonusType 
 * @return const std::string& 
 */
const std::string &getBonusModelName(const unsigned int bonusType);
/**
 * @brief Clamp a float between the min and max
 * 
 * @param n 
 * @param lower 
 * @param upper 
 * @return float 
 */
template<typename T>
T clamp(const T &n, const T &lower, const T &upper)
{
  return std::max(lower, std::min(n, upper));
}
} // namespace Utils

#endif
