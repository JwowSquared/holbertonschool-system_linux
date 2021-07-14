#ifndef _HLS_H_
#define _HLS_H_

void update_flags(int **, char *);
void print_flags(int *);
void print_dir(char *, int *);
int key_parser(int **, int **, int *, int *, int, char **);
int hidden_check(char *, int *);
void print_details(char *, char *);
char *fix_path(char *, char *);

#endif /* _HLS_H_ */
