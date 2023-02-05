R""(
#version 460 core

in vec2 inTexCoords;
out vec4 FragColor;

uniform sampler2D texture0;

void main() {
  // FragColor = texture(texture0, vec2(1,1));
  FragColor = texture(texture0, inTexCoords);
  // FragColor = vec4(1,1,1,1);
}
)""
