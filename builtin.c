#include "hash.h"

/**
 * exit_shell  - Exists an interactive shell.
 * Sets an environment variable.
 *
 * @cmd_line: Dynamically allocated buffer used by the {getline} function.
 * @args: Array of arguments passed to the command.
 * @err: Error structure containing the nature of the error occured while
 * executing the command.
 *
 * Return: Does not return on success, -1 on failure.
 */
int exit_shell(char *cmd_line, char **args, err_t err)
{
	int status = 0;
	(void)err;

	if (arr_size(args) > 1)
	{
		status = _atoi(args[1]);

		if (status == 0)
		{
			perr(args, "Illegal number", err, 1);
			free(cmd_line);
			free_tokens(args);
			return (-1);
		}
	}

	free(cmd_line);
	free_tokens(args);
	exit(status);
}

/**
 * cd - Changes a directory.
 *
 * @args: Array of arguments passed to the command.
 * @err: Error structure containing the nature of the error occured while
 * executing the command.
 *
 * Return: 0 on success, -1 on failure.
 */
int cd(char **args, err_t err)
{
	int tokens = arr_size(args);
	char *dir = NULL;

	if (tokens > 2)
		return (cderr(args, NULL, tokens, err));

	if (tokens == 1)
	{
		dir = _getenv("HOME");
		return (set_cd(args, dir, tokens, err));
	}

	if (_strcmp(args[1], "-"))
	{
		dir = _getenv("OLDPWD");
		return (set_cd(args, dir, tokens, err));
	}

	dir = _strdup(args[1]);
	return (set_cd(args, dir, tokens, err));
}

/**
 * setenv_c - Wrapper function for {setenv} that executes the setenv command.
 * Sets an environment variable.
 *
 * @args: Array of arguments passed to the command.
 * @err: Error structure containing the nature of the error occured while
 * executing the command.
 *
 * Return: 1 on success, 0 on failure.
 */
int setenv_c(char **args, err_t err)
{
	int tokens = arr_size(args);

	if (tokens > 3)
	{
		perr(args, "Too many arguments", err, 1);
		return (-1);
	}

	else if (tokens < 2)
	{
		perr(args, "Invalid argument", err, 1);
		return (-1);
	}

	if (_setenv(args[1], args[2], 1) == -1)
	{
		perr(args, "Cannot set environment", err, 1);
		return (-1);
	}
	return (0);

}

/**
 * unsetenv_c - Wrapper function for {unsetenv} that executes the unsetenv
 * command.
 * Unets an environment variable.
 *
 * @args: Array of arguments passed to the command.
 * @err: Error structure containing the nature of the error occured while
 * executing the command.
 *
 * Return: 1 on success, 0 on failure.
 */
int unsetenv_c(char **args, err_t err)
{
	int tokens = arr_size(args);

	if (tokens > 2)
	{
		perr(args, "Too many arguments", err, 1);
		return (-1);
	}

	else if (tokens == 1)
	{
		perr(args, "Invalid argument", err, 1);
		return (-1);
	}

	if (_unsetenv(args[1]) == -1)
	{
		perr(args, "No such environment", err, 1);
		return (-1);
	}
	return (0);
}
