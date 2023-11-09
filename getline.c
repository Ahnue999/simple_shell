#include "main.h"

/**
 * _realloc - reallocates a memory block
 * @ptr: old memory
 * @old_size: size of ptr
 * @new_size: size of the new memory
 * Return: pointer to new memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;
	unsigned int index;
	char *old_ptr;

	if (new_size == old_size)
		return (ptr);

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size > old_size)
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (NULL);
	}

	old_ptr = ptr;
	index = 0;
	while (index < old_size)
	{
		new_ptr[index] = old_ptr[index];
		index++;
	}
	free(old_ptr);

	return (new_ptr);
}

int _fileno(FILE *stream)
{
	if (stream == NULL)
		return (-1);

	return stream->_fileno;
}

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	static char *buffer = NULL;
	static size_t index;
	ssize_t bytes_read;
	int fd;

	if (*lineptr == NULL)
	{
		*n = 120; /* initial buffer siuze */
		buffer = malloc(sizeof(char) * (*n));
		if (buffer == NULL)
			return (-1);
		*lineptr = buffer;
	}

	index = 0;
	fd = _fileno(stream);
	while (1)
	{
		if (index == 0)
		{
			bytes_read = read(fd, &buffer[index], *n);      
			if (bytes_read == -1 || bytes_read == 0)
				return (-1);
		}
		buffer[bytes_read] = '\0';

		while (buffer[index] != '\n')
		{
			(*lineptr)[index] = buffer[index];
			index++;
			if (index >= *n)
			{
				*n *= 2; /* Double the size of the buffer */      
				buffer = _realloc(buffer, index, index + 1);      
				if (buffer == NULL)
					return (-1);
			}
		}
		if (buffer[index] == '\n')
			break;
	}
	buffer[index] = '\0';

	return (index);
}