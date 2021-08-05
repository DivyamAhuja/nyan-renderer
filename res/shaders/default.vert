#version 330

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTex;

uniform float scale;

out vec3 color;
out vec2 texCoord;

void main() {
  color = aColor;
  texCoord = aTex;
  gl_Position = vec4(aPos * (1.0 + scale), 1.0);
}
