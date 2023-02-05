R""(
#version 460 core
layout (location = 0) in vec2 aPos;

out vec2 inTexCoords;

void main() {
  gl_Position = vec4(aPos,1,1);
  inTexCoords = aPos*0.5 + vec2(0.5,0.5);
}
)""
