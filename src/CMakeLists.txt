cmake_minimum_required(VERSION 2.8)

project(une-piece C CXX)

add_definitions(-std=c++11)
add_definitions(-g)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
# set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR})
include_directories(class/include glimac/include third-party/include)

# Include SOIL
set(SOIL_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/COMPILED_SOIL)
link_directories(${SOIL_DIRECTORY})
include_directories(${SOIL_DIRECTORY})
find_library(SOIL SOIL ${SOIL_DIRECTORY})

# Include ASSIMP
set(ASSIMP_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/COMPILED_ASSIMP)
link_directories(${ASSIMP_DIRECTORY})
include_directories(${ASSIMP_DIRECTORY})
find_library(assimp assimp ${ASSIMP_DIRECTORY})

# Include Freetype
set(FREETYPE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/libs/COMPILED_FREETYPE)
link_directories(${FREETYPE_DIRECTORY})
include_directories(${FREETYPE_DIRECTORY})
find_library(freetype freetype ${FREETYPE_DIRECTORY})

# Adding libraries
add_subdirectory(class)
add_subdirectory(glimac)

set(ALL_LIBRARIES class glimac assimp SOIL freetype ${SDL_LIBRARY} ${GLEW_LIBRARY} ${OPENGL_LIBRARIES})

# Copy save directory
file(COPY save DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


file(GLOB UP_DIRECTORY "UP*")

foreach(UP ${UP_DIRECTORY})
    add_subdirectory(${UP})
endforeach()

# call the CMakeLists.txt to make the documentation (Doxygen)
# > 'make html' to generate the documentation
# > the documentation is located in : [CMAKE ROOT]/build/doc/doc-doxygen/html
add_subdirectory(doc)