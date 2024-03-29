#include "hash.h"

#define MAX_SIZE 128
/**
 * is_delim - Checks whether a character is a delimeter.
 *
 * @c: The character to check.
 * @delim: A string of delimeters.
 *
 * Return: 1 if character is a delimeter, 0 otherwise.
 */
int is_delim(char c, const char *delim)
{
	int j;

	for (j = 0; delim[j]; j++)
		if (c == delim[j])
			return (1);
	return (0);
}

/**
 * _strtok - Breaks a string into a sequence of tokens.
 *
 * @s: The string to tokenize.
 * @delim: A string of characters that indicates where to break a string.
 *
 * Return: The first time _strtok() is called, it returns a pointer to the
 * first token.
 * In later calls with the same token string, _strtok() returns a pointer to
 * the next token in the string.
 * A NULL pointer is returned when there are no more tokens.
 * All tokens are NULL-terminated.
 */
char *_strtok(char *s, const char *delim)
{
	int i = 0, len;
	static char *buf;
	char slice[BUFF_SIZE];
	char *token;

	if (s != NULL)
		buf = s;

	if (buf == NULL)
		return (NULL);
	len = _strlen(buf);

	while (is_delim(buf[i], delim))
		i++;
	buf += i;

	if (i == len)
		return (NULL);

	for (i = 0; buf[i] && !is_delim(buf[i], delim); i++)
		slice[i] = buf[i];

	slice[i] = '\0';
	token = _strdup(slice);
	buf += i;

	if (i > 0 && i == len)
	{
		buf = NULL;
		return (token);
	}

	if (i == 0)
	{
		buf = NULL;
		free(token);
		return (NULL);
	}
	return (token);
}

/**
 * tokenize - Tokenize a line to a series of command to be executed by the
 * shell.
 *
 * @line: The command a user enters. _getline() gets this line.
 *
 * Return: A pointer to an array of command tokens, NULL on error.
 */
char **tokenize(char *line)
{
	int i = 0;
	char **token_arr = malloc(sizeof(char *) * MAX_SIZE);
	char *token = _strtok(line, " ");

	if (token_arr == NULL)
		return (NULL);

	while (token != NULL)
	{
		token_arr[i] = token;

		if (token_arr[i] == NULL)
			return (NULL);

		token = _strtok(NULL, " ");
		i++;
	}

	token_arr[i] = NULL;
	return (token_arr);
}

/**
 * free_tokens - Frees the memory used by token_arr.
 *
 * @token_arr: An array of tokens.
 *
 * Return: Nothing.
 */
void free_tokens(char **token_arr)
{
	int i;

	for (i = 0; token_arr[i]; i++)
		free(token_arr[i]);
	free(token_arr);
}
