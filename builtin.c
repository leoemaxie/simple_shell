#include "hash.h"

int exec_builtin(char *cmd, char **tokens, err_t err)
{
	int i;
	btn_t builtins[] = {
		//{alias, "alias"},
		{cd, "cd"},
		{printenv, "env"},
		{exit_shell, "exit"},
		//{setenv_c, "setenv"},
		//{unsetenv_c, "unsetenv"}
	};

	for (i = 0; i < 3; i++)
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
		print_builtin_err(":cd: Too many arguments\n", err);
		return (-1);
	}

	if (oldpwd == NULL)
	{
		print_builtin_err(":cd: Old PWD not set\n", err);
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
		print_builtin_err(":cd: Invalid argument\n", err);
		return (-1);
	}

	return (0);
}
/*
int unset_c(char **arr, err_t err)
{
	int tokens = arrlen(dirarr);

	if (tokens > 1)
	{
		print_builtin_err(":unset: Too many arguments\n", err);
		return (-1);
	}

	if (tokens == 1)
	{
		if unset
}*/
