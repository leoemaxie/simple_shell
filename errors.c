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
	if (close(fd) == -1)
		;

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

	ptr = malloc(11 - len);
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
 * print_cmd_err  - Prints a short message about the error occured while
 * executing builtin commands to stderr.
 *
 * @err: Error structure containing the nature of the error while executing
 * shell commands.
 * @msg: Error message to print.
 *
 * Return: Nothing.
 */
void print_cmd_err(char *cmd, char *msg, err_t err)
{
	char *error = create_err(err);

	if (error)
	{
		write(STDERR_FILENO, error, _strlen(error));
		write(STDERR_FILENO, cmd, _strlen(cmd));
		write(STDERR_FILENO, cmd, _strlen(cmd));
		write(STDERR_FILENO, msg, _strlen(msg));
		free(error);
	}
}

/**
 * print_builtin_err - Prints a short message about the error occured while
 * executing builtin commands to stderr.
 *
 * @err: Error structure containing the nature of the error while executing
 * shell commands.
 * @msg: Error message to print.
 *
 * Return: Nothing.
 */
void print_builtin_err(char **tokens, char *msg, err_t err)
{
	char *error = create_err(err);
	int size = 6; /* Extra delimiters */
	char *err_msg = NULL;

	if (error)
	{
		size += (_strlen(error) + _strlen(msg) + _strlen(tokens[0]));

		if (tokens[1])
			size += _strlen(tokens[1]);

		err_msg = malloc(size);
		if (err_msg)
		{
			_strcpy(err_msg, error);
			_strcat(err_msg, ": ");
			_strcat(err_msg, tokens[0]);
			_strcat(err_msg, ": ");

			if (tokens[1])
			{
				_strcat(err_msg, tokens[1]);
				_strcat(err_msg, ": ");
			}
			_strcat(err_msg, msg);
			write(STDERR_FILENO, err_msg, size);
			free(err_msg);
		}
	}
}
