#include "hash.h"

int cmd_exsts(const char *cmd)
{
	char *path = _getenv("PATH");
	char *token = strtok(path, ":");
	char cmd_path[BUFF_SIZE];
	char *c;

	while (token != NULL)
	{
		_strcpy(cmd_path, token);
		_strcat(cmd_path, "/");
		_strcat(cmd_path, cmd);
		if (access(cmd_path, X_OK) == 0)
			return (1);
		token = strtok(NULL, ":");
	}

	write(STDERR_FILENO, "hah", 466);
	perror("hash");
	return (0);
}
int main(int ac, char **av, char **env)
{
	err_t e = {av[0], 499056, printerr};
	e.print(e);
	//printf("%d", cmd_exists("login"));
	return (0);
}
