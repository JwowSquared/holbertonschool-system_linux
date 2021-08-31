#ifndef _HBTN_ELF_
#define _HBTN_ELF_

#include <stdio.h>
#include <elf.h>

void printElf_32(FILE *);
void printElf_64(FILE *);

void flip32_0(Elf32_Ehdr *header);
void flip64_0(Elf64_Ehdr *header);

#endif /* _HBTN_ELF_*/
