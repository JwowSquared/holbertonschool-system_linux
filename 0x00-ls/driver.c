#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "hls.h"

/**
* main - entrypoint for the program
* @ac: number of commandline arguments
* @av: array of strings / commandline arguments
*
* Return: 0 on success, 2 on error
*/
int main(int ac, char **av)
{
	int *flags = NULL;
	int idx, multi, num_dirs = 0, num_regs = 0, *key = NULL, ecode = 0;

	key = malloc(sizeof(int) * ac);
	if (key == NULL)
		return (1);

	update_flags(&flags, NULL);
	ecode = key_parser(&key, &flags, &num_dirs, &num_regs, ac, av);

	multi = num_dirs + num_regs;
	if (multi < 1 && ecode == 0)
		print_dir("./", flags);

	for (idx = 0; idx < ac; idx++)
		if (key[idx] == 2)
		{
			if (flags[3])
				print_details(av[idx], NULL);
			else if (--num_regs <= 0 || flags[0])
				printf("%s\n", av[idx]);
			else
				printf("%s  ", av[idx]);
		}
	if (multi > 1 && multi != num_dirs)
		printf("\n");

	for (idx = 0; idx < ac; idx++)
		if (key[idx] == 1)
		{
			if (multi > 1 || (multi > 0 && ecode == 2))
				printf("%s:\n", av[idx]);
			print_dir(av[idx], flags);
			if (--num_dirs > 0)
				printf("\n");
		}
	free(key);
	free(flags);
	exit(ecode);
}

/**
* key_parser - handles flags and prints errors on invalid words
* @key: double pointer to key array to be updated by av words
* @flags: double pointer to flags array to be updated by flag words
* @dirs: pointer to num of directories to print
* @regs: pointer to num of non-directories to print
* @ac: argc from main
* @av: argv from main
*
* Return: error code value; 0 on success, else 2
*/
int key_parser(int **key, int **flags, int *dirs, int *regs, int ac, char **av)
{
	int idx, ecode = 0;
	struct stat stats;
	char *err_msg;

	(*key)[0] = 0;
	for (idx = 1; idx < ac; idx++)
	{
		(*key)[idx] = 0;
		if (av[idx][0] == '-')
			update_flags(flags, av[idx]);
		else
		{
			if (lstat(av[idx], &stats) == -1)
			{
				err_msg = "%s: cannot access %s: No such file or directory\n";
				fprintf(stderr, err_msg, av[0], av[idx]);
				ecode = 2;
			}
			else if (S_ISDIR(stats.st_mode))
			{
				if (S_IROTH & stats.st_mode)
				{
					(*key)[idx] = 1;
					(*dirs)++;
				}
				else
				{
					err_msg = "%s: cannot open directory %s: Permission denied\n";
					fprintf(stderr, err_msg, av[0], av[idx]);
					ecode = 2;
				}
			}
			else if (S_ISREG(stats.st_mode))
			{
				(*key)[idx] = 2;
				(*regs)++;
			}
		}
	}
	return (ecode);
}

/**
* update_flags - turns on flags depending on input
* @flags: double pointer to flags int array (size 8)
* @input: flags string to translate
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
