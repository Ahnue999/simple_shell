#include "main.h"

/**
 * get_builtin - checks if the command is built in
 * and fetch its function.
 * @command: the name of the command.
 *
 * Return: a pointer to the built in function.
 */
int (*get_builtin(shdata_t *data))(shdata_t *)
{
	builtin_funcs_t functions [] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{"cd", builtin_cd},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{NULL, NULL}
		{NULL, NULL}
		{NULL, NULL}
	};
	int i;

	i = 0;
	while (functions[i].name)
	{
		if (_strcmp(data->args[0], functions[i].name) == 0)
			break;
		i++;
	}

	return (functions[i].func);
}
