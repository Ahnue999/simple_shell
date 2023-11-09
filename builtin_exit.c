#include "main.h"

/**
 * builtin_exit - exits the shell.
 * @data: the shell data.
 * 
 * Return: 0 when success.
 */
int builtin_exit(__attribute__((unused)) shdata_t *data)
{
	printf("im exit\n");
	return (0);
}
