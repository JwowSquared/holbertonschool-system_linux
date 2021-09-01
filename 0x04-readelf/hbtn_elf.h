#ifndef _HBTN_ELF_
#define _HBTN_ELF_

#include <stdio.h>
#include <elf.h>

unsigned long int flipEndian(unsigned long int, int);

void print_elf_32(FILE *);
void print_elf_64(FILE *);

void flip32_0(Elf32_Ehdr *);
void flip64_0(Elf64_Ehdr *);

void print_section_32(FILE *);
void print_section_64(FILE *);

void flip32_1(Elf32_Shdr *);
void flip64_1(Elf64_Shdr *);

#endif /* _HBTN_ELF_*/
