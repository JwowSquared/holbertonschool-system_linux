#include "hbtn_elf.h"
/**
* main - entry point for 1-hreadelf. Assumes av[1] is a valid ELF.
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
		printf("Usage: 1-hreadelf file_name\n");
		return (2);
	}

	file = fopen(av[1], "rb");
	if (file)
	{
		fread(&magic, sizeof(magic), 1, file);
		rewind(file);
		if (magic[EI_CLASS] == ELFCLASS32)
			print_sections(file, 32);
		else if (magic[EI_CLASS] == ELFCLASS64)
			print_sections(file, 64);
	}

	fclose(file);

	return (0);
}

/**
* print_sections - mimics readelf -W -S
* @file: open file pointer to ELF
* @bits: either 32 or 64
*/
void print_sections(FILE *file, int bits)
{
	header_t header;
	section_t section;
	char *names = NULL, *prompt, *p[3];
	int i;

	p[0] = bits == 32 ? "%08lx " : "%016lx ";
	p[1] = bits == 32 ? "Addr    " : "Address         ";
	p[2] = bits == 32 ? "" : ", l (large)";

	read_header(&header, file, bits);
	names = fetch_strtab(&header, file, bits);
	printf("There are %d section headers", header.e_shnum);
	printf(", starting at offset %#lx:\n", header.e_shoff);
	printf("\nSection Headers:\n");
	prompt = "  %-22s %-15s %s Off    Size   ES Flg Lk Inf Al\n";
	printf(prompt, "[Nr] Name", "Type", p[1]);
	fseek(file, header.e_shoff, SEEK_SET);
	for (i = 0; i < header.e_shnum; i++)
	{
		read_section(&section, &header, file, bits);
		printf("  [%2d] ", i);
		printf("%-17s ", names + section.sh_name);
		printf("%-15s ", fetch_sh_type(section.sh_type));
		printf(p[0], section.sh_addr);
		printf("%06lx ", section.sh_offset);
		printf("%06lx ", section.sh_size);
		printf("%02lx ", section.sh_entsize);
		print_sh_flags(section.sh_flags);
		printf("%2u ", section.sh_link);
		printf("%3u ", section.sh_info);
		printf("%2lu\n", section.sh_addralign);
	}
	printf("Key to Flags:\n");
	printf("  W (write), A (alloc), X (execute)");
	printf(", M (merge), S (strings)%s\n", p[2]);
	printf("  I (info), L (link order), G (group)");
	printf(", T (TLS), E (exclude), x (unknown)\n");
	printf("  O (extra OS processing required)");
	printf(" o (OS specific), p (processor specific)\n");
	free(names);
}
