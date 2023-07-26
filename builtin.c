#include "hash.h"

int exec_builtin(char *cmd, char **tokens, err_t err)
{
	int i;
	btn_t builtins[] = {
		/*{alias, "alias"},*/
		{cd, "cd"},
		{printenv, "env"},
		{exit_shell, "exit"},
		{setenv_c, "setenv"},
		{unsetenv_c, "unsetenv"}
	};

	for (i = 0; i < 5; i++)
	{
		if (_strcmp(cmd, builtins[i].cmd))
		{
			builtins[i].exec(tokens, err);
			return (1);
		}
	}
	return (0);
}

int exit_shell(char **arr, err_t err)
{
	(void)err;

	if (arrlen(arr) > 1)
		exit(_atoi(arr[1]));
	exit(0);
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
		print_builtin_err(dirarr, "Too many arguments\n", err);
		return (-1);
	}

	if (oldpwd == NULL)
	{
		print_builtin_err(dirarr, "Old PWD not set\n", err);
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
		print_builtin_err(dirarr, " : Invalid argument\n", err);
		return (-1);
	}

	return (0);
}

int setenv_c(char **arr, err_t err)
{
	int tokens = arrlen(arr);

	if (tokens > 3)
	{
		print_builtin_err(arr, "Too many arguments\n", err);
		return (-1);
	}

	else if (tokens < 2)
	{
		print_builtin_err(arr, "Invalid argument\n", err);
		return (-1);
	}

	if (_setenv(arr[1], arr[2], 1) == -1)
	{
		print_builtin_err(arr, "Cannot set environment\n", err);
		return (-1);
	}
	return (0);

}

int unsetenv_c(char **arr, err_t err)
{
	int tokens = arrlen(arr);

	if (tokens > 2)
	{
		print_builtin_err(arr, "Too many arguments\n", err);
		return (-1);
	}

	else if (tokens == 1)
	{
		print_builtin_err(arr, "Invalid argument\n", err);
		return (-1);
	}

	if (_unsetenv(arr[1]) == -1)
	{
		write(STDERR_FILENO, arr[1], _strlen(arr[1]));
		print_builtin_err(arr, "No such environment\n", err);
		return (-1);
	}
	return (0);
}
