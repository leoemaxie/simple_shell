#include "test.h"

int main(int ac, char **av, char **env)
{
	int lineno = 0;
	char *msg = NULL;

	err_t e = {av[0], lineno, msg, printerr};
	e.print(e);

	return (0);
}
