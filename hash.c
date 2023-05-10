#include "hash.h"

/**
 * main - Runs the hash shell.
 *
 * @ac: The number of command line argunents.
 * @av: An array of command line argunents.
 * @env: An array of enviromental variables
 *
 * Return: 0.
 */
int main(int ac, char **av, char **env)
{
	printf("%s", env[1]);
	return (0);
}
