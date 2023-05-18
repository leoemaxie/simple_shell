#include "hash.h"

char *read_shell(void)
{
	int nreads = 0;
	char *str = NULL;
	size_t n = 0;

	while (1)
	{
		nreads = _getline(&str, &n, STDIN_FILENO);
		if (nreads == -1)
			return (NULL);
		if (nreads == 0)
			break;
	}
	return (str);
}

int shell_exec(void)
{
	char *cmd_arr;

	while (1)
	{
		write(STDOUT_FILENO, "($) ", 4);
		cmd_arr = read_shell();
		free(cmd_arr);
	}
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
	if (av[1])
		;
	else
		shell_exec();

	return (0);
}
