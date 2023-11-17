#include "main.h"

/**
  * check_symbols - checks for ";" and "#".
  * @str: the str to check.
  * @data: shell data.
  *
  * Return: an array of commands.
 */
char **check_symbols(char *str, shdata_t *data)
{
	char **cmd_arr;
	int i = 0;

	while (str[i])
	{
		if (str[i] == '#')
		{
			str[i] = '\0';
			break;
		}
		else if (str[i] == '$')
		{
			if (str[i + 1])
			{
				switch (str[i + 1])
				{
					case '$':
						str = expand(str, &i, '$', data);
						break;
					case '?':
						str = expand(str, &i, '?', data);
						break;
					case ' ':
						break;
					default:
						str = expand(str, &i, 'v', data);
				}
			}
		}
		i++;
	}
	cmd_arr = split_string(str, "\n;\t\0");
	return (cmd_arr);
}

/**
 * expand - expands a shell variable.
 * @str: the whole command (will be edited).
 * @i: the index of the expand specifier.
 * @to_expand: type of expantion.
 * @data: shell data.
 *
 * Return: the command after expantion.
 */
char *expand(char *str, int *i, char to_expand, shdata_t *data)
{
	char *before, *after, *new = "", *var_name, *var_value, *tmp;
	char **env_arr;
	int len, j;

	before = _strdup(str);
	before[*i] = '\0';
	tmp = _strdup(str);
	after = tmp;
	after = after + *i;
	while (!(*after == ' ' || *after == '\0'))
		after++;
	new = strcat_alloc(new, before);
	switch (to_expand)
	{
		case '$':
			data->pid = getpid();
			new = strcat_alloc(new, itos(data->pid));
			new = strcat_alloc(new, after);
			(*i) += _strlen(itos(data->pid));
			break;
		case '?':
			new = strcat_alloc(new, itos(data->status));
			new = strcat_alloc(new, after);
			(*i) += _strlen(itos(data->status));
			break;
		case 'v':
			len = j = 0;
			while (str[*i + 1 + len] != ' ' && str[*i + 1 +len] != '\n')
				len++;
			var_name = malloc(sizeof(char) * len + 1);
			while (j < len)
				var_name[j] = str[*i + 1 + j], j++;
			var_name[j] = '\0';
			env_arr = list_to_array(data->sh_env);
			var_value = _getenv(var_name, env_arr);
			free_aop(env_arr);
			if (var_value == NULL)
				var_value = "";
			new = strcat_alloc(new, var_value);
			new = strcat_alloc(new, after);
			i += _strlen(var_value);
			free(var_name);
	}
	
	 free(before);
	 free(tmp);
	 
	return (new);
}
