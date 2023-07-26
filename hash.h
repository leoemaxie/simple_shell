#ifndef _HASH_H_
#define _HASH_H_

#define BUFF_SIZE 1024
#define CTRL_KEY(k) ((k) & 0x1f)

/** Includes **/
#include <errno.h>
#include <fcntl.h>
#include <signal.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;

/**
 * struct error- Error structure for errors encountered while executing
 * shell commands.
 *
 * @name: Runtime name of this shell program.
 * @lineno: Line number where error occured.
 * @print: pointer to the print function which prints an error msg to stderr.
*/
typedef struct error
{
	char *name;
	unsigned int lineno;
	void (*print)(struct error err);
} err_t;

/**
 * struct builtin - Builtin structure for builtin shell commands.
 *
 * @exec: Pointer to an exec function of builtin commands.
 * @cmd: Name of the builtin command.
*/
typedef struct builtin
{
	int (*exec)(char **tokens, err_t err);
	char *cmd;
} btn_t;

/***** Declarations *****/

/** builtin.c **/
int cd(char **args, err_t err);
int exec_builtin(char *cmd, char **tokens, err_t err);
int exit_shell(char *cmd, char **args, err_t err);
int unsetenv_c(char **args, err_t err);
int setenv_c(char **args, err_t err);

/** errors.c **/
void close_fd(int fd);
char *create_err(err_t err);
void perr(char **tokens, char *msg, err_t err, int is_builtin);
void printerr(err_t err);
char *strnum(unsigned int lineno);

/** env_utils.c **/
int addenv(const char *name, const char *value);
void create_env(char **envptr, const char *name, const char *value);
int get_env_index(const char *name);
int get_initial_env_len(void);

/** env.c **/
char *_getenv(const char *mame);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *mame);
int printenv(char **args, err_t err);

/** exec.c **/
int _exec(int fd, err_t err);
char *get_cmd_path(char *cmd);
int sysexec(char *cmd, char **args, err_t err);

/** getline.c **/
int getfd(const char *filename);
ssize_t _getline(char **lineptr, size_t *n, int fd);
int fill_buf(char **lineptr, char *buf, ssize_t old_len, ssize_t new_len);
int line_end(int c);
int resize(char **lineptr, ssize_t old_len, ssize_t new_len);

/** hash.c **/
int file_exec(char **argv);
void shell_exec(char *name);

/** string.c **/
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, const char *src);
char *_strdup(char *str);
int _strlen(const char *s);

/** tokenize.c **/
char *_strtok(char *s, const char *delim);
int is_delim(char c, const char *delim);
void free_tokens(char **token_arr);
int is_delim(char c, const char *delim);
char **tokenize(char *line);

/** utils.c */
int _atoi(const char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int arr_size(char **arr);
void clean_env(void);

/** write_output.c **/
int _putchar(int c);
int _puts(const char *s);

#endif
