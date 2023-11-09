#include "main.h"

extern char **environ;

/**
 * fill_shdata - fills the shdata_t structure.
 * @data: the empty structure.
 * @argv: main arguments.
 *
 * Return: 0 when succes and 1 otherwise.
 */
int fill_shdata(shdata_t *data)
{
	/* yes, it is incomplete */
	int i;

	data->status = 0;
	for (i = 0; environ[i]; i++)
		;

	data->sh_env = malloc(sizeof(char *) * i + 1);
	if (!data->sh_env)
		exit(1);

	i = 0;
	while (environ[i])
	{
		data->sh_env[i] = strdup(environ[i]);
		i++;
	}
	data->sh_env[i] = NULL;

	return (0);
}

/**
 * main - entry point.
 * @argc: arguments count.
 * @argv: arguments vector.
 *
 * Return: always 0.
 */
int main(__attribute__((unused)) int argc, char **argv)
{
	shdata_t data;

	fill_shdata(&data);
	if (argc > 1)
	{
		non_interactive(argv);
		return (0);
	}

	run_shell(&data);
	return (0);
}
