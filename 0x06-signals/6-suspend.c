#include "signals.h"

/**
* main - entry point for suspend program
*
* Return: EXIT_SUCCESS
*/
int main(void)
{
	int sig;
	sigset_t sigs;
	struct sigaction act;

	sigemptyset(&sigs);
	sigaddset(&sigs, SIGINT);

	act.sa_handler = helper;

	if (sigaction(SIGINT, &act, NULL) == -1)
		return (EXIT_FAILURE);

	sigwait(&sigs, &sig);

	raise(sig);

	printf("Signal received\n");

	return (EXIT_SUCCESS);
}

/**
* helper - prescribed behavior to overwrite SIGINT with
* @n: numerical value of the signal caught, usually 2
*/
void helper(int n)
{
	printf("Caught %d\n", n);
	fflush(stdout);
}
