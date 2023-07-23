#include "test.h"

int test_strtok(void)
{
	char *s1 = "Hello World;;;;;This is great ";
	char s2[] = "great";
	char *s3 = "IN 1960, A great orator was born   One who changes the world!";
	const char *delim = " ;!";
	char *token;

	token = _strtok(s1, delim);
	while (token != NULL)
	{
		printf("%s\n", token);
		token = _strtok(NULL, delim);
	}

	token = _strtok(s2, delim);
	while (token != NULL)
	{
		printf("%s\n", token);
		token = _strtok(NULL, delim);
	}

	token = _strtok(s3, delim);
	while (token != NULL)
	{
		printf("%s\n", token);
		token = _strtok(NULL, delim);
	}

	return (0);
}

int test_tokenize(void)
{
	int i = 0;
	size_t n = 0;
	char *cmd;
	char **tokens;
	
	if (_getline(&cmd, &n, STDIN_FILENO) > -1)
		tokens = tokenize(cmd);

	while (tokens[i])
	{
		puts(tokens[i]);
		i++;
	}
	
	free_tokens(tokens);
	free(cmd);
	return (0);

}

int main (void)
{
	test_strtok();
	test_tokenize();

	return (0);
}
