R""(
#version 460 core
layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoord;

/* for instance drawing
layout (location = 0) in vec2   aPos;
layout (location = 1) in vec2   aTexCoord;
layout (location = 2) in vec2   aTexDisp;
layout (location = 2) in vec2   aTexSize;
layout (location = 4) in vec4   aColor;
layout (location = 5) in float  aRotation; //in radians
*/

out vec2 TexCoord; //essentially just the displacement from bl 

//texcoord transformation
uniform vec2 tcDisplacement;
uniform vec2 tcSize;

uniform mat4 projection;
uniform mat4 model;

//a is in radians, not degrees
vec2 rotate(vec2 v, float a) {
	float s = sin(a);
	float c = cos(a);
	mat2 m = mat2(c, -s, s, c);
	return m * v;
}

void main() {
  gl_Position = projection * model * vec4(aPos, 0, 1.0);
  TexCoord = (aTexCoord * tcSize) + tcDisplacement;
}
)""
