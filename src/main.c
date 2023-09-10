#include "linmath.h"
#include "shader.h"
#include <GL/glew.h>
#include <stdio.h>
#include <stdlib.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

void calcView(mat4x4 mvp, vec3 eye, vec3 center, vec3 up);

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
  // [x, y, z]
  static const GLfloat vertices[] = {
      -1.0f, -1.0f, -1.0f,                      // triangle 1 : begin
      -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  // triangle 1 : end
      1.0f,  1.0f,  -1.0f,                      // triangle 2 : begin
      -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, // triangle 2 : end
      1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,
      1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,
      -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,  -1.0f, 1.0f,
      -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f,
      -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f,
      -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  1.0f,
      1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, -1.0f,
      1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,
      1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  -1.0f, 1.0f};

  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  //===
  // Vertex Array Buffer
  //===
  unsigned int VBO;
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);

  // Load the vertices into the vertex array buffer
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  // [y, y, z]
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(0);

  //===
  // Color Buffer
  //===
  static const GLfloat colors[] = {
      0.583f, 0.771f, 0.014f, 0.609f, 0.115f, 0.436f, 0.327f, 0.483f, 0.844f,
      0.822f, 0.569f, 0.201f, 0.435f, 0.602f, 0.223f, 0.310f, 0.747f, 0.185f,
      0.597f, 0.770f, 0.761f, 0.559f, 0.436f, 0.730f, 0.359f, 0.583f, 0.152f,
      0.483f, 0.596f, 0.789f, 0.559f, 0.861f, 0.639f, 0.195f, 0.548f, 0.859f,
      0.014f, 0.184f, 0.576f, 0.771f, 0.328f, 0.970f, 0.406f, 0.615f, 0.116f,
      0.676f, 0.977f, 0.133f, 0.971f, 0.572f, 0.833f, 0.140f, 0.616f, 0.489f,
      0.997f, 0.513f, 0.064f, 0.945f, 0.719f, 0.592f, 0.543f, 0.021f, 0.978f,
      0.279f, 0.317f, 0.505f, 0.167f, 0.620f, 0.077f, 0.347f, 0.857f, 0.137f,
      0.055f, 0.953f, 0.042f, 0.714f, 0.505f, 0.345f, 0.783f, 0.290f, 0.734f,
      0.722f, 0.645f, 0.174f, 0.302f, 0.455f, 0.848f, 0.225f, 0.587f, 0.040f,
      0.517f, 0.713f, 0.338f, 0.053f, 0.959f, 0.120f, 0.393f, 0.621f, 0.362f,
      0.673f, 0.211f, 0.457f, 0.820f, 0.883f, 0.371f, 0.982f, 0.099f, 0.879f};

  GLuint colorbuffer;
  glGenBuffers(1, &colorbuffer);
  glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
  glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)0);
  glEnableVertexAttribArray(1);

  //===
  // Element Buffer Object
  //===
  /*unsigned int EBO;*/
  /*unsigned int indicies[] = {*/
  /*0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14, 15, 16, 17,*/
  /*18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,*/
  /*};*/

  /*glGenBuffers(1, &EBO);*/

  /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);*/
  /*glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies,*/
  /*GL_STATIC_DRAW);*/

  GLuint MatrixID = glGetUniformLocation(shader.ID, "MVP");

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  //=============
  // main loop
  //=============

  // Enable our shader
  glUseProgram(shader.ID);

  mat4x4 mvp;

  vec3 eye = {4, 3, 3};
  vec3 center = {0, 0, 0};
  vec3 up = {0, 1, 0};

  while (!glfwWindowShouldClose(window)) {
    calcView(mvp, eye, center, up);

    // Clear the screen
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

    // Render the buffer
    glBindVertexArray(VAO);
    /*glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, 0);*/
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  // Cleanup
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VAO);
  /*glDeleteBuffers(1, &EBO);*/

  shader_destroy(&shader);

  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}

void calcView(mat4x4 mvp, vec3 eye, vec3 center, vec3 up) {
  mat4x4 projection;
  mat4x4_perspective(projection, 0.785398, 1.0, 0.01, 100.);

  mat4x4 view;
  mat4x4_look_at(view, eye, center, up);

  mat4x4 model = {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}};

  mat4x4_mul(mvp, projection, view);
  mat4x4_mul(mvp, mvp, model);
}
