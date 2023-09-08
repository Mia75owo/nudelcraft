#include "utils.h"
#include <stdio.h>
#include <stdlib.h>

const char *file_to_string(const char *filepath) {
  char *buffer = NULL;
  long length;
  FILE *file = fopen(filepath, "rb");

  if (!file) {
    printf(">! Failed to open file: %s\n", filepath);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  length = ftell(file);
  fseek(file, 0, SEEK_SET);
  buffer = malloc(length);
  if (buffer) {
    fread(buffer, 1, length, file);
  } else {
    printf(">! Failed to alloc buffer for file: %s\n", filepath);
  }
  fclose(file);

  return buffer;
}
