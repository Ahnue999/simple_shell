#include "main.h"

/**
  * _getenv - gets an enviroment variable.
  * @name: the name of the variable.
  *
  * Return: the valuse of the variable.
  */
char *_getenv(const char *name, char **env_arr)
{
	int i, j;
	char *ret;

	if (!name)
	{
		printf("No Name Provided");
		exit(99);
	}

	i = 0;
	while (env_arr[i])
	{
		j = 0;
		while (name[j])
		{
			if (env_arr[i][j] != name[j])
			{
				i++;
				break;
			}
			else
				j++;
		}
		if (name[j] == '\0' && env_arr[i][j] == '=')
		{
			 /* remove the name of variable from the line */
			ret = strdup(env_arr[i]);
			while (j + 1)
			{
				ret++;
				j--;
			}
			return (ret);
		}
	}
	return (NULL);
}
