#ifndef _HASH_H_
#define _HASH_H_

#define BUFF_SIZE 1024
#define CTRL_KEY(k) ((k) & 0x1f)

/** Includes **/
#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

/**
 * struct error- Error structure for errors encountered while running a program.
 *
 * @name: Runtime name of the program.
 * @line: line number where error occured.
 * @print: pointer to the print function which prints an error msg to stderr.
*/
typedef struct error
{
	char *name;
	int line;
	void (*print)(struct error err);
} err_t;

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
void printerr(err_t err);

/** string.c **/
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, const char *src);
int _strlen(const char *s);

/** env.c **/
char *_getenv(const char *mame);
char *_get_env_index(const char *mame);
int _unsetenv(const char *mame);
void printenv(void);

/** write_output.c **/
int _putchar(int c);
int _puts(const char *s);

#endif
