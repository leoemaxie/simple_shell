#include "hash.h"

/**
 * _putchar - Prints a character to stdout. It uses a local buffer inorder to
 * call write as little as possible. a char of -1 indicates end of output
 * stream.
 *
 * @c: The character to print.
 *
 * Return: Number of all characters written if write was successful.
 */
int _putchar(int c)
{
	static int i;
	static char buffer[BUFF_SIZE];

	if (c == -1 || i >= BUFF_SIZE)
	{
		write(1, &buffer, i);
		i = 0;
	}
	if (c != -1)
		buffer[i++] = c;

	return (1);
}

/**
 * _puts - Prints a string,
 *
 * @s: The string to print.
 *
 * Return: Length of string i.e The number of characters printed.
 */
int _puts(const char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		_putchar(s[i]);
	return (i);
}
