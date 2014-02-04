#version 400 core
in vec3 inputColor;
in vec4 inputPosition;
out vec3 color;
void main(void) {
  color = inputColor;
  gl_Position = inputPosition;
}
