#include "main.h"

/**
  * _strdup - duplicates a string
  * @str: string to duplicate
  * Return: a pointer to the duplicated string
  */
char *_strdup(const char *str)
{
	int len, index;
	char *new_str;

	if (str == NULL)
		return (NULL);

	len = 0;
	while (str[len] != '\0')
		len++;

	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);

	index = 0;
	while (index < len)
	{
		new_str[index] = str[index];
		index++;
	}
	new_str[index] = '\0';

	return (new_str);
}
