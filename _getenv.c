#include <stdio.h>
#include <stdlib.h>

extern char **environ;

/**
  * _getenv - gets an enviroment variable.
  * @name: the name of the variable.
  *
  * Return: the valuse of the variable.
  */
char *_getenv(const char *name)
{
	int i, j;

	if (!name)
	{
		printf("No Name Provided");
		exit(99);
	}

	i = 0;
	while (environ[i])
	{
		j = 0;
		while (name[j])
		{
			if (environ[i][j] != name[j])
			{
				i++;
				j++;
				break;
			}
			else
				j++;
		}
		if (name[j] == '\0')
		{
			 /* remove the name of variable from the line */
			while (j + 1)
			{
				environ[i]++;
				j--;
			}
			return (environ[i]);
		}
	}
	return (NULL);
}
