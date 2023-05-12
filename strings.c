#include "hash.h"

int _strlen(const char *s)
{
	int len = 0;

	while (s[len])
		len++;

	return (len);
}

int _strcmp(const char *s1, const char *s2)
{
	int i;

	if (_strlen(s1) != _strlen(s2))
		return (0);

	for (i = 0; s1[i]; i++)
		if (s1[i] != s2[i])
			return (0);

	return (1);
}
