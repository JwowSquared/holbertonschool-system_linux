#ifndef _HBTN_ELF_
#define _HBTN_ELF_

#include <stdio.h>
#include <elf.h>

void printElf_32(FILE *);
void printElf_64(FILE *);

unsigned long int flipEndian(unsigned long int, int);
void flip32_0(Elf32_Ehdr *);
void flip64_0(Elf64_Ehdr *);

#endif /* _HBTN_ELF_*/
