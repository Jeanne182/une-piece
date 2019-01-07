#include <class/Skybox.hpp>
#include <class/AssetManager.hpp>
#include <class/common.hpp>
#include <class/Utils.hpp>

using namespace glimac;
namespace UP
{
Skybox::Skybox()
{
  loadImages();
}

Skybox::~Skybox()
{
  glDeleteVertexArrays(1, &_vao);
  glDeleteBuffers(1, &_vbo);
}

void Skybox::loadImages()
{

  // Setup the Program
  AssetManager::Get()->skyboxProgram()._Program.use();
  glUniform1i(AssetManager::Get()->skyboxProgram()._uSkybox, 0);

  _P = glm::perspective(glm::radians(70.f), (float)WINDOW_WIDTH / (float)WINDOW_WIDTH, 0.1f, 100.0f);

  // Setup the vertices for the vao
  float vertices[] = {
      // positions
      -1.0f, 1.0f, -1.0f,
      -1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
      1.0f, 1.0f, -1.0f,
      -1.0f, 1.0f, -1.0f,

      -1.0f, -1.0f, 1.0f,
      -1.0f, -1.0f, -1.0f,
      -1.0f, 1.0f, -1.0f,
      -1.0f, 1.0f, -1.0f,
      -1.0f, 1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f,

      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,

      -1.0f, -1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, -1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f,

      -1.0f, 1.0f, -1.0f,
      1.0f, 1.0f, -1.0f,
      1.0f, 1.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f, 1.0f,
      -1.0f, 1.0f, -1.0f,

      -1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f, 1.0f,
      1.0f, -1.0f, -1.0f,
      1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f, 1.0f,
      1.0f, -1.0f, 1.0f};

  // Setup the vao and vbo
  glGenVertexArrays(1, &_vao);
  glGenBuffers(1, &_vbo);

  glBindVertexArray(_vao);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), &vertices, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

  glGenTextures(1, &_texture);
  glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);

  std::vector<std::string> texturesNames = {
      "right",
      "left",
      "top",
      "bottom",
      "front",
      "back"};

  // Load the 6 textures
  std::unique_ptr<Image> imgPtr;
  for (GLuint i = 0; i < texturesNames.size(); i++)
  {
    imgPtr = loadImage(AssetManager::Get()->textureFile((texturesNames[i] + ".jpg")));
    assert(imgPtr != nullptr);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                 0,
                 GL_RGBA,
                 imgPtr->getWidth(),
                 imgPtr->getHeight(),
                 0,
                 GL_RGBA,
                 GL_FLOAT,
                 imgPtr->getPixels());
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}

void Skybox::computeMatrix(const glm::mat4 &view)
{
  // Remove translation
  _V = glm::mat4(glm::mat3(view));
}

void Skybox::display() const
{
  /*
  std::cout << "Skybox" << std::endl;
  std::cout << "P : " << _P << std::endl << std::endl;
  std::cout << "V : " << _V << std::endl << std::endl;
  std::cout << "PV : " << _P * _V << std::endl << std::endl;
  std::cout << "uProj " << sp._uProj << " | uView :" << sp._uView << std::endl;
  */
  // change depth function so depth test passes when values are equal to depth buffer's content
  glCheckError();
  glDepthFunc(GL_LEQUAL);

  // Use the program
  const SkyboxProgram &sp = AssetManager::Get()->skyboxProgram();
  sp._Program.use();
  glUniformMatrix4fv(sp._uProj, 1, GL_FALSE, glm::value_ptr(_P));
  glUniformMatrix4fv(sp._uView, 1, GL_FALSE, glm::value_ptr(_V));

  glBindVertexArray(_vao);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, _texture);

  glDrawArrays(GL_TRIANGLES, 0, 36);

  // Reset
  glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
  glBindVertexArray(0);
  glDepthFunc(GL_LESS);
  glCheckError();
}
} // namespace UP