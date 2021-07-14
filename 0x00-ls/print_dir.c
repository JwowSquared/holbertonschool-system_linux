#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
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
			if (flags[3])
				print_details(current->d_name, path);
			else if (--num_out <= 0 || flags[0])
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

/**
* print_details - used for the -l operation
* @fname: file name
* @parent: any additional path required for lstat
*/
void print_details(char *fname, char *parent)
{
	struct stat s;
	int perms, max = 9;
	char *out = "rxw", *usr, *grp, *date_string, *path;

	if (parent != NULL)
		path = fix_path(parent, fname);
	else
		path = fname;

	lstat(path, &s);
	perms = s.st_mode;

	if (perms & 16384)
		printf("d");
	else
		printf("-");

	while (max > 0)
	{
		perms = perms << 1;
		if (perms & 512)
			printf("%c", out[max % 3]);
		else
			printf("-");
		max--;
	}

	usr = getpwuid(s.st_uid)->pw_name;
	grp = getgrgid(s.st_gid)->gr_name;
	printf(" %d %s %s %d ", (int)s.st_nlink, usr, grp, (int)s.st_size);
	date_string = ctime(&(s.st_mtime));
	printf("%.12s %s\n", &(date_string[4]), fname);

	if (parent != NULL)
		free(path);
}

/**
* fix_path - prepends parent to fname, split with /
* @parent: the absolute path minus the file name
* @fname: file name
*
* Return: pointer to full path, else NULL
*/
char *fix_path(char *parent, char *fname)
{
	int i = -1, j = -1, size = 0;
	char *out;

	while (parent[i + 1])
		i++;

	while (fname[j + 1])
		j++;

	size = 3 + i + j;
	if (parent[i] != '/')
		size++;

	out = malloc(sizeof(char) * size);
	if (out == NULL)
		return ("NULL");

	size = 0;
	while (parent[size])
	{
		out[size] = parent[size];
		size++;
	}

	if (parent[i] != '/')
		out[size++] = '/';

	i = 0;
	while (fname[i])
		out[size++] = fname[i++];
	out[size] = '\0';
	return (out);
}
