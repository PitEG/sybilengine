R""(
#version 460 core
// base vertex stuff
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

// instance stuff
layout (location = 2) in vec2 position;

out vec3 color;

void main() {
  gl_Position = vec4(aPos + vec3(position,0), 1);
  color = aColor;
}
)""
