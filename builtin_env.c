#include "main.h"

/**
 * builtin_env - prints the process environment.
 * @data: shell data.
 *
 * Return: 0 when success.
 */
int builtin_env(shdata_t *data)
{
	int i;

	i = 0;
	while(data->sh_env)
	{
		for (i = 0; data->sh_env->str[i] != '\0'; i++)
			;
		write(STDOUT_FILENO, data->sh_env->str, i + 1);
		write(STDOUT_FILENO, "\n", 1);
		data->sh_env = data->sh_env->next;
	}

	return (0);
}
