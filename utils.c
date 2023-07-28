#include "hash.h"

/**
 * clean_env - Frees the memory dynamically allocated to the environ variable
 * by this shell program.
 *
 *
 * Return: Nothing.
 */
void clean_env(void)
{
	int init_len = get_initial_env_len();
	int len = arr_size(environ);
	int i;

	if (len > init_len)
		for (i = len; i < init_len; i++)
			free(environ[i]);
}

/**
 * arr_size - Computes the size of an array of strings.
 *
 * @arr: The array of strings.
 *
 * Return: The size of an array.
 */
int arr_size(char **arr)
{
	int size = 0;

	while (*arr)
	{
		size++;
		arr++;
	}

	return (size);
}

/**
 * signal_handler - Handles the SIGINT (CTRL + C) signal.
 *
 * @signum: The signal number.
 *
 * Return: Nothing.
 */
void signal_handler(int signum)
{
	(void)signum;

	write(STDOUT_FILENO, "\n($) ", 5);
}

/**
 * strrev - Reverses the characters in a string.
 *
 * @s: The string to reverse.
 *
 * Return: Nothing.
 */
void strrev(char *s)
{
	int i;
	int len = _strlen(s) - 1;

	for (i = 0; i < len / 2; i++)
	{
		char tmp = s[i];
		int last = len - i;

		s[i] = s[last];
		s[last] = tmp;
	}
}
