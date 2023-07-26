#include "hash.h"

int exec_builtin(char *cmd, char **tokens, err_t err)
{
	int i;
	btn_t builtins[] = {
		/*{alias, "alias"},*/
		{cd, "cd"},
		{printenv, "env"},
		{setenv_c, "setenv"},
		{unsetenv_c, "unsetenv"}
	};

	for (i = 0; i < 2; i++)
	{
		if (_strcmp(cmd, builtins[i].cmd))
		{
			builtins[i].exec(tokens, err);
			return (1);
		}
	}
	return (0);
}

int exit_shell(char *cmd_arr, char **arr, err_t err)
{
	int status = 0;
	(void)err;

	if (arrlen(arr) > 1)
	{
		status = _atoi(arr[1]);

		if (status == 0)
		{
			perr(arr, "Not a number\n", err, 1);
			free(cmd_arr);
			free_tokens(arr);
			return (-1);
		}
	}

	free(cmd_arr);
	free_tokens(arr);
	exit(status);
}

int arrlen(char **arr)
{
	int len = 0;

	while (*arr)
	{
		len++;
		arr++;
	}

	return (len);
}

int cd(char **dirarr, err_t err)
{
	int set_pwd, set_oldpwd;
	int tokens = arrlen(dirarr);
	char *dir;
	char *oldpwd = _getenv("PWD");

	if (tokens > 2)
	{
		perr(dirarr, "Too many arguments\n", err, 1);
		return (-1);
	}

	if (oldpwd == NULL)
	{
		perr(dirarr, "Old PWD not set\n", err, 1);
		return (-1);
	}

	if (tokens == 1)
		dir = _getenv("HOME");
	else
		dir = _strcmp("-", dirarr[1]) ? oldpwd : dirarr[1];

	if (dir == NULL)
		return (-1);

	if (chdir(dir) == -1)
	{
		err.print(err);
		return (-1);
	}

	set_oldpwd = _setenv("OLDPWD", oldpwd, 0);
	set_pwd = _setenv("PWD", dir, 0);
	if (set_oldpwd == -1 || set_pwd == -1)
	{
		perr(dirarr, " : Invalid argument\n", err, 1);
		return (-1);
	}

	return (0);
}

int setenv_c(char **arr, err_t err)
{
	int tokens = arrlen(arr);

	if (tokens > 3)
	{
		perr(arr, "Too many arguments\n", err, 1);
		return (-1);
	}

	else if (tokens < 2)
	{
		perr(arr, "Invalid argument\n", err, 1);
		return (-1);
	}

	if (_setenv(arr[1], arr[2], 0) == -1)
	{
		perr(arr, "Cannot set environment\n", err, 1);
		return (-1);
	}
	return (0);

}

int unsetenv_c(char **arr, err_t err)
{
	int tokens = arrlen(arr);

	if (tokens > 2)
	{
		perr(arr, "Too many arguments\n", err, 1);
		return (-1);
	}

	else if (tokens == 1)
	{
		perr(arr, "Invalid argument\n", err, 1);
		return (-1);
	}

	if (_unsetenv(arr[1]) == -1)
	{
		perr(arr, "No such environment\n", err, 1);
		return (-1);
	}
	return (0);
}
