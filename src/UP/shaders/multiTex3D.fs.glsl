#version 330

// Entrées du shader
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec4 fFragColor;

uniform sampler2D uTexture_diffuse1;
uniform sampler2D uTexture_specular1;

void main() {
  vec4 tx1 = texture(uTexture_diffuse1, vTexCoords);
  vec4 tx2 = texture(uTexture_specular1, vTexCoords);
  //fFragColor = tx1+tx2;
  float multiplier = 2.0;
  fFragColor = tx1*tx2 * vec4(multiplier, multiplier, multiplier, multiplier);
}
