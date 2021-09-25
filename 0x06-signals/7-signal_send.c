#include "signals.h"

/**
* main - entry point for signal_send program
* @ac: argc
* @av: argv
*
* Return: EXIT_FAILURE on improper usage or kill fail, else EXIT_SUCCESS
*/
int main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Usage: %s <pid>\n", av[0]);
		exit(EXIT_FAILURE);
	}

	if (kill(atoi(av[1]), SIGINT) == -1)
		return (EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
