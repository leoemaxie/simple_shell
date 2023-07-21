#include "hash.h"

int main(int ac, char **av, char **env)
{
	printf("%p %p", environ, env);
	printf("%s", _getenv("HOME"));
	printenv();
	return (0);
}
