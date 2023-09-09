#version 330 core

layout (location = 0) in vec3 pos;

void main()
{
  // Pass the position without modifying it
  gl_Position = vec4(pos.xyz, 1.0);
}
