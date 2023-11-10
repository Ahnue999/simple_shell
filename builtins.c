#include "main.h"

/**
 * builtin_exit - exits the shell.
 * @data: the shell data.
 * 
 * Return: 0 when success.
 */
int builtin_exit(shdata_t *data)
{
	_exit(data->status);
}
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
