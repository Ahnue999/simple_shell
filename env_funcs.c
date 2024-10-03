#include "main.h"

/**
  * _getenv - gets an enviroment variable.
  * @name: the name of the variable.
  * @env_arr: environment list
  * Return: the valuse of the variable.
  */
char *_getenv(const char *name, char **env_arr)
{
	int i, j;
	char *var;

	if (!name)
	{
		printf("No Name Provided");
		exit(99);
	}

	i = 0;
	while (env_arr[i])
	{
		j = 0;
		while (name[j])
		{
			if (env_arr[i][j] != name[j])
			{
				i++;
				break;
			}
			else
				j++;
		}
		if (name[j] == '\0' && env_arr[i][j] == '=')
		{
			var = _strdup(env_arr[i]);
			return (var);
		}
	}
	return (NULL);
}

/**
 * builtin_setenv - adds an environment variable.
 * @data: shell data.
 *
 * Return: 0 when success and -1 otherwise.
 */
int builtin_setenv(shdata_t *data)
{
	char *name, *value, *new;
	int index;
	char **env_arr;

	if (!data->args[1] || !data->args[2])
	{
		write(STDERR_FILENO, "Error", 5);
		data->status = 2;
		return (-1);
	}
	name = _strdup(data->args[1]);
	value = _strdup(data->args[2]);
	env_arr = list_to_array(data->sh_env);
	index = search_array(name, env_arr);
	free_aop(env_arr);
	new = malloc(sizeof(char) * 1024);
	if (!new)
	{
		free(name);
		free(value);
		return (-1);
	}
	strcat(new, name);
	strcat(new, "=");
	strcat(new, value);
	if (index == -1)
		add_node_end(&(data->sh_env), new);
	else
	{
		if (data->setenv_flag)
		{
			delete_node_at_index(&(data->sh_env), index);
			insert_node(&(data->sh_env), index, new);
		}
	}
	free(new);
	free(name);
	free(value);
	return (0);
}

/**
 * builtin_unsetenv - deletes an environmental variable.
 * @data: shell data.
 *
 * Return: 0 when success and -1 otherwise.
 */
int builtin_unsetenv(shdata_t *data)
{
	int index;
	char *name;
	char **env_arr;

	if (!data->args[1])
	{
		write(STDERR_FILENO, "ERROR", 5);
		data->status = 2;
		return (-1);
	}

	name = data->args[1];

	env_arr = list_to_array(data->sh_env);
	index = search_array(name, env_arr);
	free_aop(env_arr);

	if (index != -1)
		delete_node_at_index(&(data->sh_env), index);

	free(name);
	return (0);
}

/**
 * search_array - search if a string exist in an array.
 * @string: string to find.
 * @env_arr: list head pointer.
 *
 * Return: the index of the string if exist or -1 if it
 * doesn't.
 */
int search_array(char *string, char **env_arr)
{
	int i, j;

	i = 0;
	while (env_arr[i])
	{
		j = 0;
		while (string[j])
		{
			if (env_arr[i][j] != string[j])
			{
				i++;
				break;
			}
			else
				j++;
		}
		if (string[j] == '\0' && env_arr[i][j] == '=')
		{
			return (i);
		}
	}
	return (-1);
}
