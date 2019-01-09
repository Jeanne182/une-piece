#ifndef COMMON_HPP__
#define COMMON_HPP__

#pragma once

#include <GL/glew.h>
#include <string>
#include <map>

#include <glimac/glm.hpp>
#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>

using namespace glimac;

namespace UP
{

static const bool USE_CHRONO = false;
static const int WINDOW_WIDTH = 800;
static const int WINDOW_HEIGHT = 800;
static const bool DEBUG = true;
static bool DEBUG_DISPLAY = false;

static const float COIN_ROTATION_SPEED = 1.f;
static const float TENTACLE_ANGLE_AMPLITUDE = 1.5f;
static const float TENTACLE_ANGLE_SPEED = 0.3f;

static const std::string PLAYER_MODEL_NAME = "bateau.obj";
static const std::string ROCK_MODEL_NAME = "rock.obj";
static const std::string TENTACLE_MODEL_NAME = "tentacle.obj";
static const std::string PONTON_MODEL_NAME = "ponton.obj";
static const std::string WATER_MODEL_NAME = "water.obj";
static const std::string COIN_MODEL_NAME = "ruby.obj";
static const std::string BONUS_INVULNERABILITY_MODEL_NAME = "invincible.obj";
static const std::string BONUS_SLOWNESS_MODEL_NAME = "Bonus_SpeedUp.obj";
static const std::string BONUS_LIFEUP_MODEL_NAME = "Bonus_SpeedDown.obj";
static const std::string BONUS_MAGNET_MODEL_NAME = "Bonus_SpeedDown.obj";

static const float PLAYER_ACCELERATION_AMOUNT = 0.02f;
static const float PLAYER_DECCELERATION_AMOUNT = 0.9f;
static const int PLAYER_ACCELERATION_INTERVAL = 600;

static const glm::vec3 VEC_NORTH = glm::vec3(1.f, 0.f, 0.f);
static const glm::vec3 VEC_SOUTH = glm::vec3(-1.f, 0.f, 0.f);
static const glm::vec3 VEC_EAST = glm::vec3(0.f, 0.0f, 1.f);
static const glm::vec3 VEC_WEST = glm::vec3(0.f, 0.0f, -1.f);

static const glm::mat4 MATRIX_PERSPECTIVE = glm::perspective(glm::radians(70.0f), (float)(WINDOW_WIDTH / WINDOW_HEIGHT), 0.1f, 200.f);


enum DIRECTION {
  DIR_NORTH,
  DIR_EAST,
  DIR_SOUTH,
  DIR_WEST
};

/**
 * @brief Data structure for a vertex
 *
 */
struct ShapeVertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;

    ShapeVertex()
    {
    };

    ShapeVertex(const glm::vec3& p, const glm::vec3& n, const glm::vec2& c) {
      position = p;
      normal = n;
      texCoords = c;
    };

};

/**
 * @brief Data Structure for a 2D point
 *
 */
struct Vertex2DUV
{

  glm::vec2 position;
  glm::vec2 coord;

  Vertex2DUV(const glm::vec2 &pos, const glm::vec2 &c)
  {
    position.x = pos.x;
    position.y = pos.y;
    coord.x = c.x;
    coord.y = c.y;
  };
};

/**
 * @brief Data structure for a texture
 *
 */
struct Texture
{
  unsigned int id;
  std::string type;
  std::string path;
  float shininess;
  glm::vec3 diffuse = glm::vec3(3);
  glm::vec3 specular = glm::vec3(3);
};

/**
 * @brief Data structure to simplify the Coordinates management
 *
 */
enum COORD
{
  X,
  Y,
  Z
};

/**
 * @brief Data structure to identify the Point of View
 *
 */
enum POV
{
  FIRST_PERSON,
  THIRD_PERSON,
  ROTATING,
  FREE_FLY
};

} // namespace UP

#endif
