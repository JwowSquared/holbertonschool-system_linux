#include "hbtn_elf.h"

/**
* flip32_Shdr - calls flipEndian on all members of section. Almost identical to flip64_Shdr -- see README
* @header: struct to flip
*/
void flip32_Shdr(Elf32_Shdr *section)
{
	section->sh_name = flipEndian(section->sh_name, 32);
	section->sh_type = flipEndian(section->sh_type, 32);
	section->sh_flags = flipEndian(section->sh_flags, 32); /*64*/
	section->sh_addr = flipEndian(section->sh_addr, 32); /*64*/
	section->sh_offset = flipEndian(section->sh_offset, 32); /*64*/
	section->sh_size = flipEndian(section->sh_size, 32); /*64*/
	section->sh_link = flipEndian(section->sh_link, 32);
	section->sh_info = flipEndian(section->sh_info, 32);
	section->sh_addralign = flipEndian(section->sh_addralign, 32); /*64*/
	section->sh_entsize = flipEndian(section->sh_entsize, 32); /*64*/
}

/**
* flip64_Shdr - calls flipEndian on all members of section. Almost identical to flip32_Shdr -- see README
* @section: struct to flip
*/
void flip64_Shdr(Elf64_Shdr *section)
{
	section->sh_name = flipEndian(section->sh_name, 32);
	section->sh_type = flipEndian(section->sh_type, 32);
	section->sh_flags = flipEndian(section->sh_flags, 64); /*32*/
	section->sh_addr = flipEndian(section->sh_addr, 64); /*32*/
	section->sh_offset = flipEndian(section->sh_offset, 64); /*32*/
	section->sh_size = flipEndian(section->sh_size, 64); /*32*/
	section->sh_link = flipEndian(section->sh_link, 32);
	section->sh_info = flipEndian(section->sh_info, 32);
	section->sh_addralign = flipEndian(section->sh_addralign, 64); /*32*/
	section->sh_entsize = flipEndian(section->sh_entsize, 64); /*32*/
}
