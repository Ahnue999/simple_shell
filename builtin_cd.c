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
	char *cwd;
	char **env_arr;
	int status;

	cwd = getcwd(NULL, 4096);
	env_arr = list_to_array(data->sh_env);
	home = _getenv("HOME", env_arr);
	oldpwd = _getenv("OLDPWD", env_arr);

	if (!data->args[1] || _strcmp(data->args[1], "~") == 0)
		status = chdir(home);
	else if (_strcmp(data->args[1], "-") == 0)
		status = chdir(oldpwd);
	else
		status = chdir(data->args[1]);

	if (status == -1)
		perror("");
	else
	{
		data->args[1] = "OLDPWD";
		data->args[2] = strdup(cwd);
		builtin_setenv(data);
	}
	return (0);
}
