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

	if (cmd[0] == '/')
		return (cmd);

	while (token != NULL)
	{
		_strcpy(cmd_path, token);
		_strcat(cmd_path, "/");
		_strcat(cmd_path, cmd);

		if (access(cmd_path, X_OK) == 0)
		{
			free(path);
			return (cmd_path);
		}

		token = _strtok(NULL, ":");
	}

	free(path);
	free(cmd_path);
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
	{
		free(cmd_arr);
		free(tokens);
		return (-1);
	}

	if(_strcmp(tokens[0], "exit"))
		return (exit_shell(cmd_arr, tokens, err));
	
	if (!exec_builtin(tokens[0], tokens, err))
		status = sysexec(tokens[0], tokens, err);


	if (status == -2)
		perr(tokens, "Command Not Found\n", err, 0);

	free(cmd_arr);
	free_tokens(tokens);
		
	return (status);
}

int sysexec(char *cmd, char **tokens, err_t err)
{
	int status = 0;
	pid_t pid;
	char cmd_path[BUFF_SIZE];
	char *path = get_cmd_path(cmd);

	if (path == NULL)
	{
		free(path);
		return (-2);
	}

	_strcpy(cmd_path, path);
	free(path);

	pid = fork();

	if (pid < 0)
	{
		 err.print(err);
		 return (-1);
	}
	else if (pid == 0)
	{
		if (execve(cmd_path, tokens, environ) == -1)
		{
			err.print(err);
			return (-1);
		}
		wait(&status);
	}

	if (status == -1)
	{
		err.print(err);
		return (-1);
	}
	return (1);
}
