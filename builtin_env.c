#include "main.h"

/**
 * builtin_env - prints the process environment.
 * @data: shell data.
 *
 * Return: 0 when success.
 */
int builtin_env(shdata_t *data)
{
	int i, j;

	i = 0;
	while(data->sh_env[i])
	{
		for (j = 0; sh_env[i][j] != '\0'; j++)
			;
		write(STDOUT_FILENO, sh_env[i], j + 1);
		write(STDOUT_FILENO, '\n', 1);
		i++;
	}
}
