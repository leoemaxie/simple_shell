#ifndef _HASH_H_
#define _HASH_H_

#define BUFF_SIZE 1024

/** Includes **/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/***** Declarations *****/
ssize_t getline(char **lineptr, size_t *n, FILE *stream);

/** write_output **/
int _putchar(int c);
int _puts(const char *s);

#endif
