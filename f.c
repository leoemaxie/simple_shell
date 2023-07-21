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
	int delimiters = 0;

	for (; s[i]; i++)
	{
		if (!is_delim(s[i], delim) && !is_delim(s[i + 1], delim))
			break;
		delimiters++;
	}
	
	return (delimiters);
}

char *_strtok(char *s, const char *delim)
{	
	int i, has_delim = 0;
	static char *buf;
	static int index;
	char slice[BUFF_SIZE];
	char *token;

	if (s != NULL)
	{
		buf = s;
		return s += skip_consecutive_delim(buf, delim, index);
	}

	for (i = 0; buf[index]; i++, index++)
	{
		slice[i] = buf[index];
		if (is_delim(buf[index], delim))
		{
			has_delim = 1;
			break;
		}
		printf("%c %c\n", slice[i], buf[index]);
	}

	token = slice;
	if (index < 50)
		slice[i] = '\0';
index += 1;
	if (has_delim)
	{
		index += skip_consecutive_delim(buf, delim, index);
		return (token);
	}

	index = 0;
	buf = NULL;
	return (NULL);
}

int main(void)
{
	char s[] = "Hello World;;;;;This is great ";
	//char s[] = "great";
	const char *c = " ;";
	char *token = _strtok(s, c);
	char y[] = "IN 1960, A great orator was born   One who changes the world!";
	/*while (token != NULL)
	{
		token = _strtok(NULL, c);
		printf("%s\n", token);
	}*/
	token = _strtok(y, c);

	while (token != NULL)
	{
		token = _strtok(NULL, c);
		printf("%s\n", token);
	}
	return (0);

}
