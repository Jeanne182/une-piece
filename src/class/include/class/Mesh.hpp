#include <vector>
#include <glimac/common.hpp>

using namespace glimac;

namespace UP
{

class Mesh
{
public:
  
  
  /*  Functions  */
  Mesh(std::vector<ShapeVertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
  void draw() const;

private:
  /*  Mesh Data  */
  std::vector<ShapeVertex> _vertices;
  std::vector<unsigned int> _indices;
  std::vector<Texture> _textures;
  /* OBJ Data */
  GLuint _VAO, _VBO, _EBO;
  void setupMesh();
};

} // namespace UP