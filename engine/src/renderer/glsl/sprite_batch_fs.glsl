R""(
#version 460 core
out vec4 FragColor;

in vec4 inColor;

void main() {
  FragColor = inColor;
  // FragColor = vec4(1);
}
)""
