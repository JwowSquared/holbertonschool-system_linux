#include "signals.h"

/**
* trace_signal_sender - overwrites SIGQUIT with helper
*
* Return: 0 on success, else -1
*/
int trace_signal_sender(void)
{
	struct sigaction act;

	act.sa_handler = helper;

	if (sigaction(SIGQUIT, &act, NULL) == -1)
		return (-1);

	return (0);
}

/**
* helper - prescribed behavior to overwrite SIGQUIT with
* @n: PID of process that sent the signal?
*/
void helper(int n)
{
	(void)n;

	printf("SIGQUIT sent by %d\n", getpid());
	fflush(stdout);
}
