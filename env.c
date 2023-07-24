#include "hash.h"

/**
 * _getenv - Gets the value of an environment variable.
 *
 * @name: Pointer to a character string that contains the name of the
 * environment variable to get.
 *
 * Return: The value of an environment variable if found or NULL if it can not be found.
 */
char *_getenv(const char *name)
{
	int i = 0, j;
	int index = get_env_index(name);
	char *env_val;
	char *env;

	if (index > -1)
	{
		env = environ[index];
		while (env[i] != '=')
			i++;

		env_val = malloc(_strlen(env) - i);
		if (env_val == NULL)
			return (NULL);

		for (j = 0, i += 1;  env[i]; i++, j++)
			env_val[j] = env[i];

		return (env_val);
	}
	return (NULL);
}

/**
 * printenv - Prints the environment variables.
 *
 * Return: Nothing.
 */
int printenv(char **arr, err_t err)
{
	if (arrlen(arr) > 1)
	{
		print_builtin_err(":env: Too many arguments\n", err);
		return (-1);
	}

	while (*environ)
	{
		_puts(*environ);
		_putchar('\n');
		environ++;
	}
	_putchar(-1);
	return (0);
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
