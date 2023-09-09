#ifndef SHADER_H_
#define SHADER_H_

typedef struct {
  unsigned int ID;
} Shader;

// Generates a GLProgram from the file path of a vertex and a fragment shader
int shader_init(Shader* self, const char* vertex_path, const char* fragment_path);
// Cleans up the shader
void shader_destroy(Shader* self);

#endif
