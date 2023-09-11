#include "shader.h"
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

// Handle resize
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

  // Set openGL version
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create a window
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
  // Create our shader
  Shader shader;
  shader_init(&shader, "src/shaders/vertex.glsl", "src/shaders/fragment.glsl");

  //===
  // Vertex Array Object
  //===
  unsigned int VAO;

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  //===
  // Vertex Buffer Object
  //===
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // [x, y, z]+[r, g, b]
  float vertices[] = {
      -0.5f, -0.5f, 0.0f, 1.0, 0.0, 0.0, // 1
      0.5f,  -0.5f, 0.0f, 0.0, 1.0, 0.0, // 2
      0.0f,  0.5f,  0.0f, 0.0, 0.0, 1.0, // 3
  };

  // Copy the date into the buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // tell openGL how to interpret the data in the array
  // [x, y, z]
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  // [r, g, b] (with 3 floats of offset)
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  //===
  // Element Buffer Object
  //===
  unsigned int EBO;
  unsigned int indicies[] = {0, 1, 2};

  glGenBuffers(1, &EBO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies,
               GL_STATIC_DRAW);

  //=============
  // main loop
  //=============

  // Enable our shader
  glUseProgram(shader.ID);

  while (!glfwWindowShouldClose(window)) {
    // Clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Render the buffer
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Cleanup
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VAO);
  glDeleteBuffers(1, &EBO);

  shader_destroy(&shader);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}
