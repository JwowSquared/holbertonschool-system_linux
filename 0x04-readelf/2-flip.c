#include "hbtn_elf.h"

void flip32_2(Elf32_Phdr *program)
{
	program->p_type = (unsigned int)flipEndian(program->p_type, 32);
	program->p_offset = (unsigned int)flipEndian(program->p_offset, 32);
	program->p_vaddr = (unsigned int)flipEndian(program->p_vaddr, 32);
	program->p_paddr = (unsigned int)flipEndian(program->p_paddr, 32);
	program->p_filesz = (unsigned int)flipEndian(program->p_filesz, 32);
	program->p_memsz = (unsigned int)flipEndian(program->p_memsz, 32);
	program->p_flags = (unsigned int)flipEndian(program->p_flags, 32);
	program->p_align = (unsigned int)flipEndian(program->p_align, 32);
}

void flip64_2(Elf64_Phdr *program)
{
	program->p_type = (unsigned int)flipEndian(program->p_type, 32);
	program->p_flags = (unsigned int)flipEndian(program->p_flags, 32);
	program->p_offset = (unsigned long int)flipEndian(program->p_offset, 64);
	program->p_vaddr = (unsigned long int)flipEndian(program->p_vaddr, 64);
	program->p_paddr = (unsigned long int)flipEndian(program->p_paddr, 64);
	program->p_filesz = (unsigned long int)flipEndian(program->p_filesz, 64);
	program->p_memsz = (unsigned long int)flipEndian(program->p_memsz, 64);
	program->p_align = (unsigned long int)flipEndian(program->p_align, 64);
}
