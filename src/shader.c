#include "shader.h"
#include "utils.h"
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

int shader_init(Shader *self, const char *vertex_path,
                const char *fragment_path) {
  int success = 1;
  char info_log[512];
  unsigned int vertex, fragment;

  const char *vertex_content = file_to_string(vertex_path);
  const char *fragment_content = file_to_string(fragment_path);

  // Compile vertex shader
  vertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex, 1, &vertex_content, NULL);
  glCompileShader(vertex);

  glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(vertex, 512, NULL, info_log);
    printf("%s\n", info_log);
  }

  // Compile fragment shader
  fragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment, 1, &fragment_content, NULL);
  glCompileShader(fragment);

  glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragment, 512, NULL, info_log);
    printf("%s\n", info_log);
  }

  // Link into program
  self->ID = glCreateProgram();
  glAttachShader(self->ID, vertex);
  glAttachShader(self->ID, fragment);
  glLinkProgram(self->ID);

  glGetProgramiv(self->ID, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(self->ID, 512, NULL, info_log);
    printf("%s\n", info_log);
  }

  // Clean up

  glDeleteShader(vertex);
  glDeleteShader(fragment);

  free((void *)vertex_content);
  free((void *)fragment_content);
  return 0;
}
