#include "_getline.h"

/**
* _getline - reads an entire line from a file descriptor
* @fd: file descriptor to read from
*
* Return: null-terminated string without newline, else NULL
*/
char *_getline(const int fd)
{
	static char *buffer;
	static int idx;
	int start;
	char *out = NULL, *temp = NULL;

	if (buffer == NULL)
	{
		idx = 0;
		buffer = malloc(sizeof(char) * (READ_SIZE + 1));
		if (buffer == NULL)
			return (NULL);
		memset(buffer, 0, READ_SIZE + 1);
		if (read(fd, buffer, READ_SIZE) == -1)
			return (NULL);
	}

	if (idx < READ_SIZE && *(buffer + idx) == '\0')
		idx++;

	start = idx;
	while (*(buffer + idx) != '\n' && *(buffer + idx) != '\0' && idx < READ_SIZE)
		idx++;

	if (idx == READ_SIZE)
	{
		if (start != idx)
			out = strdup(buffer + start);
		else
			out = NULL;
		free(buffer);
		buffer = NULL;
		idx = 0;
		temp = _getline(fd);
		if (temp == NULL)
		{
			if (out != NULL)
				free(out);
			if (buffer != NULL)
				free(buffer);
			return (NULL);
		}
		if (out != NULL)
		{
			out = realloc(out, 1 + _strlen(out) + _strlen(temp));
			strcat(out, temp);
			free(temp);
		}
		else
			out = temp;
		return (out);
	}

	if (*(buffer + idx) == '\0')
	{
		if (idx != start)
			out = strdup(buffer + start);
		free(buffer);
		return (out);
	}

	if (idx != start || *(buffer + idx) == '\n')
	{
		*(buffer + idx) = '\0';
		out = strdup(buffer + start);
	}

	return (out);
}

/**
* _strlen - returns length of input string
* @input: string to determine the length of
*
* Return: length of input string, else 0
*/
int _strlen(char *input)
{
	int i = 0;

	if (input == NULL)
		return (0);

	while (input[i])
		i++;

	return (i);
}
