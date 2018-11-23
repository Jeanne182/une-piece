cmake_minimum_required(VERSION 2.8)

project(une-piece C CXX)

add_definitions(-std=c++11)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
# set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

set(ASSIMP_LIBRARY_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp-4.1.0/build/code/)
set(ASSIMP_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp-4.1.0/include/ ${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp-4.1.0/build/include/)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
include_directories(${ASSIMP_INCLUDE_DIRS})
include_directories(${SOIL_INCLUDE_DIRS})
include_directories(class/include glimac/include third-party/include)

link_directories(${ASSIMP_LIBRARY_DIRS})

set(ALL_LIBRARIES glimac class assimp ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

# Adding libraries
add_subdirectory(class)
add_subdirectory(glimac)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/libs/assimp-4.1.0)

file(GLOB UP_DIRECTORY "UP*")

foreach(UP ${UP_DIRECTORY})
    add_subdirectory(${UP})
endforeach()
