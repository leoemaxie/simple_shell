#include "hash.h"

int main(int ac, char **av, char **env)
{
	_setenv("JOME", "NULL", 1);
	//puts(env[31]);
	printenv();
	printf("%lu", sizeof(env));
	//printenv();
	return (0);
}
