#include "main.h"

char **split_string(const char *str, const char *delimiter);
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
	char *str_copy1 = _strdup(str);
	char *str_copy2 = _strdup(str);

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
		str_array[index] = _strdup(token);
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

/**
 * _strcmp - compares to strings
 * @s1: the first string
 * @s2: the second string
 * Return: 1 if the same and 0 otherwise
 */
int _strcmp(char *s1, char *s2)
{
	int i = 0, d = 0;

	while (d == 0)
	{
		if (s1[i] == '\0' && s2[i] == '\0')
			break;
		d = s1[i] - s2[i];
		i++;
	}
	return (d);
}

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 * Return: a pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int len, index;
	char *new_str;

	if (str == NULL)
		return (NULL);

	len = 0;
	while (str[len] != '\0')
		len++;

	new_str = malloc(sizeof(char) * (len + 1));
	if (new_str == NULL)
		return (NULL);

	index = 0;
	while (index < len)
	{
		new_str[index] = str[index];
		index++;
	}
	new_str[index] = '\0';

	return (new_str);
}

/**
 * _atoi - converts a string to an integer.
 * @s: input string.
 * Return: integer.
 */
int _atoi(char *s)
{
	unsigned int count = 0, size = 0, oi = 0, pn = 1, m = 1, i;

	while (*(s + count) != '\0')
	{
		if (size > 0 && (*(s + count) < '0' || *(s + count) > '9'))
			break;

		if (*(s + count) == '-')
			pn *= -1;

		if ((*(s + count) >= '0') && (*(s + count) <= '9'))
		{
			if (size > 0)
				m *= 10;
			size++;
		}
		count++;
	}

	for (i = count - size; i < count; i++)
	{
		oi = oi + ((*(s + i) - 48) * m);
		m /= 10;
	}
	return (oi * pn);
}

/**
 * _strcat - concatenates two strings
 * @str1: string to add to
 * @str2: string to append
 * Return: the concatenated string
 */
char *_strcat(char *str1, const char *str2)
{
	int index1 = 0, index2 = 0;

	while (str1[index1] != '\0')
		index1++;

	while (str2[index2])
		str1[index1++] = str2[index2++];

	str1[index1] = '\0';

	return (str1);
}

/**
 * _strchr - returns a character in a string
 * @s: string
 * @c: character
 * Return: pointer to the character or NULL
 */

char *_strchr(const char *str, char c)
{
	int index = 0;

	while (str[index] != '\0')
	{
		if (str[index] == c)
		{
			return ((char *)&str[index]);
		}
		index++;
	}
	return (NULL);
}

/**
 * _strtok - breaks a string into a sequesnce of
 more non-empty tokens
 * @str: string to be parsed
 * @delim: delimits the tokens in the parsed string
 * Return: a pointer to the next token or
 NULL if there are no more tokens
 */
char *_strtok(char *str, const char *delim)
{
	static char *next_token;
	int index;

	if (str == NULL && next_token == NULL)
		return (NULL);

	if (str == NULL)
		str = next_token;

	index = 0;
	while (str[index] != '\0')
	{
		if (_strchr(delim, str[index]) != NULL)
		{
			str[index] = '\0';
			next_token = &str[index + 1];
			break;
		}
		index++;
	}
	if (str[index] == '\0')
		next_token = NULL;

	return (str);
}
