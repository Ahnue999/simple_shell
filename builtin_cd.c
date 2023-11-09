#include "main.h"

/**
 * builtin_cd - change current working directory.
 * @data: the shell data.
 * 
 * Return: 0 when success.
 */
int builtin_cd(shdata_t *data)
{
	char *home, *oldpwd;
	char **env_arr;

	env_arr = list_to_array(data->sh_env);
	home = _getenv("HOME", env_arr);
	oldpwd = _getenv("OLDPWD", env_arr);

	if (!data->args[1] || _strcmp(data->args[1], "~") == 0)
	{
		if (chdir(home) == -1)
			perror("");
	}

	else if (_strcmp(data->args[1], "-") == 0)
	{
		if (chdir(oldpwd) == -1)
			perror("");
	}

	else if (chdir(data->args[1]) == - 1)
		perror("");

	return (0);
}
