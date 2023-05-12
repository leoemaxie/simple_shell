#ifndef _HASH_H_
#define _HASH_H_

#define BUFF_SIZE 1024

/** Includes **/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/***** Declarations *****/
ssize_t _getline(char **lineptr, size_t *n, int fd);

/** tokenize **/
void tokenize(char *s, char **cmd_arr);

/** errors **/
void die(const char *s);
void close_fd(int fd);

/** string **/
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);

/** write_output **/
int _putchar(int c);
int _puts(const char *s);

#endif
