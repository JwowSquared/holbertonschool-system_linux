#include "hbtn_elf.h"

void flip32_1(Elf32_Shdr *section)
{
	section->sh_name = (unsigned int)flipEndian(section->sh_name, 32);
	section->sh_type = (unsigned int)flipEndian(section->sh_type, 32);
	section->sh_flags = (unsigned int)flipEndian(section->sh_flags, 32);
	section->sh_addr = (unsigned int)flipEndian(section->sh_addr, 32);
	section->sh_offset = (unsigned int)flipEndian(section->sh_offset, 32);
	section->sh_size = (unsigned int)flipEndian(section->sh_size, 32);
	section->sh_link = (unsigned int)flipEndian(section->sh_link, 32);
	section->sh_info = (unsigned int)flipEndian(section->sh_info, 32);
	section->sh_addralign = (unsigned int)flipEndian(section->sh_addralign, 32);
	section->sh_entsize = (unsigned int)flipEndian(section->sh_entsize, 32);
}

void flip64_1(Elf64_Shdr *section)
{
	section->sh_name = (unsigned int)flipEndian(section->sh_name, 32);
	section->sh_type = (unsigned int)flipEndian(section->sh_type, 32);
	section->sh_flags = (unsigned long int)flipEndian(section->sh_flags, 64);
	section->sh_addr = (unsigned long int)flipEndian(section->sh_addr, 64);
	section->sh_offset = (unsigned long int)flipEndian(section->sh_offset, 64);
	section->sh_size = (unsigned long int)flipEndian(section->sh_size, 64);
	section->sh_link = (unsigned int)flipEndian(section->sh_link, 32);
	section->sh_info = (unsigned int)flipEndian(section->sh_info, 32);
	section->sh_addralign = (unsigned long int)flipEndian(section->sh_addralign, 64);
	section->sh_entsize = (unsigned long int)flipEndian(section->sh_entsize, 64);
}
