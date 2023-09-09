#version 330 core

layout(location = 0) out vec4 diffuseColor;
in vec3 vertexColor;

void main() {
  // Pass the color without modifying it
  diffuseColor = vec4(vertexColor.xyz, 1.0);
}
