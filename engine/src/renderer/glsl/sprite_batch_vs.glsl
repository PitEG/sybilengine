R""(
#version 460 core
layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec3 instancePos;

out vec3 color;

void main() {
  gl_Position = vec4(inPos + instancePos, 1);
  color = inColor;
}
)""
