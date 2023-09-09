#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *file_to_string(const char *filepath) {
  char *buffer = NULL;
  long length = 0;
  FILE *file = fopen(filepath, "rb");

  if (!file) {
    printf(">! Failed to open file: %s\n", filepath);
    return NULL;
  }

  fseek(file, 0, SEEK_END);
  length = ftell(file);
  fseek(file, 0, SEEK_SET);
  buffer = malloc(length + 1);
  if (buffer) {
    memset(buffer, 0, length + 1);
    fread(buffer, 1, length, file);
  } else {
    printf(">! Failed to alloc buffer for file: %s\n", filepath);
    buffer = NULL;
  }
  fclose(file);

  return buffer;
}
