#version 330 core

// Entrées du shader
in vec4 vPosition_vs; // Position du sommet transformé dans l'espace View
in vec4 vNormal_vs; // Normale du sommet transformé dans l'espace View
in vec2 vTexCoords; // Coordonnées de texture du sommet

// Sorties
out vec4 fFragColor;

// Uniforms
uniform vec3 uKd;
uniform vec3 uKs;
uniform float uShininess;

uniform vec3 uLightDir_vs;
uniform vec3 uLightIntensity;

uniform vec3 viewPos;
uniform vec3 lightPos;

uniform sampler2D uTexture_diffuse1;
uniform sampler2D uTexture_specular1;

uniform float uTextureRepeat;

uniform vec3 uColor;

void main() {    
  vec3 lightColor = vec3(1.0f, 1.0f, 1.0f) * uLightIntensity;
  
  // Texture
  vec3 tx1 = texture(uTexture_diffuse1, vTexCoords * uTextureRepeat).xyz;
  vec3 tx2 = texture(uTexture_specular1, vTexCoords * uTextureRepeat).xyz;
  vec3 tx = mix(tx1, tx2, 0.5);
  
  // Ambient
  float ambientStrength = 0.25;
  vec3 ambient = ambientStrength * lightColor;
  
  // Diffuse
  vec3 norm = normalize(vNormal_vs.xyz);
  vec3 lightDir = normalize(lightPos - vPosition_vs.xyz);
  float diff = max(dot(norm, lightDir), 0.0);
  vec3 diffuse = diff * lightColor;
  
  // Specular
  float specularStrength = 0.7;
  vec3 viewDir = normalize(viewPos - vPosition_vs.xyz);
  vec3 reflectDir = reflect(-lightDir, norm);
  float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16);
  vec3 specular = specularStrength * spec * lightColor;
  
  vec3 result = (ambient + diffuse + specular) * tx;
  fFragColor = vec4(result, 1.0);
  
  
  if (uColor != vec3(0.0))
  {
    fFragColor = vec4(uColor, 1.0);  
  }
  else
  {
    fFragColor = vec4(result, 1.0);
  }
}
