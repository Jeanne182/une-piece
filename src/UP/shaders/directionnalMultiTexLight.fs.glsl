#version 330

// Entrées du shader
in vec3 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec3 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

// Sorties
out vec3 fFragColor;

// Uniforms
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

uniform sampler2D uTexture_diffuse1;
uniform sampler2D uTexture_specular1;

uniform float uTextureRepeat;

vec3 blinnPhong() {
  vec3 wi = normalize(uLightDir_vs);
  vec3 halfVector = normalize(-vPosition_vs);
  vec3 p1 = uKd*(dot(wi, vNormal_vs));
  vec3 p2 = uKs*pow((dot(halfVector, vNormal_vs)), uShininess);
  vec3 color = uLightIntensity*(p1+p2);
  return color;
}

void main() {
  vec3 tx1 = texture(uTexture_diffuse1, vTexCoords * uTextureRepeat).xyz;
  vec3 tx2 = texture(uTexture_specular1, vTexCoords * uTextureRepeat).xyz;
  vec3 tx = mix(tx1, tx2, 0.5);
  float mixer = 0.2;
  fFragColor = tx * blinnPhong()*(1-mixer) + tx*(mixer);
}
