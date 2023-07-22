#include "hash.h"

/**
 * die - Terminates the current shell execution if an error occurs and prints
 * the error to STDERR.
 *
 * @s: The error to print.
 *
 * Return: Nothing.
 */
void die(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

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
		die("hash");

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
	char *ptr = malloc(len);
	char buf[len];

	if (ptr == NULL)
		return (NULL);

	buf[len] = '\0';
	while (lineno)
	{
		buf[--len] = (lineno % 10) + '0';
		lineno /= 10;
	}

	for (i = 0; buf[len]; i++, len++)
		ptr[i] = buf[len];
	ptr[i] = '\0';

	return (ptr);
}

/**
 * printerr - Prints error message to stderr.
 *
 * @err: Error structure containing the nature of the error while executing
 * shell commands.
 *
 * Return: Nothing.
 */
void printerr(err_t err)
{
	int i, j;
	char msg[BUFF_SIZE];
	char *num_str = strnum(err.lineno);

	for (i = 0; i < BUFF_SIZE; i++)
	{
		for (j = 0; err.name[j]; j++)
			msg[i++] = err.name[j];
		msg[i++] = ':';
		msg[i] = ' ';

		if (num_str != NULL)
			for (j = 0; num_str[j]; j++)
				msg[++i] = num_str[j];

		msg[i] = ':';
		msg[i++] = '\0';
		free(num_str);
		break;
	}
	perror(msg);
}

