#version 330

// Entrées du shader
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec4 fFragColor;

uniform sampler2D uTexture_diffuse1;
uniform sampler2D uTexture_specular1;
uniform float uTextureRepeat;

void main() {
  vec4 tx1 = texture(uTexture_diffuse1, vTexCoords * uTextureRepeat);
  vec4 tx2 = texture(uTexture_specular1, vTexCoords * uTextureRepeat);
  float multiplier = 1.0;
  tx1 = tx1 * vec4(multiplier, multiplier, multiplier, multiplier);
  tx2 = tx2 * vec4(multiplier, multiplier, multiplier, multiplier);
  fFragColor = tx1*tx2;
  //fFragColor = normalize(vec4(vTexCoords, vTexCoords));
  //fFragColor = tx1*tx2;
}
