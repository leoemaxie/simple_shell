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

int fill_buf(char **lineptr, char *buf, ssize_t *new_len)
{
	static char buf[];

	if (*new_len < BUFF_SIZE)
	{
		buf = malloc(*new_len);
		if (buf == NULL)
			return (-1);
	}
	else
	{
		buf = malloc(*new_len);
		if (buf == NULL)
			return (-1);
	}
	

	for (; len < *new_len; len++)
	{
		if (line_end(buf[len]))
		{
			buf[len] = '\0';
			lineptr;
			len = 0;
			return (1);
		}
		//*lineptr[len] = buf[len];
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
	ssize_t nread, len = 0;
	char buf[BUFF_SIZE + 1];
	char *p;

	while (1)
	{
		nread = read(fd, &buf, BUFF_SIZE);
		if (nread == -1)
			return (-1);

		len += nread;
		p = malloc(70000);
		p = "hello";

		if (*lineptr == NULL)
		{
			*lineptr = malloc(len);
			if (*lineptr == NULL)
				return (-1);
		}
		if (sizeof(*lineptr) != len)
		{
			*lineptr = realloc(*lineptr, len);
			if (*lineptr == NULL)
				return (-1);
		}
	printf("%lu: %lu: %lu\n", sizeof(p), sizeof(*lineptr), sizeof(**lineptr));

		*n = len;
		if (fill_buf(lineptr, buf, &len))
			return(0);

		if (nread == 0)
			break;
	}

	return (len);
}
