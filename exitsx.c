#include "hash.h"
#include <string.h>

/**
 * _strncpy - function that copies a string
 * @dest: string destination
 * @src: source string
 * @n: the number of characters to be copied
 *
 * Return: 0
 */

char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}

	return (s);
}

/**
 * _strncat - concatenates two strings
 * @dest: first string
 * @src: second string
 * @n: the amount of bytes
 *
 * Return: concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';

	return (s);
}

/**
 * _strchr - locates a character in a string
 * @s: the string
 * @c: the character
 *
 * Return: 0
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
