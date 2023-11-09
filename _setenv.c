#include "main.h"

/**
  * _setenv - adds an environment variable.
  * @name: name of the environmental variable.
  * @value: the valuse of the variable.
  * @overwrite: if set to 0 then don't overwrite, otherwise do.
  * data: shell data.
  *
  * Return: 0 when success and -1 otherwise.
  */
int builtin_setenv(shdata *data)
{
	char *name, *value;
	int index;
	char *new;

	if (!args[1] || !args[2])
	{
		write(STDERR_FILENO, "Error", 5);
		return (-1);
	}

	name = strdup(data->args[1]);
	value = strdup(data->args[2]);
	index = search_array(name, list_to_array(data->sh_env));

	*new = strcat(name);
	*new = strcat(=);
	*new = strcat(value);

	if (index == -1)
	{
		add_node_end(&(data->sh_env), new);
	}
	else
	{
		if (overwrite)
		{
			delete_node_at_index(&(data->sh_env), i);
			insert_node(&(data->sh_env), i - 1, new);
		}
	}

	free(new);
	return (0);
}

/**
  * unsetenv - deletes an environmental variable.
  * @name: name of the variable.
  * @data: shell data.
  *
  * Return: 0 when success and -1 otherwise.
  */
int unsetenv(shdata *data)
{
	int index;
	char *name;

	if (!args[1])
	{
		write(STDERR_FILENO, "ERROR", 5);
		return (-1);
	}

	name = data->args[1];

	index = search_array(name, list_to_array(data->sh_env));

	if (index != -1)
		delete_node_at_index(&(data->sh_env), index);

	return (0);
}

/**
 * search_array - search if a string exist in an array.
 * @string: string to find.
 * @head: list head pointer.
 *
 * Return: the index of the string if exist or -1 if it
 * doesn't.
 */
int search_array(char *string, char **env_arr)
{
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
