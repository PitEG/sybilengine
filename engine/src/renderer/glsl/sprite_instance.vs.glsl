R""(
#version 460 core
//change locations
layout (location = 0) in vec2   aPos;
layout (location = 1) in vec2   aTexCoord;
layout (location = 2) in vec2   aOrigin; //origin
layout (location = 3) in vec2   aPosition;
layout (location = 4) in float  aRotation; //in radians
layout (location = 5) in vec2   aScale; 
layout (location = 6) in vec4   aColor;
layout (location = 7) in vec2   aTexDisp;
layout (location = 8) in vec2   aTexSize;
layout (location = 9) in int    aEnabled;

out vec2 TexCoords;
out vec4 Color;
out int  Enabled;

uniform mat4 projection;

mat4 rotate(mat4 model, float angle) {
  model[0][0] = cos(angle);
  model[0][1] = sin(angle);
  model[1][0] = -sin(angle);
  model[1][1] = cos(angle);

  return model;
}

mat4 translate(mat4 model, vec2 translation) {
  model[3][0] += translation.x;
  model[3][1] += translation.y;
  
  return model;
}

mat4 scale(mat4 model, vec2 scale) {
  model[0][0] *= scale.x;
  model[1][1] *= scale.y;
  
  return model;
}

void main() {
  mat4 model = mat4(1.0); //identity matrix

  mat4 translation = translate(model, aPosition);
  //rotate along origin TODO: it only rotations along the center atm
  mat4 rotation = rotate(model, aRotation);
  mat4 scale = scale(model, aScale);

  vec4 resultVector = translation * rotation * scale * vec4(aPos, 0 , 1);

  gl_Position = projection * resultVector; //vec4(aPos, 0, 1.0);
  //gl_Position = vec4(aPos, 0, 0);

  TexCoords = (aTexCoord * aTexSize) + aTexDisp;
  
  Color = aColor;
  Enabled = aEnabled;
}
)""
