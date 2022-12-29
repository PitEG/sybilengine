R""(
#version 460 core
out vec4 FragColor;

uniform sampler2D texture0;

void main() {
  // FragColor = texture(texture0, vec2(1,1));
  FragColor = vec4(1,1,1,1);
}
)""
