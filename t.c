#include "hash.h"

int main(int ac, char **av, char **env)
{
	pid_t pid = fork();

	if (pid == -1)
		perror(av[0]);

	else if (pid == 0)
	{
		execve(av[1], av[1], env);
	}
	else {
		int status;
		wait(&status);
	return (0);
}
