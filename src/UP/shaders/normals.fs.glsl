#version 330

// Entrées du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

out vec3 fFragColor;

uniform vec3 uColor;

void main() {
  if (uColor == vec3(0.0, 0.0, 0.0))
  {
  }
  else
  {
  fFragColor = uColor;
  }
  fFragColor = normalize(vNormal_vs);
}
