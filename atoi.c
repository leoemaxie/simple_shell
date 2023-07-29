#include "hash.h"

/**
 * _atoi - Converts a string to an integer. Modified to accept only positive
 * convertible string.
 *
 * @s: The string to convert.
 *
 * Return: The integer represebtation of the string, 0 otherwise.
 */
int _atoi(const char *s)
{
	int i = 0;
	int num = 0;

	if (s[i] == '-')
		return (0);

	while (s[i])
	{
		if (s[i] < '0'  || s[i] > '9')
			return (0);
		num = (num * 10) + (s[i] - '0');
		i++;
	}

	return (num);
}
