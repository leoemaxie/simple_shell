#include "hash.h"

int comment_replacement(char **tokens, int index)
{
	int j;

	for (j = index; tokens[j]; j++)
		free(tokens[j]);
	tokens[index] = NULL;

	return (1);
}

int env_replacement(char **tokens, int index)
{
	int i;
	char name[100];
	char *env;

	for (i = 0; tokens[index][i + 1]; i++)
		name[i] = tokens[index][i + 1];
	name[i] = '\0';

	env = _getenv(name);
	if (env == NULL)
		return (0);

	free(tokens[index]);
	tokens[index] = env;
	return (1);
}

int var_replacement(char **tokens, int status, pid_t pid)
{
	int i;

	for (i = 0; tokens[i]; i++)
	{
		if (tokens[i][0] == '#')
		{
			if (i == 0)
				return (-2);
			return (comment_replacement(tokens, i));
		}

		if (tokens[i][0] == '$')
			dollar_replacement(tokens, i, status, pid);
	}
	return (0);
}

int stat_replacement(char **tokens, int index, int stat)
{
	char *num = strnum(stat);

	if (num == NULL)
		return (0);

	free(tokens[index]);
	tokens[index] = num;

	return (1);
}

int dollar_replacement(char **tokens, int index, int status, pid_t pid)
{
	int pid_num = (int)pid;

	if (tokens[index][1] == '?')
		return (stat_replacement(tokens, index, status));

	if (tokens[index][1] == '$')
		return (stat_replacement(tokens, index, pid_num));

	if (tokens[index][1] >= 'A' || tokens[index][1] <= 'Z')
		return (env_replacement(tokens, index));

	return (-1);
}


