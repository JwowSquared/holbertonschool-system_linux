#include "hbtn_elf.h"

/**
* read_header - freads an ElfN_Ehdr from file
* @out: pointer to header to read into
* @file: open file pointer to ELF
* bits: either 32 or 64
*/
void read_header(header_t *out, FILE *file, int bits)
{
	Elf32_Ehdr h32;
	int i;

	if (bits == 32)
	{
		fread(&h32, sizeof(h32), 1, file);
		for (i = 0; i < EI_NIDENT; i++)
			out->e_ident[i] = h32.e_ident[i];
		out->e_type = h32.e_type;
		out->e_machine = h32.e_machine;
		out->e_version = h32.e_version;
		out->e_entry = h32.e_entry;
		out->e_phoff = h32.e_phoff;
		out->e_shoff = h32.e_shoff;
		out->e_flags = h32.e_flags;
		out->e_ehsize = h32.e_ehsize;
		out->e_phentsize = h32.e_phentsize;
		out->e_phnum = h32.e_phnum;
		out->e_shentsize = h32.e_shentsize;
		out->e_shnum = h32.e_shnum;
		out->e_shstrndx = h32.e_shstrndx;
	}
	else
		fread(out, sizeof(*out), 1, file);

	if (out->e_ident[EI_DATA] == ELFDATA2MSB)
		flip_header(out, bits);
}

/**
* read_section - freads an ElfN_Shdr from file
* @out: pointer to section to read into
* @header: reference to ELF header struct
* @file: open file pointer to ELF
* bits: either 32 or 64
*/
void read_section(section_t *out, header_t *header, FILE *file, int bits)
{
	Elf32_Shdr s32;

	if (bits == 32)
	{
		fread(&s32, sizeof(s32), 1, file);
		out->sh_name = s32.sh_name;
		out->sh_type = s32.sh_type;
		out->sh_flags = s32.sh_flags;
		out->sh_addr = s32.sh_addr;
		out->sh_offset = s32.sh_offset;
		out->sh_size = s32.sh_size;
		out->sh_link = s32.sh_link;
		out->sh_info = s32.sh_info;
		out->sh_addralign = s32.sh_addralign;
		out->sh_entsize = s32.sh_entsize;
	}
	else
		fread(out, sizeof(*out), 1, file);

	if (header->e_ident[EI_DATA] == ELFDATA2MSB)
		flip_section(out, bits);
}
