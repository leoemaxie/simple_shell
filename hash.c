#include "hash.h"

/**
 * shell_exec - Executes a shell command.
 *
 * @name: The name of the program.
 *
 * Return: Nothing.
 */
void shell_exec(char *name)
{
	err_t err = {NULL, 0, printerr};

	err.name = name;
	while (1)
	{
		signal(SIGINT, signal_handler);
		err.lineno++;
		write(STDOUT_FILENO, "($) ", 4);
		_exec(STDIN_FILENO, err);
	}
}

/**
 * file_exec- Executes shell commands from a file.
 *
 * @argv: Array of command line arguments.
 *
 * Return: Nothing.
 */
int file_exec(char **argv)
{
	int fd = getfd(argv[1]);
	err_t err = {NULL, 0, printerr};

	err.name = argv[0];

	if (fd == -1)
	{
		char *msg = create_err(err);

		write(STDERR_FILENO, msg, _strlen(msg));
		write(STDERR_FILENO, ": ", 2);
		write(STDERR_FILENO, "Can't open ", 11);
		write(STDERR_FILENO, argv[1], _strlen(argv[1]));
		write(STDERR_FILENO, "\n", 1);
		free(msg);
		exit(127);
	}

	while (1)
	{
		if (_exec(fd, err) == -1)
			err.print(err);
		err.lineno++;
	}

	if (close(fd) == -1)
	{
		err.print(err);
		exit(127);
	}
}

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

	err.name = av[0];
	(void)av;
	(void)ac;

	if (ac > 1)
		file_exec(av);

	else if (!isatty(STDIN_FILENO))
		return (_exec(STDIN_FILENO, err));

	shell_exec(av[0]);

	return (0);
}
