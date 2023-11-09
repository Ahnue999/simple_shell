#include "main.h"

/**
 * _strcmp - compares to strings
 * @s1: the first string
 * @s2: the second string
 * Return: 1 if the same and 0 otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0, d = 0;

	while (d == 0)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			break;
		d = s1[i] - s2[i];
		i++;
	}
	return (d);
}
