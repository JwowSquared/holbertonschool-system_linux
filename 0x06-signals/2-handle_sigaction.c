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
