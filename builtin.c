#include "hash.h"

int exec_builtin(char *cmd, char **tokens, err_t err)
{
	int i;
	btn_t builtins[] = {
		//{alias, "alias"},
		{cd, "cd"},
		//{printenv, "env"},
		{close, "exit"},
		//{set, "setenv"},
		//{unset, "unsetenv"}
	};

	for (i = 0; i < 6; i++)
	{
		if (_strcmp(cmd, builtins[i].cmd))
		{
			builtins[i].exec(tokens, err);
			return (1);
		}
	}
	return (0);
}

int close(char **arr)
{
	int tokens = arrlen(arr);

	if (tokens > 1)
		exit(_atoi(arr[0]);
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

int cd(const char **dirarr, err_t err)
{
	int set_pwd, set_oldpwd;
	int tokens = arrlen(dirarr);
	char *dir;
	char *oldpwd = _getenv("PWD");

	if (tokens > 1)
	{
		print_builtin_err(":cd: Too many arguments\n");
		return (-1);
	}

	if (oldpwd == NULL)
	{
		print_builtin_err(":cd: Old PWD not set\n");
		return (-1);
	}

	if (token == 0)
		dir = _getenv("HOME");
	else
		dir = _strcmp("-", dirarr[0]) ? oldpwd : dirarr[0];

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
		print_builtin_err(":cd: Invalid argument\n");
		return (-1);
	}

	return (0);
}
