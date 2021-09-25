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
	if (ac != 2)
	{
		printf("Usage: %s <signum>\n", av[0]);
		exit(EXIT_FAILURE);
	}

	dup2(1, 2);

	psignal(atoi(av[1]), av[1]);
	exit(EXIT_SUCCESS);
}
