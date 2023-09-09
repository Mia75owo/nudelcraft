#ifndef UTILS_H_
#define UTILS_H_

// Trys to read a file from filepath into a string which must be freed
// Returns NULL on failure
const char* file_to_string(const char* filepath);

#endif
