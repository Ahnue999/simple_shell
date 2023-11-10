#include "main.h"

/**
  * check_symbol - checks for ";" and "#".
  * @str: the string to check.
  *
  * Return: an array of commands.
  */
char **check_symbols(char *string)
{
	char **cmd_arr;
	int i = 0;

	while(string[i])
	{
		if (string[i] == '#')
		{
			string[i] = '\0';
			break;
		}
		i++;
	}

	cmd_arr = split_string(string, ";");
	return (cmd_arr);
}
