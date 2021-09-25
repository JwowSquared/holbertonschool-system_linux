#include "signals.h"

/**
* current_handler_sigaction - returns the current signal handler for SIGINT
*
* Return: pointer to handler, else NULL
*/
void (*current_handler_sigaction(void))(int)
{
	struct sigaction oact;

	if (sigaction(SIGINT, NULL, &oact) == -1)
		return (NULL);

	return (oact.sa_handler);
}
