#include "main.h"

/**
 * fill_shdata - fills the shdata_t structure.
 * @data: the empty structure.
 * @argv: argument vector.
 *
 * Return: 0 when succes and 1 otherwise.
 */
int fill_shdata(shdata_t *data, char **argv)
{
	/* yes, it is incomplete */
	int i;

	i = 1;
	data->args = NULL;
	while (argv[i])
	{
		data->args[i - 1] = _strdup(argv[i]);
	}
	data->status = 0;
	data->ps_count = 0;
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

	fill_shdata(&data, argv);
	if (argc > 1)
	{
		read_script(&data);
		execute(&data);
		return (0);
	}

	run_shell(&data);
	return (0);
}
