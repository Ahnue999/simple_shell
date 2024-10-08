#include "main.h"

/**
 * get_builtin - checks if the command is built in
 * and fetch its function.
 * @data: the name of the command.
 *
 * Return: a pointer to the built in function.
 */
int (*get_builtin(shdata_t *data))(shdata_t *)
{
	builtin_funcs_t functions[] = {
		{"exit", builtin_exit},
		{"env", builtin_env},
		{"cd", builtin_cd},
		{"setenv", builtin_setenv},
		{"unsetenv", builtin_unsetenv},
		{NULL, NULL}
	};
	int i;

	if (!data->args[0])
		return (NULL);
	i = 0;
	while (functions[i].name)
	{
		if (_strcmp(data->args[0], functions[i].name) == 0)
			break;
		i++;
	}

	return (functions[i].func);
}

/**
 * builtin_exit - exits the shell.
 * @data: the shell data.
 *
 * Return: 0 when success.
 */
int builtin_exit(shdata_t *data)
{
	free_list(&(data->sh_env));
	free_aop(data->argvs);
	free_aop(data->args);
	_exit(data->status);
}

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

	free_list(&ptr);
	return (0);
}

/**
 * builtin_cd - change current working directory.
 * @data: the shell data.
 *
 * Return: 0 when success.
 */
int builtin_cd(shdata_t *data)
{
	char *home, *oldpwd, *tmphome, *tmpold, *cwd;
	char **env_arr;
	int status, i;

	cwd = getcwd(NULL, 4096);
	env_arr = list_to_array(data->sh_env);
	tmphome = _getenv("HOME", env_arr);
	i = 0;
	while (tmphome[i] != '=' && tmphome[i] != '\0')
		i++;
	home = (tmphome += i);
	tmpold = _getenv("OLDPWD", env_arr);
	i = 0;
	while (tmpold[i] != '=' && tmpold[i] != '\0')
		i++;
	oldpwd = (tmpold += i);

	if (!data->args[1] || _strcmp(data->args[1], "~") == 0)
		status = chdir(home);
	else if (_strcmp(data->args[1], "-") == 0)
		status = chdir(oldpwd);
	else
		status = chdir(data->args[1]);

	if (status == -1)
	{
		data->status = 2;
		perror("");
	}
	else
	{
		data->args[1] = "OLDPWD";
		data->args[2] = _strdup(cwd);
		builtin_setenv(data);
	}
	free(cwd);
	free(tmphome);
	free(tmpold);
	free_aop(env_arr);
	return (0);
}
