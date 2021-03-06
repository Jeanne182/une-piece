#include <string>
#include <iostream>

#include <class/AssetManager.hpp>
#include <class/TextManager.hpp>
#include <class/Error.hpp>
#include <class/Utils.hpp>

using namespace glimac;
namespace UP
{
void TextManager::setupTTF()
{
  FT_Library ft;
  if (FT_Init_FreeType(&ft))
    std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

  FT_Face face;
  if (FT_New_Face(ft, AssetManager::Get()->fontFile("Old-London.ttf").c_str(), 0, &face))
    std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

  FT_Set_Pixel_Sizes(face, 0, 48);

  if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
    std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;

  // Load the 128 first characters
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1); // Disable byte-alignment restriction

  for (GLubyte c = 0; c < 128; c++)
  {
    // Load character glyph
    if (FT_Load_Char(face, c, FT_LOAD_RENDER))
    {
      std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
      continue;
    }
    // Generate texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RED,
        face->glyph->bitmap.width,
        face->glyph->bitmap.rows,
        0,
        GL_RED,
        GL_UNSIGNED_BYTE,
        face->glyph->bitmap.buffer);

    // Set texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Now store character for later use
    Glyph glyph;
    glyph._textureID = texture;
    glyph._size = glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows);
    glyph._bearing = glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top);
    glyph._advance = static_cast<GLuint>(face->glyph->advance.x);
    _glyphes.insert(std::pair<GLchar, Glyph>(c, glyph));
  }

  FT_Done_Face(face);
  FT_Done_FreeType(ft);

  // Setup the VBO and VAO
  glGenVertexArrays(1, &_vao);
  glGenBuffers(1, &_vbo);

  glBindVertexArray(_vao);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);

  glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, NULL, GL_DYNAMIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  // Send the projection
  glCheckError();

  glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(WINDOW_WIDTH), 0.0f, static_cast<GLfloat>(WINDOW_HEIGHT));
  glCheckError();

  AssetManager::Get()->glyphProgram()._Program.use();
  glUniformMatrix4fv(AssetManager::Get()->glyphProgram()._uProjection, 1, GL_FALSE, glm::value_ptr(projection));

  glCheckError();
}

void TextManager::renderText(const std::string &text, const GLfloat &x, const GLfloat &y, const GLfloat &scale, const glm::vec3 &color)
{
  // Setup the program
  const GlyphProgram &gp = AssetManager::Get()->glyphProgram();
  gp._Program.use();

  // Send the color
  glUniform3fv(gp._uTextColor, 1, glm::value_ptr(color));

  // Texture unit
  glActiveTexture(GL_TEXTURE0);
  glBindVertexArray(_vao);

  // Iterate through all characters
  float x_ = x;
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++)
  {
    Glyph glyph = _glyphes[*c];

    GLfloat xpos = x_ + glyph._bearing.x * scale;
    GLfloat ypos = y - (glyph._size.y - glyph._bearing.y) * scale;

    GLfloat w = glyph._size.x * scale;
    GLfloat h = glyph._size.y * scale;

    // Update VBO for each character
    GLfloat vertices[6][4] = {
        {xpos, ypos + h, 0.0, 0.0},
        {xpos, ypos, 0.0, 1.0},
        {xpos + w, ypos, 1.0, 1.0},

        {xpos, ypos + h, 0.0, 0.0},
        {xpos + w, ypos, 1.0, 1.0},
        {xpos + w, ypos + h, 1.0, 0.0}};

    // Render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, glyph._textureID);

    // Update content of VBO memory
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Render quad

    glDrawArrays(GL_TRIANGLES, 0, 6);

    // Advance cursors for next glyph
    x_ += (glyph._advance >> 6) * scale; // Bitshift by 6 to get value in pixels (2^6 = 64)
  }

  // Unbind
  glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

} // namespace UP