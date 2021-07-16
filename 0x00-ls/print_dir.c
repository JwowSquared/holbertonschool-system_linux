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
* print_details - used for the -l operation
* @fname: file name
* @parent: any additional path required for lstat
*/
void print_details(char *fname, char *parent)
{
	struct stat s;
	int perms, i = 0;
	char *path, *buf = NULL;
	ssize_t BUFLEN = 1024;

	if (parent != NULL)
		path = fix_path(parent, fname);
	else
		path = fname;

	lstat(path, &s);
	perms = s.st_mode;

	if (perms & 8192)
	{
		buf = malloc(sizeof(char) * BUFLEN);
		if (buf == NULL)
			return; /* memory error */

		while (i < BUFLEN)
			buf[i++] = '\0';
		readlink(path, buf, BUFLEN);
	}

	display_long(perms, &s, fname);

	if (buf != NULL)
	{
		printf(" -> %s", buf);
		free(buf);
	}
	printf("\n");

	if (parent != NULL)
		free(path);
}

/**
* display_long - displays the long format
* @perms: permission value
* @s: pointer to stat struct
* @fname: filename
*/
void display_long(int perms, struct stat *s, char *fname)
{
	char *date_string;
	struct passwd *usr;
	struct group *grp;

	print_perms(perms);
	printf(" %d", (int)s->st_nlink);

	usr = getpwuid(s->st_uid);
	grp = getgrgid(s->st_gid);
	if (usr != NULL)
		printf(" %s", usr->pw_name);
	else
		printf(" %d", (int)s->st_uid);
	if (grp != NULL)
		printf(" %s", grp->gr_name);
	else
		printf(" %d", (int)s->st_gid);
	printf(" %d", (int)s->st_size);

	date_string = ctime(&(s->st_mtime));
	printf(" %.12s %s", &(date_string[4]), fname);
}

/**
* print_perms - prints the rwx string
* @perms: st_mode value
*/
void print_perms(int perms)
{
	int max = 9;
	char *out = "rxw";

	if (perms & 16384)
		printf("d");
	else if (perms & 8192)
		printf("l");
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
