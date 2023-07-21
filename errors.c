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

int cmd_exists(const char *cmd, err_t err)
{
	char *path = _getenv("PATH");
	char *token = strtok(path, ":");
	char cmd_path[BUFF_SIZE];

	while (token != NULL)
	{
		_strcpy(cmd_path, token);
		_strcat(cmd_path, "/");
		_strcat(cmd_path, cmd);

		if (access(cmd_path, X_OK) == 0)
			return (1);

		token = strtok(NULL, ":");
	}

	err.print(err);
	return (-1);
}

void printerr(err_t err)
{
	int i, j;
	char msg[BUFF_SIZE];

	for (i = 0; i < BUFF_SIZE; i++)
	{
		for (j = 0; err.name[j]; j++)
			msg[i++] = err.name[j];
		msg[i] = ':';

		while (err.line / 10)
		{
			msg[i++] = (err.line % 10) + '0';
			err.line /= 10;
		}

		msg[i] = ':';
		msg[i++] = '\0';
		break;
	}
	perror(msg);
}
