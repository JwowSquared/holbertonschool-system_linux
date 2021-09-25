#ifndef _SIGNALS_H_
#define _SIGNALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

/**
* struct macro_matcher_s - there HAS to be a better way than this
* @code: signal code
* @val: signal description
*/
typedef struct macro_matcher_s
{
	char *code;
	char *val;
} matcher_t;

/* helper functions */
void helper(int);

/* mandatory functions */
int handle_signal(void);
void (*current_handler_signal(void))(int);
int handle_sigaction(void);
void (*current_handler_sigaction(void))(int);
int trace_signal_sender(void);

#endif /* _SIGNALS_H_ */
