#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *file_to_string(const char *filepath) {
  char *buffer = NULL;
  long length = 0;
  // Open the file
  FILE *file = fopen(filepath, "rb");

  if (!file) {
    printf(">! Failed to open file: %s\n", filepath);
    return NULL;
  }

  // Go to the end of the file
  fseek(file, 0, SEEK_END);
  // Get the position of the cursor (end of file)
  length = ftell(file);
  fseek(file, 0, SEEK_SET);
  // Allocate enough memory for the file length
  buffer = malloc(length + 1);
  if (buffer) {
    // Clear the buffer
    memset(buffer, 0, length + 1);
    // Read the file into the buffer
    fread(buffer, 1, length, file);
  } else {
    printf(">! Failed to alloc buffer for file: %s\n", filepath);
    buffer = NULL;
  }
  // Close the file
  fclose(file);

  return buffer;
}
