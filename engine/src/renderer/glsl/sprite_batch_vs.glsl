R""(
#version 460 core
// base vertex stuff
layout (location = 0) in vec2 aPos;

// instance stuff
layout (location = 1) in vec2 position;
layout (location = 2) in vec4 color;

out vec4 inColor;
out vec2 inTexCoords;

void main() {
  gl_Position = vec4(aPos + position, 1, 1);
  inTexCoords = aPos + vec2(0.5,0.5);
  inColor = color;
}
)""
