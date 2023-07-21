#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int is_delim(char c, const char *delim)
{
	int j;

	for (j = 0; delim[j]; j++)
		if (c == delim[j])
			return (1);
	return (0);
}

char *_strtok(char *s, const char *delim)
{
	int i;
	int delimiters = 0;
	static char *buf;
	char *slice;

	if (s != NULL)
		buf = s;
	slice = buf;

	for (i = 0; buf[i]; i++)
		if (is_delim(s[i], delim))
			delimiters = 1;

	if (delimiters)
	{
		for (; buf[i]; i++)
		{
			if (is_delim(s[i], delim) && is_delim(s[i + 1], delim))
				delimiters++;
			else
			{
				slice[i] = '\0';
				buf += (i + delimiters);
				return (slice);
			}
		}
	}

	return (NULL);
}

int main(void)
{
	char o[100];
	char s[] = "Hello World;;;;;This is great "; //"great"
	const char *c = " ;";
	char *token = _strtok(s, c);
	char y[] = "IN 1960, A great orator was born   One who changes the world!";

	while (token != NULL)
	{
		token = _strtok(NULL, c);
		printf("%s\n", token);
	}
	token = _strtok(y, c);

	while (token != NULL)
	{
		token = _strtok(NULL, c);
		printf("%s\n", token);
	}
	return (0);

}
