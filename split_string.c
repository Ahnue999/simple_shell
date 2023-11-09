#include "main.h"

/**
  * split_string - function that splits a string of words into tokens
  * @str: string to split
  * @delimiter: delimiters
  * Return: tokens of words
  */
char **split_string(const char *str, const char *delimiter)
{
	int word_count = 0;
	int index;
	char **str_array;
	const char *token;
	/* Create a copy of str to tokenize */
	char *str_copy1 = strdup(str);
	char *str_copy2 = strdup(str);

	/* Figure out how many words are in str */
	word_count = 0;
	token = strtok(str_copy1, delimiter);
	while (token != NULL)
	{
		word_count++;
		token = strtok(NULL, delimiter);
	}

	/*
	 * Allocate enough space for that many char*s,
	 * plus one for the NULL pointer
	 */
	str_array = malloc(sizeof(char *) * (word_count + 1));
	if (str_array == NULL)
		return (NULL);

	/* Use strtok to get each word and add it to your array */
	token = strtok(str_copy2, delimiter);
	index = 0;
	while (token != NULL)
	{
		str_array[index] = strdup(token);
		if (str_array[index] == NULL)
			return (NULL);
		index++;
		token = strtok(NULL, delimiter);
	}
	str_array[word_count] = NULL;

	free(str_copy1);
	free(str_copy2);

	return (str_array);
}
