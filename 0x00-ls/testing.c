#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "hls.h"

/**
* this is for debugging, dont push this
*/
void print_flags(int *out)
{
	int idx = -1;

	printf("\nFlags info:\n");
	while (++idx < 8)
		printf("flag %d = %d\n", idx, out[idx]);
}
