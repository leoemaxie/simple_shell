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

int skip_consecutive_delim(char *s, const char *delim, int i)
{
	int delimiters = 1;

	for (; s[i]; i++)
		if (is_delim(s[i], delim) && is_delim(s[i + 1], delim))
		//printf("%c", s[i + 1]);
			delimiters++;
	
	return (delimiters);
}

char *_strtok(char *s, const char *delim)
{
	int i;
	int has_delim = 0;
	static char *buf;
	char *slice;

	if (s != NULL)
		buf = s;
	slice = buf;

	for (i = 0; buf[i]; i++)
	{
		if (is_delim(buf[i], delim))
		{
			has_delim = 1;
			break;
		}
	}
		//printf("%d\n", i);
	if (has_delim)
	{
	    int u = skip_consecutive_delim(buf, delim, i);
		slice[i] = '\0';
		buf += u + i;
		return (slice);
	}

	buf = NULL;
	return (NULL);
}

int main(void)
{
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
		//token = _strtok(NULL, c);
		printf("%s\n", token);
	}
	return (0);

}
