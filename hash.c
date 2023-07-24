#include "hash.h"

/**
 * read_input - Reads any input/data/files/commands entered into the shell
 * one line at a time and copies into a buffer and terminates it with a NUL.
 *
 * @buf: Pointer to a buffer to copy read input into.
 * @fd: The file descriptor to read from.
 *
 * Return: 1 on Successful read, 0 on failure.
 */
int read_input(char **buf, int fd)
{
	size_t n = 0;
	//int nreads = _getline(buf, &n, fd);
	int nreads = getline(buf, &n, stdin);

	if (nreads == -1)
		return (1);
	return (0);
}


void shell_exec(err_t)
{
	while (1)
	{
		write(STDOUT_FILENO, "($) ", 4);
		if (_exec(STDOUT_FILENO, env) == -1)
		{
			continue;
		}
	}
}

int file_exec(char *filename, err_t err)
{
	int fd = getfd(filename);

	if (fd == -1)
		err.printerr(err);

	while (1)
	{
		if (_exec(fd, env) == -1)
		{
			err.printerr(err);
			continue;
		}
		err.lineno++;
	}

	close_fd(fd);
}
/**
 * main - Runs the hash shell.
 *
 * @ac: The number of command line argunents.
 * @av: An array of command line argunents.
 * @env: An array of enviromental variables
 *
 * Return: 0.
 */
int main(int ac, char **av, char **env)
{
	char *msg = av[0];
	err_t err = {av[0], 0, printerr};

	if (ac > 1)
		file_exec(av[1], err);

	else
		shell_exec(err);

	return (0);
}
