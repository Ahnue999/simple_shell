#include "main.h"

/**
  * path_list - makes a linked list of the PATH directories.
  *
  * Return: a pointer to the head.
  */
list_t *path_list(void)
{
	char *path;
	char **path_dirs;
	list_t *head = NULL;
	int i;

	path = _getenv("PATH");
	path_dirs = split_string(path, ":");

	i = 0;
	while (path_dirs[i])
	{
		add_node_end(&head, path_dirs[i]);
		i++;
	}

	return (head);
}
