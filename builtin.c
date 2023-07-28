#include "hash.h"

/**
 * exec_builtin - Executes a builtin command.
 * Sets an environment variable.
 *
 * @cmd: The command to execute.
 * @args: Array of arguments passed to the command.
 * @err: Error structure containing the nature of the error occured while
 * executing the command.
 *
 * Return: 1 if a command is a builtin, 0 otherwise.
 */
int exec_builtin(char *cmd, char **args, err_t err)
{
	int i;
	btn_t builtins[] = {
		/*{alias, "alias"},*/
		{cd, "cd"},
		{printenv, "env"},
		{setenv_c, "setenv"},
		{unsetenv_c, "unsetenv"}
	};

	for (i = 0; i < 4; i++)
	{
		if (_strcmp(cmd, builtins[i].cmd))
		{
			builtins[i].exec(args, err);
			return (1);
		}
	}
	return (0);
}

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
			perr(args, "Not a number\n", err, 1);
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
 * Return: 1 on success, 0 on failure.
 */
int cd(char **args, err_t err)
{
	int set_oldpwd, set_pwd;
	int tokens = arr_size(args);
	char *dir = _getenv("HOME");
	char old_dir[256];

	if (tokens > 2)
	{
		perr(args, "Too many arguments\n", err, 1);
		return (-1);
	}

	getcwd(old_dir, 256);
	if (tokens > 1)
		dir = _strcmp("-", args[1]) ? old_dir : args[1];

	if (dir == NULL || chdir(dir) == -1)
	{
		if (tokens == 1)
			free(dir);
		perr(args, "Cannot cd into directory\n", err, 1);
		return (-1);
	}

	set_oldpwd = _setenv("OLDPWD", old_dir, 0);
	set_pwd = _setenv("PWD", dir, 0);
	if (set_oldpwd == -1 || set_pwd == -1)
	{
		if (tokens == 1)
			free(dir);
		perr(args, "Unable to set environment\n", err, 1);
		return (-1);
	}

	if (_strcmp(dir, "-"))
		_puts(dir);
	if (tokens == 1)
		free(dir);

	return (0);
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
		perr(args, "Too many arguments\n", err, 1);
		return (-1);
	}

	else if (tokens < 2)
	{
		perr(args, "Invalid argument\n", err, 1);
		return (-1);
	}

	if (_setenv(args[1], args[2], 1) == -1)
	{
		perr(args, "Cannot set environment\n", err, 1);
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
		perr(args, "Too many arguments\n", err, 1);
		return (-1);
	}

	else if (tokens == 1)
	{
		perr(args, "Invalid argument\n", err, 1);
		return (-1);
	}

	if (_unsetenv(args[1]) == -1)
	{
		perr(args, "No such environment\n", err, 1);
		return (-1);
	}
	return (0);
}
