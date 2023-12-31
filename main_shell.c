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
	int i, length;

	data->args = NULL;
	data->argvs = NULL;
	i = length = 0;
	while (argv[length])
		length++;
	data->argvs = malloc(sizeof(char *) * (length + 1));
	while (i < length)
	{
		data->argvs[i] = _strdup(argv[i]);
		i++;
	}
	data->argvs[i] = NULL;
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

	fill_shdata(&data, argv);
	if (!isatty(STDIN_FILENO))
	{
		/*read_script(&data);*/
		non_interactive(&data);
		free_list(&(data.sh_env));
		free_aop(data.argvs);
		return (0);
	}

	run_shell(&data);
	free_list(&(data.sh_env));
	free_aop(data.argvs);
	return (0);
}
