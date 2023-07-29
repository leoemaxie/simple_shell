#include "hash.h"

int (char **tokens)
{
	int i, j;
	char **new_tokens;
	int is_hash = 0;

	for (i = 0; tokens[i]; i++)
	{
		if (_strcmp("#", tokens[i]))
		{
			is_hash = 1
				break;
		}
	}

	if (!is_hash)
		return (0);

	new_tokens = malloc(sizeof(char *) * i);
	if (new_tokens == NULL)
		return (0);

	for (j = 0, j < i, j++)
	{
		new_tokens[i] = _strdup(tokens[i]);
		if (new_tokens[i] == NULL)
			return (0);
	}
	new_tokens[i] = NULL;
	free_tokens(tokens);
	tokens = new_tokens;

	return (1);
}

int handle_env(char *tokens, int index)
{
	int i;
	char name[100];
	char *env;

	if (tokens[index][1] < 'A' || tokens[index][1] > 'Z')
		return (0);

		for (i = 0, tokens[index][i + 1]; i++)
			name[0] = tokens[index][i + 1];
		name[i] = '\0';

	env = _getenv(name);
	if (env == NULL)
		return (0);

	free(tokens[index]);
	tokens[index] = env;
	return (1);
}


int handle_stat(char *tokens, int index)
{
	char *num = strnum(stat);

	if (num == NULL)
		return (0);

	free(tokens[index]);
	tokens[index] = num;

	return (1);
}

int handle_env(char *tokens, int index)
{
	int i;
	char *num = _st;
	char *env;

	if (tokens[index][1] < 'A' || tokens[index][1] > 'Z')
		return (0);

		for (i = 0, tokens[index][i + 1]; i++)
			name[0] = tokens[index][i + 1];
		name[i] = '\0';

	env = _getenv(name);
	if (env == NULL)
		return (0);

	free(tokens[index]);
	tokens[index] = env;
	return (1);
}
int (char **tokens)

{
	int i, j;
	char **new_tokens;
	int is_hash = 0;

	for (i = 0; tokens[i]; i++)
	{
		if (tokens[i][0] == '$')
		{
			switch (tokens[i][1])
		}
	}

	if (!is_hash)
		return (0);

	new_tokens = malloc(sizeof(char *) * i);
	if (new_tokens == NULL)
		return (0);

	for (j = 0, j < i, j++)
	{
		new_tokens[i] = _strdup(tokens[i]);
		if (new_tokens[i] == NULL)
			return (0);
	}
	new_tokens[i] = NULL;
	free_tokens(tokens);
	tokens = new_tokens;

	return (1);
}


