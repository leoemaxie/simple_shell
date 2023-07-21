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


int _exec(int fd, char **env)
{
	int b;
	size_t n = 0;
	int status;
	pid_t pid;
	char *cmd_arr;
	char *token;

	if (_getline(&cmd_arr, &n, fd) == -1)
		return (-1);

	token = strtok(cmd_arr, " ");
	while (token != NULL)
	{
		token = strtok(NULL, " ");
		
		/*if (fork() == -1)
			_exit(1);
		else 
		{
			char *params[2] = {token, NULL};
			char *r[2] = {token, NULL};
			if (execve(token, params, r) == -1)
				return (-1);
			wait(&status);
		}*/
	}
	free(cmd_arr);
	//printenv(env);

	return (0);
}


void shell_exec(char **env)
{
	while (1)
	{
		write(STDOUT_FILENO, "($) ", 4);
		if (_exec(STDOUT_FILENO, env) == -1)
		{
			perror(PROGRAM_NAME);
			continue;
		}
	}

}

int file_exec(char *filename, char **env)
{
	int fd = getfd(filename);
	int line_no = 0;

	if (fd == -1)
		die(PROGRAM_NAME);

	while (1)
	{
		if (_exec(fd, env) == -1)
		{
			dprintf(STDERR_FILENO, "%s: %d: %s", PROGRAM_NAME, line_no, strerror(errno));
			continue;
		}
		line_no++;
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
	if (ac > 1)
		file_exec(av[1], env);

	else
		shell_exec(env);

	return (0);
}
