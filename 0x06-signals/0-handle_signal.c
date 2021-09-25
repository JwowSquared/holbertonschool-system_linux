#include "signals.h"

/**
* handle_signal - overwrites SIGINT with helper
*
* Return: 0 on success, else -1
*/
int handle_signal(void)
{
	if (signal(SIGINT, helper) == SIG_ERR)
		return (-1);

	return (0);
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
