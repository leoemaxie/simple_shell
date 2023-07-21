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

/**
 * _strcpy - Copies a string into another.
 *
 * @dest: The string to copy into.
 * @src: The source string to copy.
 *
 * Return: A pointer to dest.
 */
char *_strcpy(char *dest, const char *src)
{
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[i] = src[i];
	dest[i] = '\0';

	return (dest);
}

/**
 * _strcat- Concatenates two strings.
 *
 * @desr: The string to append.
 * @src: The string to append to.
 *
 * Return: A pointer to the resulting string dest.
 */
char *_strcat(char *dest, const char *src)
{
	int i;
	int len = _strlen(dest);

	for (i = 0; src[i] != '\0'; ++i)
		dest[len + i] = src[i];
	dest[len + i] = '\0';

	return (dest);
}
