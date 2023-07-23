#include "hash.h"

/**
 * get_env_index - Gets the index of an environment variable.
 *
 * @name: pointer to a character string that contains the name of the
 * environment variable to get.
 *
 * Return: The index of the environment variable if found or
 * -1 if it can not be found.
 */
int get_env_index(const char *name)
{
	int i = 0, j;
	int found = 1;

	if (name == NULL)
		return (-2);

	while (environ[i])
	{
		for (j = 0; environ[i][j] != '='; j++)
		{
			if (!name[j])
				return (-1);
			if (name[j] != environ[i][j])
			{
				found = 0;
				break;
			}
		}

		if (found && _strlen(name) == j)
			return (i);
		found = 1;
		i++;
	}

	return (-1);
}

/**
 * create_env - Creates environment variables.
 *
 * @envptr: Pointer to a buffer to write the created variables into.
 * @name: Pointer to a character string that contains the name of the
 * environment variable to create.
 * @value: Pointer to a character string that contains the value to use for the
 * environment variable for {name}.
 *
 * Return: Nothing.
 */
void create_env(char **envptr, const char *name, const char *value)
{
	int i, j;

	for (i = 0; i < BUFF_SIZE; i++)
	{
		for (j = 0; name[j] && name[j] != '='; j++)
			(*envptr)[i++] = name[j];
		(*envptr)[i++] = '=';
		for (j = 0; value[j]; j++)
			(*envptr)[i++] = value[j];
		(*envptr)[i] = '\0';
		break;
	}
}

/**
 * addenv - Adds environment variables.
 *
 * @name: pointer to a character string that contains the name of the
 * environment variable add.
 * @value: Pointer to a character string that contains the value of the
 * environment variable for {name}.
 *
 * Return: 0 on success -1 on error.
 */
int addenv(const char *name, const char *value)
{
	int env_len = 0;
	int char_len = _strlen(name) + _strlen(value) + 2; /* 2 chars: = and '\0' */

	while (environ[env_len])
		env_len++;

	environ[env_len] = malloc(char_len);
	environ[env_len + 1] = malloc(sizeof(char *));

	if (!environ[env_len] || !environ[env_len + 1])
		return (-1);

	create_env(&environ[env_len], name, value);
	environ[env_len + 1] = NULL;

	return (0);
}
