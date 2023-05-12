#include "hash.h"

/**
 * die - Terminates the current shell execution if an error occurs and prints
 * the error to STDERR.
 *
 * @s: The error to print.
 *
 * Return: Nothing.
 */
void die(const char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

/**
 * close_fd - Closes a file descriptor and prints an error message to STDERR
 * when an error is encountered.
 *
 * @fd: The file descriptor to close.
 *
 * Return: Nothing.
 */
void close_fd(int fd)
{
	if (close(fd) == -1)
		die("close");
	
}
