#ifndef _HASH_H_
#define _HASH_H_

#define BUFF_SIZE 1024
#define CTRL_KEY(k) ((k) & 0x1f)
#define PROGRAM_NAME (__FILE__)

/** Includes **/
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/***** Declarations *****/

/** builtin.c **/
int is_builtin(char *s);
void perform_builtin_cmd(int index, char **env);

/** getline.c **/
int getfd(const char *filename);
ssize_t _getline(char **lineptr, size_t *n, int fd);
int fill_buf(char **lineptr, char *buf, ssize_t old_len, ssize_t new_len);
int line_end(int c);
int resize(char **lineptr, ssize_t old_len, ssize_t new_len);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

/** tokenize **/
void tokenize(char *s, char **cmd_arr);

/** errors.c **/
void die(const char *s);
void close_fd(int fd);

/** string **/
int _strlen(const char *s);
int _strcmp(const char *s1, const char *s2);

/** env.c **/
char *_getenv(const char *mame);
char *_get_env_index(const char *mame);
int _unsetenv(const char *mame);
void printenv(void);

/** write_output.c **/
int _putchar(int c);
int _puts(const char *s);

#endif
