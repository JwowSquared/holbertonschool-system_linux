#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "hls.h"

/**
* print_dir - prints a directory
* @path: path of directory to print
* @flags: bools that influence what is printed/how its displayed
*/
void print_dir(char *path, int *flags)
{
	DIR *dir;
	struct dirent *current;
	int num_out = 0;

	dir = opendir(path);
	current = readdir(dir);
	while (current != NULL)
	{
		if (hidden_check(current->d_name, flags))
			num_out++;
		current = readdir(dir);
	}
	closedir(dir);

	dir = opendir(path);
	current = readdir(dir);
	while (current != NULL)
	{
		if (hidden_check(current->d_name, flags))
		{
			if (--num_out <= 0 || flags[0])
				printf("%s\n", current->d_name);
			else
				printf("%s  ", current->d_name);
		}
		current = readdir(dir);
	}
	closedir(dir);
}

/**
* hidden_check - checks if a file/directory should be displayed
* @path: raw path
* @flags: modes to determine if the path should be displayed
*
* Return: 1 if path should be printed, else 0
*/
int hidden_check(char *path, int *flags)
{
	if (flags[1])
		return (1);
	if (flags[2])
	{
		if (path[0] == '.')
		{
			if (path[1] == '\0')
				return (0);
			if (path[1] == '.' && path[2] == '\0')
				return (0);
			return (1);
		}
	}
	if (path[0] == '.')
		return (0);
	return (1);
}
