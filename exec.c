#include "hash.h"

/**
 * get_cmd_path - Adds, changes, and deletes environment variables.
 *
 * @cmd: Pointer to a character string that contains the name of the
 * command a user input into the shell.
 *
 * Return: A pointer to the path of the command or NULL on error.
 */
char *get_cmd_path(char *cmd)
{
	char *path = _getenv("PATH");
	char *token;
	char *cmd_path = malloc(_strlen(cmd) + _strlen(path) + 2);

	if (cmd_path == NULL || path == NULL)
		return (NULL);

	token = _strtok(path, ":");
	free(path);

	while (token != NULL)
	{
		_strcpy(cmd_path, token);
		_strcat(cmd_path, "/");
		_strcat(cmd_path, cmd);

		if (access(cmd_path, X_OK) == 0)
			return (cmd_path);

		token = _strtok(NULL, ":");
	}

	return (NULL);
}

int _exec(int fd, err_t err)
{
	int status = 0;
	size_t n = 0;
	char *cmd_arr;
	char **tokens;

	get_initial_env_len();
	if (_getline(&cmd_arr, &n, fd) == -1)
	{
		free(cmd_arr);
		return (-1);
	}

	tokens = tokenize(cmd_arr);
	if (tokens == NULL)
		return (-1);

	if (!exec_builtin(tokens[0], tokens, err))
		status = sysexec(tokens[0], tokens, err);

	free(cmd_arr);
	free_tokens(tokens);

	if (status == -1)
	{
		err.print(err);
		return (-1);
	}
		
	return (0);
}

int sysexec(char *cmd, char **tokens, err_t err)
{
	pid_t pid;
	char *path = get_cmd_path(cmd);

	if (path == NULL)
	{
		free(path);
		return (-1);
	}

	pid = fork();

	if (pid < 0)
	{
		err.print(err);
		 return (-1);
	}
	else if (pid == 0)
	{
		if (execve(path, tokens, environ) == -1)
		{
			err.print(err);
			return (-1);
		}
	}
	return (1);
}
