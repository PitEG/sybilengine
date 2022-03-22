R""(
#version 460 core
out vec4 FragColor;

in vec2 TexCoords;
in vec4 Color;
in flat int Enabled;

uniform sampler2D texture1;

void main() {
  if (Enabled == 0) { return; }
  FragColor = Color * texture(texture1, TexCoords);
}
)""