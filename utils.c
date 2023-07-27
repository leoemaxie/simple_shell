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

void signal_handler(int signum)
{
	(void)signum;

	write(STDOUT_FILENO, "\n($) ", 5);
}
