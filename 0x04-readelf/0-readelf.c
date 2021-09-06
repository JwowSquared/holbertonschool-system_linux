#include "hbtn_elf.h"

/**
* main - entry point for 0-hreadelf. Assumes av[1] is a valid ELF.
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
		printf("Usage: 0-hreadelf file_name\n");
		return (2);
	}

	file = fopen(av[1], "rb");
	if (file)
	{
		fread(&magic, sizeof(magic), 1, file);
		rewind(file);
		if (magic[EI_CLASS] == ELFCLASS32)
			print_header(file, 32);
		else if (magic[EI_CLASS] == ELFCLASS64)
			print_header(file, 64);
	}

	fclose(file);

	return (0);
}

/**
* print_header - prints an ElfN_Ehdr.
* @file: open file pointer to ELF
* @bits: either 32 or 64
*/
void print_header(FILE *file, int bits)
{
	header_t header;
	int i;

	read_header(&header, file, bits);

	printf("ELF Header:\n");
	printf("  Magic:   ");
	for (i = 0; i < EI_NIDENT; i++)
		printf("%02x ", header.e_ident[i]);
	printf("\n");
	printf("  %-34s %s\n", "Class:", fetch_ei_class(header.e_ident[EI_CLASS]));
	printf("  %-34s %s\n", "Data:", fetch_ei_data(header.e_ident[EI_DATA]));
	printf("  %-34s %s\n", "Version:", "1 (current)"); /* e_ident[EI_VERSION] is always 1 */
	printf("  %-34s %s\n", "OS/ABI:", fetch_ei_osabi(header.e_ident[EI_OSABI]));
	printf("  %-34s %u\n", "ABI Version:", header.e_ident[EI_ABIVERSION]);
	printf("  %-34s %s\n", "Type:", fetch_e_type(header.e_type));
	printf("  %-34s %s\n", "Machine:", fetch_e_machine(header.e_machine));
	printf("  %-34s %s\n", "Version:", "0x1"); /* header.e_version is always 0x1 */
	printf("  %-34s %#lx\n", "Entry point address:", header.e_entry);
	printf("  %-34s %lu %s\n", "Start of program headers:", header.e_phoff, "(bytes into file)");
	printf("  %-34s %lu %s\n", "Start of section headers:", header.e_shoff, "(bytes into file)");
	printf("  %-34s %s\n", "Flags:", "0x0"); /* header.e_flags is always 0x0 */
	printf("  %-34s %u %s\n", "Size of this header:", header.e_ehsize, "(bytes)");
	printf("  %-34s %u %s\n", "Size of program headers:", header.e_phentsize, "(bytes)");
	printf("  %-34s %u\n", "Number of program headers:", header.e_phnum);
	printf("  %-34s %u %s\n", "Size of section headers:", header.e_shentsize, "(bytes)");
	printf("  %-34s %u\n", "Number of section headers:", header.e_shnum);
	printf("  %-34s %u\n", "Section header string table index:", header.e_shstrndx);
}
