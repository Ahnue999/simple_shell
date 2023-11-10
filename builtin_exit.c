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
