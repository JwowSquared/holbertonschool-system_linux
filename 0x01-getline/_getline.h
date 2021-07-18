#ifndef _GETLINE_H_
#define _GETLINE_H_

#define READ_SIZE 16

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *_getline(const int fd);
int _strlen(char *);

#endif /* _GETLINE_H_ */
