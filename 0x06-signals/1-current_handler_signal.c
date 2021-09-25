#include "signals.h"

/**
* current_handler_signal - returns the current signal handler for SIGINT
*
* Return: pointer to handler, else NULL
*/
void (*current_handler_signal(void))(int)
{
	void (*out)(int);

	out = signal(SIGINT, SIG_DFL);
	signal(SIGINT, out);

	return (out);
}
