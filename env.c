#include "hash.h"
void printenv(char **env)
{
	while(*env)
	{
		_puts(*env);
		_putchar('\n');
		env++;
	}
}
