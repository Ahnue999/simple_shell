#include "main.h"

/**
 * builtin_exit - exits the shell.
 * 
 */
int builtin_exit(shdata_t *data)
{
	exit(9);
	return (0);
}
