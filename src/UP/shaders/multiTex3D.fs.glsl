#version 330 core

// Entrées du shader
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec4 fFragColor;

uniform sampler2D uTexture_diffuse1;
uniform sampler2D uTexture_specular1;
uniform float uTextureRepeat;

void main() {
  vec4 tx1 = texture(uTexture_diffuse1, vTexCoords * uTextureRepeat);
  vec4 tx2 = texture(uTexture_specular1, vTexCoords * uTextureRepeat);
  fFragColor = tx1*tx2;
  //fFragColor = normalize(vec4(vTexCoords, vTexCoords));
  //fFragColor = tx1*tx2;
}
