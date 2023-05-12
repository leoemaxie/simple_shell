#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
/*char *_strtok(char *s, const char *delim)
{
	int i, j;
	//int len = 0;
	static char *buf;
	char *slice;

	if (s != NULL)
		buf = s;
	//len = _strlen(buf);
	slice = buf;

	for (i = 0; buf[i]; i++)
	{
		for (j = 0; delim[j]; j++)
		{
			if (buf[i] == delim[j])
			{
				slice[i] = '\0';
				//if (len - i > 0)
					buf += (i + 1);
				return (slice);
			}
		}
	}

	return (NULL);
}*/

int main(int ac, char **av, char **env)
{
	char s[] = "Hello World;;;;;This is great ";
	const char *c = " ;";
	//char *token = _strtok(s, c);
	char *d[] = {"/data/data/com.termux/files/usr/bin/vi", "hash.c", NULL};
	char *as[] = {"/data/data/com.termux/files/usr/bin", NULL};

	if (execve(d[0], d, env) == -1)
		perror(d[0]);
	puts("hello");

	/*while (token != NULL)
	{
		printf("%s\n", token);
		token = _strtok(NULL, c);
	}
	token = _strtok(y, c);
	while (token != NULL)
	{
		printf("%s\n", token);
		token = _strtok(NULL, c);
	}
	return (0);*/
	return (0);
}
