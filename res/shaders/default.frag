#version 330

layout(location = 0) out vec4 frag_colour;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main() {
  frag_colour = texture(tex0, texCoord);
}
