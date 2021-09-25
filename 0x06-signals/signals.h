#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* helper functions */
void helper(int);

/* mandatory functions */
int handle_signal(void);

#endif /* _SIGNALS_H_ */
