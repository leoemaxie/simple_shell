#include "hash.h"

/**
 * close_fd - Closes a file descriptor and prints an error message to STDERR
 * when an error is encountered.
 *
 * @fd: The file descriptor to close.
 *
 * Return: Nothing.
 */
void close_fd(int fd)
{
	close(fd);

}

/**
 * strnum - Converts the line number an error was encountered to a string.
 *
 * @lineno: Number of the line where an error was encountered.
 *
 * Return: The string representation of the number on success, NULL on error.
 */
char *strnum(unsigned int lineno)
{
	int i;
	unsigned int len = 11; /* Max number of digits of uint + NUL terminator */
	char *ptr;
	char buf[11];

	buf[len] = '\0';
	while (lineno)
	{
		buf[--len] = (lineno % 10) + '0';
		lineno /= 10;
	}

	ptr = malloc(12 - len);
	if (ptr == NULL)
		return (NULL);

	for (i = 0; len < 11; i++, len++)
		ptr[i] = buf[len];

	ptr[i] = '\0';
	return (ptr);
}

/**
 * create_err - Creates an error message.
 *
 * @err: Error structure containing the nature of the error while executing
 * shell commands.
 *
 * Return: Nothing.
 */
char *create_err(err_t err)
{
	int i, j;
	char *msg = malloc(BUFF_SIZE);
	char *num_str = strnum(err.lineno);

	if (msg == NULL)
		return (NULL);
	for (i = 0; i < BUFF_SIZE; i++)
	{
		for (j = 0; (err.name)[j]; j++)
			msg[i++] = (err.name)[j];
		msg[i++] = ':';
		msg[i++] = ' ';

		if (num_str != NULL)
			for (j = 0; num_str[j]; j++)
				msg[i++] = num_str[j];

		msg[i] = ':';
		msg[i++] = '\0';
		free(num_str);
		break;
	}

	return (msg);
}

/**
 * printerr - Prints system error message to stderr.
 *
 * @err: Error structure containing the nature of the error while executing
 * shell commands.
 *
 * Return: Nothing.
 */
void printerr(err_t err)
{
	char *msg = create_err(err);

	if (msg)
		perror(msg);
	free(msg);
}

/**
 * perr - Prints a short message about the error occured while
 * executing commands to stderr.
 *
 * @tokens: An array of token strings.
 * shell commands.
 * @msg: Error message to print.
 * @err: Error structure containing the nature of the error while executing
 * @is_builtin: Indicates whether a command is builtin or executed from a
 * syscall.
 *
 * Return: Nothing.
 */
void perr(char **tokens, char *msg, err_t err, int is_builtin)
{
	char *error = create_err(err);
	int size = 5; /* Extra delimiters */
	char *err_msg = NULL;

	if (error)
	{
		size += (_strlen(error) + _strlen(msg) + _strlen(tokens[0]));

		if (tokens[1] && is_builtin)
			size += _strlen(tokens[1]) + 2;

		err_msg = malloc(size);
		if (err_msg)
		{
			_strcpy(err_msg, error);
			_strcat(err_msg, ": ");
			_strcat(err_msg, tokens[0]);
			_strcat(err_msg, ": ");

			if (is_builtin && tokens[1])
			{
				_strcat(err_msg, tokens[1]);
				_strcat(err_msg, ": ");
			}
			_strcat(err_msg, msg);
			write(STDERR_FILENO, err_msg, size);
			free(err_msg);
		}
	}
	free(error);
}
