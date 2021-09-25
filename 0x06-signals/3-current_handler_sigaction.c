#include "signals.h"

/**
* current_handler_sigaction - returns the current signal handler for SIGINT
*
* Return: pointer to handler, else NULL
*/
void (*current_handler_sigaction(void))(int)
{
	struct sigaction oact;

	sigaction(SIGINT, NULL, &oact);

	return (oact.sa_handler);
}
