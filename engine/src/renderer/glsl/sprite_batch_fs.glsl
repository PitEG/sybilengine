R""(
#version 460 core
out vec4 FragColor;

in vec4 inColor;
in vec2 inTexCoords;

uniform sampler2D texture0;

void main() {
  FragColor = texture(texture0, inTexCoords);
  // FragColor = inColor * texture(texture0, vec2(1,1));
}
)""
