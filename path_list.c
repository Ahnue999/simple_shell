#include "main.h"

/**
  * path_list - makes a linked list of the PATH directories.
  *
  * Return: a pointer to the head.
  */
list_t *path_list(shdata_t data)
{
	char *path;
	char **path_dirs, **env_arr;
	list_t *head = NULL;
	int i;

	env_arr = list_to_array(data.sh_env);
	path = _getenv("PATH", env_arr);
	path_dirs = split_string(path, ":");

	i = 0;
	while (path_dirs[i])
	{
		add_node_end(&head, path_dirs[i]);
		i++;
	}

	return (head);
}
