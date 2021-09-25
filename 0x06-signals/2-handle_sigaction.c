#include "signals.h"

/**
* handle_sigaction - overwrites SIGINT using sigaction
*
* Return: 0 on success, else -1
*/
int handle_sigaction(void)
{
	struct sigaction act;

	act.sa_handler = helper;

	return (sigaction(SIGINT, &act, NULL));
}

/**
* helper - prescribed behavior to overwrite SIGINT with
* @n: numerical value of the signal caught, usually 2
*/
void helper(int n)
{
	printf("Gotcha! [%d]\n", n);
	fflush(stdout);
}
