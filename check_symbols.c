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

	cmd_arr = split_string(string, ";");
	return (cmd_arr);
}
