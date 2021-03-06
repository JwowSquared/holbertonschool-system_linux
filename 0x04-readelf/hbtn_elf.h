#ifndef _HBTN_ELF_
#define _HBTN_ELF_

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

typedef Elf64_Ehdr header_t;
typedef Elf64_Shdr section_t;
typedef Elf64_Phdr program_t;

unsigned long int flipEndian(unsigned long int, int);
void flip_header(header_t *, int);
void flip_section(section_t *, int);
void flip_program(program_t *, int);

void print_header(FILE *, int);
void read_header(header_t *, FILE *, int);

char *fetch_ei_class(unsigned int);
char *fetch_ei_data(unsigned int);
char *fetch_ei_osabi(unsigned int);
char *fetch_e_type(unsigned int);
char *fetch_e_machine(unsigned int);

void print_sections(FILE *, int);
void read_section(section_t *, header_t *, FILE *, int);

char *fetch_strtab(header_t *, FILE *, int);
char *fetch_sh_type(unsigned int);
void print_sh_flags(unsigned long int);

void print_programs(FILE *, int);
void read_program(program_t *, header_t *, FILE *, int);

void display_map(header_t *, FILE *, int);
int display_p_prompt(header_t *, int);
char *fetch_p_type(unsigned int);
void print_p_flags(unsigned long int);
void print_interp(program_t *, FILE *);

#endif /* _HBTN_ELF_*/
