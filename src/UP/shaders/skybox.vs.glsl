#version 330 core

layout (location = 0) in vec3 aPosition;

out vec3 vTexCoords;

uniform mat4 uProj;
uniform mat4 uView;

void main()
{
    vTexCoords = aPosition;
    //vec4 pos = uProjection * uView * vec4(aPosition, 1.0);
    vec4 pos = uProj * uView * vec4(aPosition, 1.0);
    gl_Position = pos.xyww;
}  