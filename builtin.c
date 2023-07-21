#include "hash.h"

int is_builtin(char *s)
{
	int i;
	char *builtins[] = {"cd", "env", "exit"};

	for (i = 0; i < 3; i++)
		if (_strcmp(builtins[i], s))
			return (i);
	return (-1);
}

void close(int status)
{
	exit(status);
}

void perform_builtin_cmd(int index, char **env)
{
	switch (index)
	{
		case 0:
			break;
		case 1:
			printenv();
			break;
		case 2:
			exit(1);
			break;
	}
}

/*
cd(const char *dir)
{
	static char *prev_dir;
	if (dir == NULL)
		dir = _getenv("HOME");
	if (chdir(dir) == -1)

	uuperror
	*/
