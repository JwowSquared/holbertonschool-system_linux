#include "hbtn_elf.h"

void flip32_0(Elf32_Ehdr *header)
{
	printf("TEST type= %lu\n", sizeof(header->e_type));
	printf("TEST machine= %lu\n", sizeof(header->e_machine));
	printf("TEST version= %lu\n", sizeof(header->e_version));
	printf("TEST entry= %lu\n", sizeof(header->e_entry));
	printf("TEST phoff= %lu\n", sizeof(header->e_phoff));
	printf("TEST shoff= %lu\n", sizeof(header->e_shoff));
	printf("TEST flags= %lu\n", sizeof(header->e_flags));
	printf("TEST ehsize= %lu\n", sizeof(header->e_ehsize));
	printf("TEST phentsize= %lu\n", sizeof(header->e_phentsize));
	printf("TEST phnum= %lu\n", sizeof(header->e_phnum));
	printf("TEST shentsize= %lu\n", sizeof(header->e_shentsize));
	printf("TEST shnum= %lu\n", sizeof(header->e_shnum));
	printf("TEST shstrndx= %lu\n", sizeof(header->e_shstrndx));
}

void flip64_0(Elf64_Ehdr *header)
{
	printf("TEST short= %lu\n", sizeof(short));
	printf("TEST int= %lu\n", sizeof(int));
	printf("TEST long int= %lu\n", sizeof(long));

	printf("TEST type= %lu\n", sizeof(header->e_type));
	printf("TEST machine= %lu\n", sizeof(header->e_machine));
	printf("TEST version= %lu\n", sizeof(header->e_version));
	printf("TEST entry= %lu\n", sizeof(header->e_entry));
	printf("TEST phoff= %lu\n", sizeof(header->e_phoff));
	printf("TEST shoff= %lu\n", sizeof(header->e_shoff));
	printf("TEST flags= %lu\n", sizeof(header->e_flags));
	printf("TEST ehsize= %lu\n", sizeof(header->e_ehsize));
	printf("TEST phentsize= %lu\n", sizeof(header->e_phentsize));
	printf("TEST phnum= %lu\n", sizeof(header->e_phnum));
	printf("TEST shentsize= %lu\n", sizeof(header->e_shentsize));
	printf("TEST shnum= %lu\n", sizeof(header->e_shnum));
	printf("TEST shstrndx= %lu\n", sizeof(header->e_shstrndx));
}
