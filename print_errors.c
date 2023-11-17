#include "main.h"

void print_errors(shdata_t *data);
/**
  * print_errors - prints an error.
  * @data: shell data.
  *
  * Return: void.
  */
void print_errors(shdata_t *data)
{
	char *filename, *command, *massage;
	char *ps;
	int i, length;

	filename = _strdup(data->argvs[0]);
	command = _strdup(data->args[0]);
	ps = _strdup(itos(data->ps_count));
	if (filename == NULL || command == NULL || ps == NULL)
	{
		free(filename);
		free(command);
		free(ps);
		perror("Memory allocation failed!\n");
		return;
	}

	i = length = 0;
	while (filename[i])
		i++, length++;
	i = 0;
	while (command[i])
		i++, length++;
	i = 0;
	while (ps[i])
		i++, length++;

	length += 16;

	massage = malloc(sizeof(char) * length + 1);
	if (massage == NULL)
	{
		perror("Memory allocation failed!\n");

		  free(filename);
		  free(command);
		  free(ps);
		 
		return;
	}
	massage[0] = '\0';

	massage = strcat(massage, filename);
	massage = strcat(massage, ": ");
	massage = strcat(massage, ps);
	massage = strcat(massage, ": ");
	massage = strcat(massage, command);
	massage = strcat(massage, ": ");
	massage = strcat(massage, "not found\n");

	write(STDOUT_FILENO, massage, _strlen(massage));
	
	  free(massage);
	  free(filename);
	  free(command);
	  free(ps);
}
