#include "hash.h"

/**
 * get_cmd_path - Adds, changes, and deletes environment variables.
 *
 * @cmd: Pointer to a character string that contains the name of the
 * command a user input into the shell.
 * @err: Error structure containing the nature of the erroroccured while
 * executing shell commands.
 *
 * Return: A pointer to the path of the command or NULL on error.
 */
char *get_cmd_path(const char *cmd, err_t err)
{
	char *path = _getenv("PATH");
	char *token = strtok(path, ":");
	char cmd_path[BUFF_SIZE];
	char *ptr;

	while (token != NULL)
	{
		_strcpy(cmd_path, token);
		_strcat(cmd_path, "/");
		_strcat(cmd_path, cmd);

		if (access(cmd_path, X_OK) == 0)
		{
			ptr = cmd_path;
			return (ptr);
		}
		token = strtok(NULL, ":");
	}

	err.print(err);
	return (NULL);
}
