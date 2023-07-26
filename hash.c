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

void shell_exec(err_t err)
{
	while (1)
	{
		write(STDOUT_FILENO, "($) ", 4);
		_exec(STDIN_FILENO, err);
	}
}

int file_exec(char *filename, err_t err)
{
	int fd = getfd(filename);

	if (fd == -1)
		err.print(err);

	while (1)
	{
		if (_exec(fd, err) == -1)
		{
			/*err.print(err);*/
			continue;
		}
		err.lineno++;
	}

	close_fd(fd);
}
/*
void cleanup(err_t *e)
{
	free(e->name);
	free(e->msg);
}

void perr(err_t err)
{
	//seterr(&err);
	perror(err.msg);
}*/
/**
 * main - Runs the hash shell.
 *
 * @ac: The number of command line argunents.
 * @av: An array of command line argunents.
 *
 * Return: 0.
 */
int main(int ac, char **av)
{
	err_t err = {NULL, 1, printerr};

	(void)av;
	(void)ac;

	err.name = av[0];


	if (ac > 1)
		file_exec(av[1], err);

	else if (!isatty(STDIN_FILENO))
		_exec(STDIN_FILENO, err);
	else
		shell_exec(err);

	return (0);
}
