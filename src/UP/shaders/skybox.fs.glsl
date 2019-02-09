#version 330 core
out vec4 fFragColor;

in vec3 vTexCoords;

uniform samplerCube uSkybox;

void main()
{    
  fFragColor = texture(uSkybox, vTexCoords);
  //fFragColor = vec4(0.2, 0.3, 1.0, 0.3);
  //fFragColor = vec4(normalize(vTexCoords), 1.0);
}