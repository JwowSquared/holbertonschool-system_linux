#include "hbtn_elf.h"

/**
* flip32_Ehdr - calls flipEndian on all members of header. Almost identical to flip64_Ehdr -- see README
* @header: struct to flip
*/
void flip32_Ehdr(Elf32_Ehdr *header)
{
	header->e_type = flipEndian(header->e_type, 16);
	header->e_machine = flipEndian(header->e_machine, 16);
	header->e_version = flipEndian(header->e_version, 32);
	header->e_entry = flipEndian(header->e_entry, 32); /*64*/
	header->e_phoff = flipEndian(header->e_phoff, 32); /*64*/
	header->e_shoff = flipEndian(header->e_shoff, 32); /*64*/
	header->e_flags = flipEndian(header->e_flags, 32);
	header->e_ehsize = flipEndian(header->e_ehsize, 16);
	header->e_phentsize = flipEndian(header->e_phentsize, 16);
	header->e_phnum = flipEndian(header->e_phnum, 16);
	header->e_shentsize = flipEndian(header->e_shentsize, 16);
	header->e_shnum = flipEndian(header->e_shnum, 16);
	header->e_shstrndx = flipEndian(header->e_shstrndx, 16);
}

/**
* flip64_Ehdr - calls flipEndian on all members of header. Almost identical to flip32_Ehdr -- see README
* @header: struct to flip
*/
void flip64_Ehdr(Elf64_Ehdr *header)
{
	header->e_type = flipEndian(header->e_type, 16);
	header->e_machine = flipEndian(header->e_machine, 16);
	header->e_version = flipEndian(header->e_version, 32);
	header->e_entry = flipEndian(header->e_entry, 64); /*32*/
	header->e_phoff = flipEndian(header->e_phoff, 64); /*32*/
	header->e_shoff = flipEndian(header->e_shoff, 64); /*32*/
	header->e_flags = flipEndian(header->e_flags, 32);
	header->e_ehsize = flipEndian(header->e_ehsize, 16);
	header->e_phentsize = flipEndian(header->e_phentsize, 16);
	header->e_phnum = flipEndian(header->e_phnum, 16);
	header->e_shentsize = flipEndian(header->e_shentsize, 16);
	header->e_shnum = flipEndian(header->e_shnum, 16);
	header->e_shstrndx = flipEndian(header->e_shstrndx, 16);
}
