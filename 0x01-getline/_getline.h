#ifndef _GETLINE_H_
#define _GETLINE_H_

#define READ_SIZE 1024

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *_getline(const int fd);
int _strlen(char *);
char *end_of_buffer(int, int, char **, int);
char *_strndup(char *, int);

#endif /* _GETLINE_H_ */
