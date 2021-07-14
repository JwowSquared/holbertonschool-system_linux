#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include "hls.h"

/**
*
*/
int main(int ac, char **av)
{
	int *flags = NULL;
	int idx, multi, num_targets = 0, *key = NULL;

	key = malloc(sizeof(int) * ac);
	if (key == NULL)
		return (1);

	update_flags(&flags, NULL);
	key[0] = 0;
	for (idx = 1; idx < ac; idx++)
	{
		key[idx] = 0;
		if (av[idx][0] == '-')
			update_flags(&flags, av[idx]);
		else
		{
			key[idx] = 1;
			num_targets++;
		}
	}
	multi = num_targets;

	for (idx = 0; idx < ac; idx++)
		if (key[idx])
		{
			if (multi > 1)
				printf("%s:\n", av[idx]);
			print_dir(av[idx]);
			if (--num_targets > 0)
				printf("\n");
		}

	return (0);
}

/**
*
*/
void print_dir(char *path)
{
	DIR *dir;
	struct dirent *current;
	struct dirent *out;

	dir = opendir(path);
	current = readdir(dir);
	while (current != NULL)
	{
		out = current;
		current = readdir(dir);
		if (current == NULL)
			printf("%s\n", out->d_name);
		else
			printf("%s  ", out->d_name);
	}

	closedir(dir);
}

/**
*
*/
void update_flags(int **flags, char *input)
{
	int idx;

	if (*flags == NULL)
	{
		*flags = malloc(sizeof(int) * 8);
		if (*flags == NULL)
			return; /* memory error */
		for (idx = 0; idx < 8; idx++)
			(*flags)[idx] = 0;
	}

	if (input == NULL || input[0] != '-')
		return; /* no flags to update */

	for (idx = 1; input[idx] != '\0'; idx++)
	{
		if (input[idx] == '1')
			(*flags)[0] = 1;
		else if (input[idx] == 'a')
			(*flags)[1] = 1;
		else if (input[idx] == 'A')
			(*flags)[2] = 1;
		else if (input[idx] == 'l')
			(*flags)[3] = 1;
		else if (input[idx] == 'r')
			(*flags)[4] = 1;
		else if (input[idx] == 'S')
			(*flags)[5] = 1;
		else if (input[idx] == 't')
			(*flags)[6] = 1;
		else if (input[idx] == 'R')
			(*flags)[7] = 1;
	}
}

/**
*
*/
void print_flags(int *out)
{
	int idx = -1;

	printf("\nFlags info:\n");
	while (++idx < 8)
		printf("flag %d = %d\n", idx, out[idx]);
}
