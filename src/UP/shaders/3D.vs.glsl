#version 330 core

// Attributs de sommet
layout(location = 0) in vec3 aVertexPosition; // Position
layout(location = 1) in vec3 aVertexNormal; // Normale
layout(location = 2) in vec2 aVertexTexCoords; // Coordonnées de texture

// Matrices de transformations reçues en uniform
uniform mat4 uMVPMatrix;
uniform mat4 uMVMatrix;
uniform mat4 uNormalMatrix;

// Sorties du shader
out vec4 vPosition_vs; // Position du sommet transformé dans l'espace View
out vec4 vNormal_vs; // Normale du sommet transformé dans l'espace View
out vec2 vTexCoords; // Coordonnées de texture du sommet

void main() {
  /* Passage en coordonnées homogènes */
  vec4 vertexPosition = vec4(aVertexPosition, 1.0);
  vec4 vertexNormal = vec4(aVertexNormal, 0.0);
  
  /* Position et normales en View Coordinates */
  vPosition_vs = (uMVMatrix * vertexPosition);
  vNormal_vs = (uNormalMatrix * vertexNormal);
  vTexCoords = aVertexTexCoords;
  
  /* Calcul de la position */
  gl_Position = uMVPMatrix * vertexPosition;
}
