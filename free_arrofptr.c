#include "main.h"

/**
  * free_aop - frees an array of pointers.
  * @arr: the array to free
  *
  * Return: void.
  */
void free_aop(char **arr)
{
	int i = 0;

	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}
