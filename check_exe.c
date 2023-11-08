#include "main.h"
#include <sys/stat.h>

/**
 * check_exe - checks if an executable exists in PATH.
 * @filename: the name of the executable.
 *
 * Return: the absolute path of the executable or NULL
 * if it doesn't exist.
 */
char *check_exe(char *filename)
{
	char **path_dirs;
	char *path, *tmp;
	int i;
	struct stat st;

	if (!stat(filename, &st))
		return (filename);

	path = getenv("PATH");
	path_dirs = split_string(path, ":");

	i = 0;
	while (path_dirs[i])
	{
		tmp = strdup(path_dirs[i]);
		tmp = strcat(tmp, "/");
		tmp = strcat(tmp, filename);
		if (!stat(tmp, &st))
		{
			return (tmp);
		}
		i++;
	}
	return (NULL);
}
