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

	data->args = NULL;
	data->status = 0;
	data->ps_count = 1;
	data->sh_env = NULL;
	data->setenv_flag = 1;

	i = 0;
	while (environ[i])
	{
		add_node_end(&(data->sh_env), *(environ + i));
		i++;
	}

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
