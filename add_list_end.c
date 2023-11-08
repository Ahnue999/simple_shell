#include "main.h"

/**
  * add_node_end - adds a node to the end of a nexted list.
  * @head : a pointer to the head pointer.
  * @str: the string to add.
  *
  * Return: the new list after update.
  */
list_t *add_node_end(list_t **head, char *str)
{
	list_t *new, *temp;

	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);

	new->str = strdup(str);
	new->next = NULL;

	temp = *head;
	if (!temp)
	{
		*head = new;
	}
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}
