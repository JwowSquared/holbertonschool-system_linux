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
	char *out = NULL;

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

	start = idx;
	while (*(buffer + idx) != '\n' && *(buffer + idx) != '\0' && idx < READ_SIZE)
		idx++;

	if (idx == READ_SIZE)
		return (end_of_buffer(start, idx, &buffer, fd));

	if (*(buffer + idx) != '\0' || idx != start)
		out = _strndup(buffer + start, idx - start);
	if (*(buffer + idx) == '\0')
	{
		free(buffer);
		buffer = NULL;
	}
	if (idx < READ_SIZE)
		idx++;

	return (out);
}

/**
* end_of_buffer - this handles lines that need multiple reads
* @start: left bound of string
* @idx: right bound of string
* @buffer: double pointer to buffer so it can be freed
* @fd: file descriptor passed in _getline function
*
* Return: full line string, else NULL
*/
char *end_of_buffer(int start, int idx, char **buffer, int fd)
{
	char *out = NULL, *temp = NULL;

	if (start != idx)
		out = strdup((*buffer) + start);
	else
		out = NULL;
	free(*buffer);
	*buffer = NULL;
	temp = _getline(fd);
	if (temp == NULL)
	{
		if (out != NULL)
			free(out);
		if (*buffer != NULL)
			free(*buffer);
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

/**
* _strndup - duplicates n chars of a string
* @src: source string to copy from
* @n: number of chars to copy
*
* Return: pointer to new string, else NULL
*/
char *_strndup(char *src, int n)
{
	int i = 0;
	char *out;

	out = malloc(sizeof(char) * (n + 1));
	if (out == NULL)
		return (NULL);

	while (i < n)
	{
		out[i] = src[i];
		i++;
	}

	out[n] = '\0';
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
