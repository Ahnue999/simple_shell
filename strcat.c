#include "main.h"

/**
  * _strcat - concatenates two strings
  * @str1: string to add to
  * @str2: string to append
  * Return: the concatenated string
  */
char *_strcat(char *str1, const char *str2)
{
	int index1 = 0, int index2 = 0;

	while (str1[index1] != '\0')
		index1++;

	while (str2[index2])
		str1[index1++] = str2[index2++];

	str1[index1] = '\0';

	return (str1);
}
