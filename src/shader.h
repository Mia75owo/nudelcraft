#ifndef SHADER_H_
#define SHADER_H_

typedef struct {
  unsigned int ID;
} Shader;

int shader_init(Shader* self, const char* vertex_path, const char* fragment_path);

#endif
