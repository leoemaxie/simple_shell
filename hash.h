#ifndef _HASH_H_
#define _HASH_H_

#define BUFF_SIZE 1024
#define CTRL_KEY(k) ((k) & 0x1f)

/** Includes **/
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - contains pseudo-arguements to pass into a function,
 * allowing uniform prototype for function pointer struct
 * @arg: a string generated from getline of arguements
 * @argv:an array of strings generated from arg
 * @path: a string path for the current command
 * @argc: the argument count
 * @line_count: the error count
 * @err_num: the error code for exit()s
 * @linecount_flag: if on count this line of input
 * @fname: the program filename
 * @env: linked list local copy of environ
 * @environ: custom modified copy of environ from LL env
 * @history: the history node
 * @alias: the alias node
 * @env_changed: on if environ was changed
 * @status: the return status of the last exec'd command
 * @cmd_buf: address of pointer to cmd_buf, on if chaining
 * @cmd_buf_type: CMD_type ||, &&, ;
 * @readfd: the fd from which to read line input
 * @histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

extern char **environ;

/**
 * struct error- Error structure for errors encountered while executing
 * shell commands.
 *
 * @name: Runtime name of this shell program.
 * @lineno: Line number where error occured.
 * @msg: Error message to print.
 * @print: pointer to the print function which prints an error msg to stderr.
*/
typedef struct error
{
	char *name;
	unsigned int lineno;
	char *msg;
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
int arrlen(char **arr);
int cd(char **dirarr, err_t err);
int exec_builtin(char *cmd, char **tokens, err_t err);
int exit_shell(char **arr, err_t err);

/** getline.c **/
int getfd(const char *filename);
ssize_t _getline(char **lineptr, size_t *n, int fd);
int fill_buf(char **lineptr, char *buf, ssize_t old_len, ssize_t new_len);
int line_end(int c);
int resize(char **lineptr, ssize_t old_len, ssize_t new_len);

/** miscellenous */
int _atoi(const char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
int arrlen(char **arr);
void cleanup(err_t e);

/** tokenize.c **/
char *_strtok(char *s, const char *delim);
int is_delim(char c, const char *delim);
void free_tokens(char **token_arr);
int is_delim(char c, const char *delim);
char **tokenize(char *line);

/** exec.c **/
int _exec(int fd, err_t err);
char *get_cmd_path(char *cmd, err_t err);
int sysexec(char *cmd, char **tokens, err_t err);

/** errors.c **/
void close_fd(int fd);
void printerr(err_t err);
void print_builtin_err(char *msg, err_t err);
void seterr(err_t err);
char *strnum(unsigned int lineno);

/** string.c **/
char *_strcat(char *dest, const char *src);
int _strcmp(const char *s1, const char *s2);
char *_strcpy(char *dest, const char *src);
char *_strdup(char *str);
int _strlen(const char *s);

/** env.c **/
char *_getenv(const char *mame);
int _setenv(const char *name, const char *value, int overwrite);
int _unsetenv(const char *mame);
int printenv(char **dir, err_t err);

/** env_helper.c **/
int addenv(const char *name, const char *value);
void create_env(char **envptr, const char *name, const char *value);
void free_environ(char *env);
int get_env_index(const char *name);

/** write_output.c **/
int _putchar(int c);
int _puts(const char *s);

/* toem_errorsx.c */
void _eputs(char *);
int _eputchar(char);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

#endif
