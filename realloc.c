#include "hash.h"

/**
 * _realloc - Reallocates a block of memory.
 *
 * @ptr: Pointer to the memory previously allocated with a call to
 * malloc(old_size).
 * @old_size: The size in bytes of the allocated space for ptr.
 * @new_size: The new size in bytes of the new memory block.
 *
 * Return: A pointer to the reallocated memory.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;
	unsigned int i, n = new_size;
	char *old_p = ptr;

	if (ptr == NULL)
	{
		p = malloc(new_size);
		return (p);
	}
	else if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else if (old_size == new_size)
		return (ptr);

	p = malloc(new_size);

	if (p == NULL)
		return (NULL);
	if (new_size > old_size)
		n = old_size;

	for (i = 0; i < n; i++)
		p[i] = old_p[i];

	free(ptr);
	return (p);
}
