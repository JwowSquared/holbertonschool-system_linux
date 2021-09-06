#include "hbtn_elf.h"

/**
* main - entry point for 2-hreadelf
* @ac: argc
* @av: argv
*
* Return: Always 0 -- no error handling required by project
*/
int main(int ac, char **av)
{
	FILE *file = NULL;
	unsigned char magic[EI_NIDENT];

	if (ac != 2)
	{
		printf("Usage: 2-hreadelf file_name\n");
		return (2);
	}

	file = fopen(av[1], "rb");
	if (file)
	{
		fread(&magic, sizeof(magic), 1, file);
		rewind(file);
		if (magic[EI_CLASS] == ELFCLASS32)
			print_programs(file, 32);
		else if (magic[EI_CLASS] == ELFCLASS64)
			print_programs(file, 64);
	}

	fclose(file);

	return (0);
}

/**
* print_programs - mimics readelf -W -l
* @file: open file pointer
* @bits: either 32 or 64
*/
void print_programs(FILE *file, int bits)
{
	header_t header;
	program_t program;
	int i;
	char *p[2];

	p[0] = bits == 32 ? "0x%08lx " : "0x%016lx ";
	p[1] = bits == 32 ? "0x%05lx " : "0x%06lx ";
	read_header(&header, file, bits);
	if (display_p_prompt(&header, bits) == -1)
		return;
	fseek(file, header.e_phoff, SEEK_SET);
	for (i = 0; i < header.e_phnum; i++)
	{
		read_program(&program, &header, file, bits);
		printf("  %-15s", fetch_p_type(program.p_type));
		printf("0x%06lx ", program.p_offset);
		printf(p[0], program.p_vaddr);
		printf(p[0], program.p_paddr);
		printf(p[1], program.p_filesz);
		printf(p[1], program.p_memsz);
		print_p_flags(program.p_flags);
		printf("%#lx\n", program.p_align);
		if (program.p_type == PT_INTERP)
			print_interp(&program, file);
	}

	display_map(&header, file, bits);
}

/**
* display_map - prints the section segment map
* @header: reference to ELF header
* @file: open file pointer
* @bits: either 32 or 64
*/
void display_map(header_t *header, FILE *file, int bits)
{
	section_t section;
	program_t program;
	int i, j;
	unsigned long int position, high, low;
	char *names;

	names = fetch_strtab(header, file, bits);

	printf("\n Section to Segment mapping:\n  Segment Sections...\n");
	fseek(file, header->e_phoff, SEEK_SET);
	for (i = 0; i < header->e_phnum; i++)
	{
		read_program(&program, header, file, bits);
		position = ftell(file);
		fseek(file, header->e_shoff, SEEK_SET);
		printf("   %02d     ", i);
		for (j = 0; j < header->e_shnum; j++)
		{
			read_section(&section, header, file, bits);
			if (section.sh_addr == 0 || section.sh_size == 0)
				continue;
			low = section.sh_offset;
			high = section.sh_offset + section.sh_size;
			if (low >= program.p_offset && high <= program.p_offset + program.p_memsz)
				printf("%s ", names + section.sh_name);
		}
		printf("\n");
		fseek(file, position, SEEK_SET);
	}
	free(names);
}
