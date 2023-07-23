#include "hash.h"

/**
 * _getenv - Gets an environmental variable.
 *
 * @name: Pointer to a character string that contains the name of the
 * environment variable to get.
 *
 * Return: The environmental variables if found or NULL if it can not be found.
 */
char *_getenv(const char *name)
{
	int i = 0, j;
	int index = get_env_index(name);
	char env_var[BUFF_SIZE];
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
 * printenv - Prints the environment variables.
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
 * _unsetenv - Removes an environment variable.
 *
 * @name: Pointer to a character string that contains the name of the
 * environment variable to be deleted.
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

/**
 * _setenv - Adds, changes, and deletes environment variables.
 *
 * @name: pointer to a character string that contains the name of the
 * environment variable to be added, changed, or deleted.
 * @value: Pointer to a character string that contains the value of the
 * environment variable for {name}.
 * @overwrite: An integer that determines the modification of {name}.
 *
 * Return: 0 on success -1 on error.
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int index = get_env_index(name);
	char new_env[BUFF_SIZE];
	char *ptr = new_env;

	if (index == -2)
		return (-1);

	if (!value && index > -1)
		for (; environ[index]; index++)
			environ[index] = environ[index + 1];

	if (value)
	{
		if (overwrite)
		{
			if (index == -1)
				return (addenv(name, value));

			create_env(&ptr, name, value);
			environ[index] = ptr;
		}

		if (!overwrite && index == -1)
			return (addenv(name, value));
	}

	return (0);
}
