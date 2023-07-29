#include "hash.h"

#include <stdio.h>
/**
 * get_cmd_path - Adds, changes, and deletes environment variables.
 *
 * @cmd: Pointer to a character string that contains the name of the
 * command a user input into the shell.
 * @path_stat: Pointer to an integer to set the status of the path.
 * 1 if path is provided e.g /bin/ls 0 if it isn't e.g ls.
 *
 * Return: A pointer to the path of the command or NULL on error.
 */
char *get_cmd_path(char *cmd, int *path_stat)
{
	char *path, *token, *cmd_path;

	if (cmd[0] == '/')
	{
		*path_stat = 1;
		if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}

	path = _getenv("PATH");
	if (path == NULL)
		return (NULL);
	cmd_path = malloc(_strlen(cmd) + _strlen(path) + 2);
	if (cmd_path == NULL)
	{
		if (path != NULL)
			free(path);
		return (NULL);
	}
	*path_stat = 0;
	token = _strtok(path, ":");

	while (token != NULL)
	{
		_strcpy(cmd_path, token);
		_strcat(cmd_path, "/");
		_strcat(cmd_path, cmd);
		free(token);
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

/**
 * get_cmd_name - Getsbthe namebofban executable
 *
 * @args: Array of arguments passed to the command.
 *
 * Return: Nothing.
 */
void get_cmd_name(char **args)
{
	int i = 0, len;
	char *name;

	if (args[0][0] == '/')
	{
		len = _strlen(args[0]);

		for (; args[0][len] != '/'; len--)
			i++;

		name = malloc(i);
		if (name != NULL)
		{
			name[i] = '\0';
			for (; i >= 0; --i)
				name[i] = args[0][len + i + 1];
			free(args[0]);
			args[0] = name;
		}
	}
}
/**
 * _exec - Executes commands.
 *
 * @fd: The file descriptor to execute commands from.
 * @err: Error structure containing the nature of the error occured while
 * executing commands.
 *
 * Return: 1 on success, 0 on failure.
 */
int _exec(int fd, err_t err)
{
	static int status;
	size_t n = 0;
	char *cmd_arr;
	char **tokens;
	pid_t pid = getpid();

	if (_getline(&cmd_arr, &n, fd) == -1)
	{
		free(cmd_arr);
		return (-2);
	}

	tokens = tokenize(cmd_arr);
	if (tokens == NULL)
	{
		free(cmd_arr);
		free(tokens);
		return (-1);
	}

	if (_strcmp(tokens[0], "exit"))
		return (exit_shell(cmd_arr, tokens, err));
	var_replacement(tokens, status, pid);

	if (!exec_builtin(tokens[0], tokens, err))
		status = sysexec(tokens[0], tokens, err);

	if (status == -2)
		perr(tokens, "not found\n", err, 0);

	free(cmd_arr);
	free_tokens(tokens);

	return (status);
}

/**
 * sysexec - Executes a system command.
 *
 * @cmd: The command to execute.
 * @args: Array of arguments passed to the command.
 * @err: Error structure containing the nature of the error occured while
 * executing the command.
 *
 * Return: 1 on success, 0 on failure.
 */
int sysexec(char *cmd, char **args, err_t err)
{
	int status = 0, path_stat;
	pid_t pid;
	char *path = get_cmd_path(cmd, &path_stat);

	if (path == NULL)
		return (-2);
	pid = fork();

	if (pid < 0)
	{
		err.print(err);
		if (path_stat == 0)
			free(path);
		return (-1);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		if (execve(path, args, environ) == -1)
		{
			err.print(err);
			if (path_stat == 0)
				free(path);
			return (-1);
		}
		if (WIFSTOPPED(status))
			err.print(err);
	}

	if (path_stat == 0)
		free(path);
	return (WEXITSTATUS(status));
}
