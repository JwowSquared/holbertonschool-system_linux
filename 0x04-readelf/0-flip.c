#include "hbtn_elf.h"

void flip32_0(Elf32_Ehdr *header)
{
	header->e_type = (unsigned short)flipEndian(header->e_type, 16);
	header->e_machine = (unsigned short)flipEndian(header->e_machine, 16);
	header->e_version = (unsigned int)flipEndian(header->e_version, 32);
	header->e_entry = (unsigned int)flipEndian(header->e_entry, 32);
	header->e_phoff = (unsigned int)flipEndian(header->e_phoff, 32);
	header->e_shoff = (unsigned int)flipEndian(header->e_shoff, 32);
	header->e_flags = (unsigned int)flipEndian(header->e_flags, 32);
	header->e_ehsize = (unsigned short)flipEndian(header->e_ehsize, 16);
	header->e_phentsize = (unsigned short)flipEndian(header->e_phentsize, 16);
	header->e_phnum = (unsigned short)flipEndian(header->e_phnum, 16);
	header->e_shentsize = (unsigned short)flipEndian(header->e_shentsize, 16);
	header->e_shnum = (unsigned short)flipEndian(header->e_shnum, 16);
	header->e_shstrndx = (unsigned short)flipEndian(header->e_shstrndx, 16);
}

void flip64_0(Elf64_Ehdr *header)
{
	header->e_type = (unsigned short)flipEndian(header->e_type, 16);
	header->e_machine = (unsigned short)flipEndian(header->e_machine, 16);
	header->e_version = (unsigned int)flipEndian(header->e_version, 32);
	header->e_entry = (unsigned long int)flipEndian(header->e_entry, 64);
	header->e_phoff = (unsigned long int)flipEndian(header->e_phoff, 64);
	header->e_shoff = (unsigned long int)flipEndian(header->e_shoff, 64);
	header->e_flags = (unsigned int)flipEndian(header->e_flags, 32);
	header->e_ehsize = (unsigned short)flipEndian(header->e_ehsize, 16);
	header->e_phentsize = (unsigned short)flipEndian(header->e_phentsize, 16);
	header->e_phnum = (unsigned short)flipEndian(header->e_phnum, 16);
	header->e_shentsize = (unsigned short)flipEndian(header->e_shentsize, 16);
	header->e_shnum = (unsigned short)flipEndian(header->e_shnum, 16);
	header->e_shstrndx = (unsigned short)flipEndian(header->e_shstrndx, 16);
}
