#include "hash.h"

/**
 * _strlen - Computes the length of a string.
 *
 * @s: The string.
 *
 * Return: length of the string.
 */
int _strlen(const char *s)
{
	int len = 0;

	while (s[len])
		len++;

	return (len);
}

/**
 * _strcmp - Compares two strings.
 *
 * @s1: The first string to compare.
 * @s2: The second string to compare.
 *
 * Return: 1 if s1 and s2 is equal, 0 otherwise.
 */
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
