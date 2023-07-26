#include "hash.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * bfree - function that frees a pointer
 * @ptr: pointer address
 *
 * Return: 0
 */

int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}

	return (0);
}
