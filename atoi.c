#include "hash.h"

/**
 * _atoi - Converts a string to an integer.
 *
 * @s: The string to convert.
 *
 * Return: The integer represebtation of the string, 0 otherwise.
 */
int _atoi(const char *s)
{
	int i = 0;
	int num = 0, minus = 1;

	if (s[i] == '-')
	{
		minus = -1;
		i++;
	}
	while (s[i])
	{
		if (s[i] < '0'  || s[i] > '9')
			return (0);
		num = (num * 10) + (s[i] - '0');
		i++;
	}

	return (num * minus);
}
