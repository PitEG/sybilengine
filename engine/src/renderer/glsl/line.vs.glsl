R""(
#version 460 core
//change locations
layout (location = 0) in vec2   aPos; //fragment position
layout (location = 1) in vec4   aPosition; //buffer position
layout (location = 2) in vec4   aColor;

out vec4 Color;

uniform mat4 projection;

vec2 dot(vec2 a, vec2 b) {
  float x = a.x * b.x;
  float y = a.y * b.y;

  return vec2(x,y);
}

float magnitude(vec2 v) {
  return sqrt(pow(v.x, 2) + pow(v.y, 2));
}

void main() {
  mat4 model = mat4(1.0); //identity matrix
  vec2 a = aPosition.xy;
  vec2 b = aPosition.zw;
  vec2 diff = b - a;

  vec2 pos = aPos * diff;
  pos = pos + a;

  vec4 resultVector = vec4(pos, 1, 1);

  gl_Position = projection * resultVector; 
  
  Color = aColor;
}
)""
