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
			if (str[i + 1] && str[i + 1] != '\n')
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
 * expand_str - expands a string variable.
 * @str: the string to check.
 * @newstr: the str's portion behind the $.
 * @after: the str's portion after the $.
 * @i: the index of the expand specifier.
 * @data: shell data.
 *
 * Return: the command after expantion.
 */
char *expand_str(char *str, char *newstr, char *after, int *i, shdata_t *data)
{
	int len, j;
	char *var_name, *tmp_var, *var_value;
	char **env_arr;

	len = j = 0;
	while (str[*i + 1 + len] != ' ' && str[*i + 1 + len] != '\n')
		len++;
	var_name = malloc(sizeof(char) * len + 1);
	while (j < len)
		var_name[j] = str[*i + 1 + j], j++;
	var_name[j] = '\0';
	env_arr = list_to_array(data->sh_env);
	tmp_var = _getenv(var_name, env_arr);
	if (tmp_var == NULL)
		var_value = "";
	else
		var_value = (tmp_var + len + 1);
	free_aop(env_arr);
	newstr = strcat_alloc(newstr, var_value);
	newstr = strcat_alloc(newstr, after);
	i += _strlen(var_value);
	free(var_name);
	free(tmp_var);

	return (newstr);
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
	char *before, *after, *new = "", *tmp;

	tmp = _strdup(str);
	before = after = tmp;
	before[*i] = '\0';
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
			new = expand_str(str, new, after, i, data);

	}
	free(before);
	return (new);
}
