R""(
#version 460 core
out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D texture1;
uniform vec4      color = vec4(1,1,1,1);

void main() {
  FragColor = color * texture(texture1, TexCoord);
}
)""
