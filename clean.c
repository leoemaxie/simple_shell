#include "hash.h"

void clean_env(void)
{
	int init_len = get_initial_env_len();
	int len = arrlen(environ);
	int i;

	if (len > init_len)
	{
		for (i = len; i < init_len; i++)
			free(environ[i]);
	}
}
