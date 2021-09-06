#include "hbtn_elf.h"

/**
* fetch_sh_type - matches macro with string to display. Only includes enough to match given cases.
* @type: sh_type  member of an ElfN_Shdr
*
* Return: string to be displayed
*/
char *fetch_sh_type(unsigned int type)
{
	if (type == SHT_NULL)
		return ("NULL");
	if (type == SHT_PROGBITS)
		return ("PROGBITS");
	if (type == SHT_SYMTAB)
		return ("SYMTAB");
	if (type == SHT_STRTAB)
		return ("STRTAB");
	if (type == SHT_RELA)
		return ("RELA");
	if (type == SHT_HASH)
		return ("HASH");
	if (type == SHT_DYNAMIC)
		return ("DYNAMIC");
	if (type == SHT_NOTE)
		return ("NOTE");
	if (type == SHT_NOBITS)
		return ("NOBITS");
	if (type == SHT_REL)
		return ("REL");
	if (type == SHT_DYNSYM)
		return ("DYNSYM");
	if (type == SHT_GNU_HASH)
		return ("GNU_HASH");
	if (type == SHT_GNU_versym)
		return ("VERSYM");
	if (type == SHT_GNU_verneed)
		return ("VERNEED");
	if (type == SHT_INIT_ARRAY)
		return ("INIT_ARRAY");
	if (type == SHT_FINI_ARRAY)
		return ("FINI_ARRAY");
	if (type == 0x6ffffffc)
		return ("VERDEF");
	if (type == 0x6ffffff1)
		return ("LOOS+ffffff1");
	if (type == 0x6ffffff3)
		return ("LOOS+ffffff3");

	return ("UNIMPLEMENTED");
}

/**
* print_sh_flags - matches macro with flags to print. Only includes enough to match given cases.
* @raw: sh_flags member of an ElfN_Shdr
*/
void print_sh_flags(unsigned long int raw)
{
	int i = 2;
	char flags[3];

	if (raw & SHF_EXECINSTR)
		flags[i--] = 'X';
	if (raw & SHF_INFO_LINK)
		flags[i--] = 'I';
	if (raw & SHF_STRINGS)
		flags[i--] = 'S';
	if (raw & SHF_MERGE)
		flags[i--] = 'M';
	if (raw & SHF_ALLOC)
		flags[i--] = 'A';
	if (raw & SHF_WRITE)
		flags[i--] = 'W';
	if (raw & SHF_EXCLUDE)
		flags[i--] = 'E';
	while (i >= 0)
		flags[i--] = ' ';

	printf("%c%c%c ", flags[0], flags[1], flags[2]);
}

/**
* fetch_strtab - returns a malloc'd copy of the string table
* @header: ELF header
* @file: open file pointer
* @bits: either 32 or 64
*
* Return: pointer to malloc'd area
*/
char *fetch_strtab(header_t *header, FILE *file, int bits)
{
	char *out;
	section_t section;
	int sh_diff = sizeof(section) - (64 - bits) / 4 * 3;
	unsigned long int position;

	sh_diff = sizeof(section) - (64 - bits) / 4 * 3; /*subtracts 24 if bits is 32*/

	position = ftell(file);

	fseek(file, header->e_shoff + sh_diff * header->e_shstrndx, SEEK_SET);
	read_section(&section, header, file, bits);
	fseek(file, section.sh_offset, SEEK_SET);
	out = malloc(sizeof(char) * section.sh_size); /* malloc error unhandled */
	fread(out, section.sh_size, 1, file);

	fseek(file, position, SEEK_SET);
	return (out);
}
