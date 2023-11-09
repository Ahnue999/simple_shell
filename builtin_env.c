#include "main.h"

/**
 * builtin_env - prints the process environment.
 * data: shell data.
 *
 * Return:
 */
int builtin_env(shdata_t *data)
{
	int i = 0;

	while(data->sh_env[i])
	{
		printf("%s", sh_env[i]);
		i++;
	}
}
