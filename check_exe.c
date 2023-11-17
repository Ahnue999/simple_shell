#include "main.h"
#include <sys/stat.h>

/**
 * check_exe - checks if an executable exists in PATH.
 * @filename: the name of the executable.
 * @env: environment variable
 * Return: the absolute path of the executable or NULL
 * if it doesn't exist.
 */
char *check_exe(char *filename, list_t *env)
{
	char **path_dirs;
	char **env_arr;
	char *path, *tmp;
	int i;
	struct stat st;

	if (!stat(filename, &st))
		return (filename);

	env_arr = list_to_array(env);
	path = _getenv("PATH", env_arr);
	free_aop(env_arr);
	path_dirs = split_string(path, ":");

	i = 0;
	while (path_dirs[i])
	{
		tmp = _strdup(path_dirs[i]);
		tmp = strcat_alloc(tmp, "/");
		tmp = strcat_alloc(tmp, filename);
		if (!stat(tmp, &st))
		{
			free_aop(path_dirs);
			return (tmp);
		}
		else
			free(tmp);
		i++;
	}
	free_aop(path_dirs);
	return (NULL);
}
