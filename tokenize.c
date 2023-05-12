#include "hash.h"

/**
 * tokenize - Tokenizes a string into an array of chars to get the commands,
 * operators, etc.
 *
 * @s: The string to tokenize. This is gotten from the command line.
 *
 * Return: Nothing.
 */
void tokenize(char *s, char **cmd_arr)
{
	static int i;
	const char *delimeter = " ;";
	char *token;

	token = strtok(s, delimeter);
	while (token != NULL)
	{
		token = strtok(NULL, delimeter);
		cmd_arr[i++] = token;
	}
}
