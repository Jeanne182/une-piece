#version 300 es

precision highp float;

in vec2 vVertexCoord;
out vec4 fFragColor;

uniform sampler2D uTexture;

void main() {
  fFragColor = texture(uTexture, vVertexCoord);
}
