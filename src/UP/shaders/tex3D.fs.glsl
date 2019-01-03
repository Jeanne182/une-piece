#version 330

// Entrées du shader
in vec4 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec4 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform sampler2D uTexture;
uniform float uTextureRepeat;

void main() {
  fFragColor = texture(uTexture, vTexCoords*uTextureRepeat).rgb;
}
