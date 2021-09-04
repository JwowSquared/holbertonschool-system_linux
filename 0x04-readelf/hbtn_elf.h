#ifndef _HBTN_ELF_
#define _HBTN_ELF_

#include <stdio.h>
#include <stdlib.h>
#include <elf.h>

unsigned long int flipEndian(unsigned long int, int);

void print32_Ehdr(FILE *);
void print64_Ehdr(FILE *);
void flip32_Ehdr(Elf32_Ehdr *);
void flip64_Ehdr(Elf64_Ehdr *);

char *fetch_ei_data(unsigned int);
char *fetch_ei_osabi(unsigned int);
char *fetch_e_type(unsigned int);
char *fetch_e_machine(unsigned int);

void print32_Shdr(FILE *);
void print64_Shdr(FILE *);
void flip32_Shdr(Elf32_Shdr *);
void flip64_Shdr(Elf64_Shdr *);

char *fetch_sh_type(unsigned int);
void print_sh_flags(unsigned long int);

void print32_Phdr(FILE *);
void print64_Phdr(FILE *);
void flip32_Phdr(Elf32_Phdr *);
void flip64_Phdr(Elf64_Phdr *);

#endif /* _HBTN_ELF_*/
