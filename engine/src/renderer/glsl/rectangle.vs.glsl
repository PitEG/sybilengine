R""(
#version 460 core
layout (location = 0) in vec2   aPos;
layout (location = 1) in vec2   aPosition;
layout (location = 2) in vec2   aSize;
layout (location = 3) in vec4   aColor; //origin

out vec4 Color;

uniform mat4 projection;

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
  // rotate along origin TODO: it only rotations along the center atm
  // mat4 rotation = rotate(model, aRotation);
  mat4 scale = scale(model, aSize);

  vec4 resultVector = translation * scale * vec4(aPos, 0 , 1);

  gl_Position = projection * resultVector; //vec4(aPos, 0, 1.0);
  //gl_Position = vec4(aPos, 0, 0);
  
  Color = aColor;
}
)""