#include "signals.h"

/**
* main - entry point for describe program
* @ac: argc
* @av: argv
*
* Return: EXIT_FAILURE on improper usage, else 0
*/
int main(int ac, char **av)
{
	int i = 0;
	matcher_t m[] = {{"1", "Hangup"}, {"2", "Interrupt"}, {"3", "Quit"},
		{"4", "Illegal instruction"}, {"5", "Trace/breakpoint trap"},
		{"6", "Aborted"}, {"7", "Bus error"}, {"8", "Floating point exception"},
		{"9", "Killed"}, {"10", "User defined signal 1"}, {NULL, NULL}};

	if (ac != 2)
		printf("Usage: %s <signum>\n", av[0]), exit(EXIT_FAILURE);
	for (i = 0; m[i].code != NULL; i++)
		if (!strcmp(m[i].code, av[1]))
			printf("%s: %s\n", av[1], m[i].val), exit(0);
	printf("%s: Unknown signal %s\n", av[1], av[1]), exit(0);
}
