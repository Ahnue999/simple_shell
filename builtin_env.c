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
	list_t *ptr = data->sh_env;

	i = 0;
	while (ptr)
	{
		for (i = 0; ptr->str[i] != '\0'; i++)
			;
		write(STDOUT_FILENO, ptr->str, i + 1);
		write(STDOUT_FILENO, "\n", 1);
		ptr = ptr->next;
	}

	free(ptr);
	return (0);
}
