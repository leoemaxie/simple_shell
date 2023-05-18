#include "hash.h"

int line_end(int c)
{
	switch (c)
	{
		case '\n':
			return (1);
		case EOF:
			return (1);
		default:
			return (0);
	}
}

int fill_buf(char **lineptr, char *buf, ssize_t *old_len, ssize_t *new_len)
{
	ssize_t i;
	ssize_t diff = *new_len - *old_len;

	if (lineptr == NULL)
	{
		lineptr = malloc(sizeof(char *));
		if (lineptr == NULL)
			return (-1);
	}
	if (*new_len <= BUFF_SIZE)
	{
		*lineptr = malloc(*new_len);
		if (*lineptr == NULL)
			return (-1);
	}
	if (sizeof(*lineptr) != *new_len)
	{
		*lineptr = realloc(*lineptr, *new_len);
		if (*lineptr == NULL)
			return (-1);
	}

	for (i = *old_len; i <= *new_len; i++)
	{
		if (line_end(buf[i]))
		{
			*lineptr[*new_len + 1] = '\0';
			return (1);
		}
		*lineptr[*old_len++] = buf[i];
	}

	return (0);
}

/**
 * getline - reads an entire line from stream, storing the address  of the
 * buffer containing the text into lineptr.
 *
 * @lineptr: Buffer to store the text.
 * @n: Pointer to the size of bytes to read at once.
 * @stream: The file to read from.
 *
 * Return: Number of characters read, -1 on error, 0 when a new line or EOF is
 * reached.
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	int i;
	ssize_t nread, old_len, len = 0;
	char buf[BUFF_SIZE + 1];

	while (1)
	{
		nread = read(fd, &buf, BUFF_SIZE);
		old_len = len;

		if (nread == -1)
			return (-1);
		if (nread == 0)
			break;

		len += nread;
		*n = len;

		if (fill_buf(lineptr, buf, &old_len, &len))
			return(0);
	}

	return (len);
}
