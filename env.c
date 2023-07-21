#include "hash.h"

/**
 * get_env_index - Gets the index of an environmental variable.
 *
 * @name: Name of the environmetal variable to get.
 *
 * Return: The index of the environmental variables if found or -1 if it can not be found.
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
 * _getenv - Gets an environmental variable.
 *
 * @name: Name 0f the environmetal variable to get.
 *
 * Return: The environmental variables if found or NULL if it can not be found.
 */
char *_getenv(const char *name)
{
	int i = 0, j;
	int index = get_env_index(name);
	char env_var[4096];
	char *env_ptr;

	if (index > -1)
	{
		while (environ[index][i] != '=')
			i++;
		for (j = 0, i += 1; environ[index][i]; i++, j++)
			env_var[j] = environ[index][i];
		env_ptr = env_var;
		return (env_ptr);
	}
	return (NULL);
}

/**
 * printenv - Prints the environmental variables.
 *
 * Return: Nothing.
 */
void printenv(void)
{
	while (*environ)
	{
		_puts(*environ);
		_putchar('\n');
		environ++;
	}
	_putchar(-1);
}

/**
 * _unsetenv - Unsets an environmental variable.
 *
 * @name: Name 0f the environmetal variable to unset.
 *
 * Return: 0 on success -1 on error.
 */
int _unsetenv(const char *name)
{
	int index = get_env_index(name);

	if (index == -2)
		return (-1);
	if (index > -1)
		for (; environ[index]; index++)
			environ[index] = environ[index + 1];

	return (0);
}

