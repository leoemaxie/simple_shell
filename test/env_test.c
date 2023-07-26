#include "test.h"

int test_getenv(void)
{
	char *env = _getenv("HOME");
	char *pwd = _getenv("PWD");
	char *path = _getenv("PATH");

	printf("%s\n%s\n%s\n", env, pwd, path);

	free(env);
	free(pwd);
	free(path);

	return (0);
}

int test_cmd_path(void)
{
	err_t err = {"hash", 0, printerr};
	char *cmd_path = get_cmd_path("vi");
	
	printf("%s\n", cmd_path);
	free(cmd_path);

	return (0);
}

int main (void)
{
	test_getenv();
	test_cmd_path();
	return (0);
}
