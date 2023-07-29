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
 * cderr - Error encountered while changing a directory.
 *
 * @args: Array of arguments passed to the command.
 * @dir: The directory to change into.
 * @tokens: Number of command tokens
 * @err: Error structure containing the nature of the error occured while
 * executing the command.
 *
 * Return: -1.
 */
int cderr(char **args, char *dir, int tokens, err_t err)
{
	if (tokens > 2)
		perr(args, "Too many arguments", err, 1);

	else
	{
		perr(args, "Can't cd to ", err, 0);
		if (tokens != 1)
			write(STDERR_FILENO, args[1], _strlen(args[1]));
		write(STDERR_FILENO, "\n", 1);
	}

	if (dir)
		free(dir);
	return (-1);
}

/**
 * set_cd - Helper function for {cd} builtin commands.
 *
 * @args: Array of arguments passed to the command.
 * @dir: The directory to change into.
 * @tokens: Number of command tokens
 * @err: Error structure containing the nature of the error occured while
 * executing the command.
 *
 * Return: 0 on success, -1 on failure.
 */
int set_cd(char **args, char *dir, int tokens, err_t err)
{
	int set_pwd, set_oldpwd;
	char *cwd;

	if (dir == NULL || chdir(dir) == -1)
		return (cderr(args, dir, tokens, err));

	cwd = _getenv("PWD");
	if (cwd == NULL)
		return (cderr(args, dir, tokens, err));

	set_oldpwd = setenv("OLDPWD", cwd, 0);
	set_pwd = setenv("PWD", dir, 0);
	if (set_oldpwd == -1 || set_pwd == -1)
	{
		free(cwd);
		return (cderr(args, dir, tokens, err));
	}

	if (tokens > 1 && _strcmp("-", args[1]))
	{
		write(STDERR_FILENO, dir, _strlen(dir));
		write(STDERR_FILENO, "\n", 1);
	}

	free(cwd);
	free(dir);
	return (0);
}

