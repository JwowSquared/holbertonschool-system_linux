#include "hbtn_elf.h"

/**
* flip_endian - reverses a number but bytes stay together
* @num: number to flip
* @size: size in bits of num
*
* Return: flipped value
*/
unsigned long int flip_endian(unsigned long int num, int size)
{
	unsigned long int left, right;

	if (size == 8)
		return (num);

	right = num & ((1 << (size / 2)) - 1);
	left = num >> (size / 2);

	right = flip_endian(right, size / 2);
	left = flip_endian(left, size / 2);

	return (left | (right << (size / 2)));
}

/**
* flip_header - calls flipEndian on all members of header.
* @header: struct to flip
* @bits: either 32 or 64
*/
void flip_header(header_t *header, int bits)
{
	header->e_type = flip_endian(header->e_type, 16);
	header->e_machine = flip_endian(header->e_machine, 16);
	header->e_version = flip_endian(header->e_version, 32);
	header->e_entry = flip_endian(header->e_entry, bits);
	header->e_phoff = flip_endian(header->e_phoff, bits);
	header->e_shoff = flip_endian(header->e_shoff, bits);
	header->e_flags = flip_endian(header->e_flags, 32);
	header->e_ehsize = flip_endian(header->e_ehsize, 16);
	header->e_phentsize = flip_endian(header->e_phentsize, 16);
	header->e_phnum = flip_endian(header->e_phnum, 16);
	header->e_shentsize = flip_endian(header->e_shentsize, 16);
	header->e_shnum = flip_endian(header->e_shnum, 16);
	header->e_shstrndx = flip_endian(header->e_shstrndx, 16);
}

/**
* flip_section - calls flipEndian on all members of section.
* @section: struct to flip
* @bits: either 32 or 64
*/
void flip_section(section_t *section, int bits)
{
	section->sh_name = flip_endian(section->sh_name, 32);
	section->sh_type = flip_endian(section->sh_type, 32);
	section->sh_flags = flip_endian(section->sh_flags, bits);
	section->sh_addr = flip_endian(section->sh_addr, bits);
	section->sh_offset = flip_endian(section->sh_offset, bits);
	section->sh_size = flip_endian(section->sh_size, bits);
	section->sh_link = flip_endian(section->sh_link, 32);
	section->sh_info = flip_endian(section->sh_info, 32);
	section->sh_addralign = flip_endian(section->sh_addralign, bits);
	section->sh_entsize = flip_endian(section->sh_entsize, bits);
}

/**
* flip_program - calls flipEndian on all members of program.
* @program: struct to flip
* @bits: either 32 or 64
*/
void flip_program(program_t *program, int bits)
{
	program->p_type = flip_endian(program->p_type, 32);
	program->p_flags = flip_endian(program->p_flags, 32);
	program->p_offset = flip_endian(program->p_offset, bits);
	program->p_vaddr = flip_endian(program->p_vaddr, bits);
	program->p_paddr = flip_endian(program->p_paddr, bits);
	program->p_filesz = flip_endian(program->p_filesz, bits);
	program->p_memsz = flip_endian(program->p_memsz, bits);
	program->p_align = flip_endian(program->p_align, bits);
}
