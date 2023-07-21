#include "hash.h"

int main(int ac, char **av, char **env)
{
	_unsetenv("_");
	printf("%p %p", environ, env);
	printf("%s", getenv("HOME"));
	printenv();
	return (0);
}
