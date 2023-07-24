#include "hash.h"

/**
 * get_cmd_path - Adds, changes, and deletes environment variables.
 *
 * @cmd: Pointer to a character string that contains the name of the
 * command a user input into the shell.
 * @err: Error structure containing the nature of the erroroccured while
 * executing shell commands.
 *
 * Return: A pointer to the path of the command or NULL on error.
 */
char *get_cmd_path(const char *cmd, err_t err)
{
	char *path = _getenv("PATH");
	char *token = strtok(path, ":");
	char cmd_path[BUFF_SIZE];
	char *ptr;

	while (token != NULL)
	{
		_strcpy(cmd_path, token);
		_strcat(cmd_path, "/");
		_strcat(cmd_path, cmd);

		if (access(cmd_path, X_OK) == 0)
		{
			ptr = cmd_path;
			return (ptr);
		}
		token = strtok(NULL, ":");
	}

	err.print(err);
	return (NULL);
}

int _exec(int fd, err_t err)
{
	size_t n = 0;
	int status;
	char *cmd_arr;
	char *cmd;
	char **tokens;

	if (_getline(&cmd_arr, &n, fd) == -1)
		return (-1);

	tokens = tokenize(cmd_arr);
	if (tokens == NULL)
		return (-1);

	cmd = _strdup(tokens[0]);
	if (cmd != NULL)
	{
		free(tokens[0]);
		tokens++;
	}

	if (!exec_builtin(cmd, tokens, err))
		status = sysexec(cmd, tokens, err);
	
	free(cmd);
	free(cmd_arr);
	free_tokens(tokens);
	
	return (0);
}

int sysexec(char *cmd, char **tokens, err_t err)
{
	int status;
	pid_t pid;
	char *path = get_cmd_path(cmd);

	if (path == NULL)
		return (-1);

	pid = fork();

	if (pid < 0)
	{
		err.print(err);
		return (0);
	}
	else if (pid == 0)
	{
		(execve(cmd, token, environ) == -1)
		{
			err.print(err);
			return (-1);
		}
	}
	return (0);
}
