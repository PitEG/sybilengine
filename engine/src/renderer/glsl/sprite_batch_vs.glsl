R""(
#version 460 core
// base vertex stuff
layout (location = 0) in vec2 aPos;

// instance stuff
layout (location = 1) in vec2 aPosition;
layout (location = 2) in vec4 aColor;
layout (location = 3) in vec2 aOrigin;
layout (location = 4) in vec2 aScale;
layout (location = 5) in float aRotation;

uniform mat4 projection;

out vec4 inColor;
out vec2 inTexCoords;

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
  mat4 rotation = rotate(model, aRotation);
  mat4 scale = scale(model, aScale);
  // vec4 compound = translation * rotation * scale * vec4(aPos, 0 , 1);

  vec4 compound = translation * rotation * scale * vec4(aPos,0,1);

  // gl_Position = vec4(aPos + position, 1, 1);
  gl_Position = projection * compound;// * projection;
  inTexCoords = aPos + vec2(0.5,0.5);
  inColor = aColor;
}
)""
