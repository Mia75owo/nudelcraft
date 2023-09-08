#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>
#include "shader.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}
void error_callback(int error, const char *description) {
  printf("%s\n", description);
}

int main(int argc, char **argv) {
  GLFWwindow *window;

  glfwSetErrorCallback(error_callback);

  if (!glfwInit()) {
    exit(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  window = glfwCreateWindow(800, 800, "nudelcraft", NULL, NULL);
  if (!window) {
    glfwTerminate();
    exit(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  //=============
  // GL
  //=============

  glewInit();
  Shader shader;
  shader_init(&shader, "src/shaders/vertex.glsl", "src/shaders/fragment.glsl");

  float vertices[] = {
      -1.0f, -1.0f, -0.0f, 1.0f, 1.0f,  -0.0f,
      -1.0f, 1.0f,  -0.0f, 1.0f, -1.0f, -0.0f,
  };
  unsigned int indicies[] = {0, 1, 2, 0, 3, 1};

  unsigned int VAO, VBO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  //=============
  // main loop
  //=============

  glUseProgram(shader.ID);
  
  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
