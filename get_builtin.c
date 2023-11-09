#include "main.h"

/**
 * get_builtin - checks if the command is built in
 * and fetch its function.
 * @command: the name of the command.
 *
 * Return: a pointer to the built in function.
 */
int (*get_builtin(char *command))(shdata_t *)
{
	builtin_funcs_t functions [] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{NULL, NULL}
	};
	int i;

	i = 0;
	while (functions[i].name)
	{
		if (_strcmp(command, functions[i].name) == 0)
			break;
		i++;
	}

	return (functions[i].func);
}
