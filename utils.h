#ifndef UTILS_H
#define UTILS_H

int execute_and_capture(const char *filepath, char **buffer);

void run_background(const char *path, char *const argv[]);

#endif
