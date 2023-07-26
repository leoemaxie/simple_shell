#include "hash.h"

/**
 * line_end - Determines whether a character is a newline, or EOF .
 *
 * @c: The character to check.
 *
 * Return: 1 when a character is a newline or EOF, 0 otherwise.
 */
int line_end(int c)
{
	switch (c)
	{
		case '\n':
			return (1);
		case EOF:
			exit (0);
		case CTRL_KEY('c'):
			exit(1);
		default:
			return (0);
	}
}

/**
 * resize - Dybamically resize a buffer.
 *
 * @lineptr: Pointer to the buffer to resize.
 * @old_len: Length of the previous characters read.
 * @new_len: Length of the current unread characters.
 *
 * Return: 0 on success, -1 on error .
 */
int resize(char **lineptr, ssize_t old_len, ssize_t new_len)
{
	if (new_len <= BUFF_SIZE)
	{
		*lineptr = malloc(new_len);
		if (!*lineptr)
			return (-1);
	}
	else
	{
		*lineptr = _realloc(*lineptr, old_len, new_len);
		if (!*lineptr)
			return (-1);
	}
	return (0);
}

/**
 * fill_buf - Fills a buffer with characters read upto a newline or EOF.
 *
 * @lineptr: Pointer to the buffer to fill the characters read.
 * @buf: Buffer to read characters from.
 * @old_len: Length of the previous characters read.
 * @new_len: Length of the current unread characters.
 *
 * Return: 1 when lineptr has been filled (i.e when a newline or EOF has been
 * reached), 0 otherwise.
 */
int fill_buf(char **lineptr, char *buf, ssize_t old_len, ssize_t new_len)
{
	int i, j = 0;
	int end_of_line;

	for (i = old_len; i < new_len; i++)
	{
		end_of_line = line_end(buf[j]);

		if (end_of_line)
		{
			if (j < 1)
				return (-1);
			(*lineptr)[i] = '\0';
			return (1);
		}

		(*lineptr)[i] = buf[j++];
	}
	return (0);
}

/**
 * _getline - reads an entire line from stream, storing the address  of the
 * buffer containing the text into lineptr.
 *
 * @lineptr: Buffer to store the text.
 * @n: Pointer to the size of bytes read.
 * @fd: The file descriptor to read from.
 *
 * Return: Number of characters read, -1 on error, 0 when a newline or EOF is
 * reached.
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	int is_full = 1;
	ssize_t nread, old_len, len = 0;
	char buf[BUFF_SIZE];

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

		if (resize(lineptr, old_len, len) == -1)
			return (-1);

		is_full = fill_buf(lineptr, buf, old_len, len);
		if (is_full == -1)
			return (-1);
		if (is_full)
			return (0);
	}

	return (len);
}

/**
 * getfd - Gets the file descriptor of a file.
 *
 * @filename: The name of the file to open.
 *
 * Return: The file descriptor of the file or -1 if an error occurs when
 * opening the file.
 */
int getfd(const char *filename)
{
	int file = filename != NULL ? open(filename, O_RDONLY) : -1;

	if (file == -1)
		return (-1);
	return (file);
}
