#include "hash.h"

int is_delim(char c, const char *delim)
{
	int j;

	for (j = 0; delim[j]; j++)
		if (c == delim[j])
			return (1);
	return (0);
}

int skip_delim(char *s, const char *delim)
{
	int i = 0;

	while (is_delim(s[i], delim))
		i++;

	return (i);
}

char *_strtok(char *s, const char *delim)
{	
	int i = 0;
	static char *buf;
	char slice[BUFF_SIZE];
	char *token;

	if (s != NULL)
		buf = s;

	buf += skip_delim(buf, delim);

	for (i = 0; buf[i]; i++)
	{
		slice[i] = buf[i];
		if (is_delim(buf[i], delim))
			break;
	}

	slice[i] = '\0';
	token = slice;
	buf += i;

	if (i > 0 && buf[i] == '\0')
		return (token);

	if (buf[i] == '\0')
	{
		buf = NULL;
		token = NULL;
	}
	return (token);
}

char **tokenize(char *line)
{
	int i = 0;
	char **token_arr = malloc(sizeof(char *));
	char *token;
	token = strtok(line, " ");

	/*if (token_arr == NULL)
		return (NULL);

	while (token != NULL)
	{
		token = strtok(NULL, " ");
		token_arr[i] = _strdup(token);

		if (token_arr[i] == NULL)
			return (NULL);

		i++;
	}*/

	//token_arr[i] = NULL;
	return (token_arr);
}

void free_tokens(char **token_arr)
{
	int i;

	for (i = 0; token_arr[i]; i++)
		free(token_arr[i]);

	free(token_arr);
}
