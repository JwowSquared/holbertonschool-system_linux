#include "hbtn_elf.h"

/**
* print_interp - displays the path to the interpreter
* @program: reference to the interp program header
* @file: open file pointer
*/
void print_interp(program_t *program, FILE *file)
{
	char *interp;
	unsigned long int position;

	position = ftell(file);
	interp = malloc(sizeof(char) * program->p_filesz);
	fseek(file, program->p_offset, SEEK_SET);
	fread(interp, program->p_filesz, 1, file);
	printf("      [Requesting program interpreter: %s]\n", interp);
	fseek(file, position, SEEK_SET);
	free(interp);
}

/**
* print_p_flags - prints flags associated with macro.
* @raw: p_flags member of ElfN_Phdr
*/
void print_p_flags(unsigned long int raw)
{
	char flags[3] = {' ', ' ', ' '};

	if (raw & PF_R)
		flags[0] = 'R';
	if (raw & PF_W)
		flags[1] = 'W';
	if (raw & PF_X)
		flags[2] = 'E';

	printf("%c%c%c ", flags[0], flags[1], flags[2]);
}

/**
* fetch_p_type - return string associated with macro.
* @type: p_type member of ElfN_Phdr
*
* Return: string to display
*/
char *fetch_p_type(unsigned int type)
{
	if (type == PT_PHDR)
		return ("PHDR");
	if (type == PT_INTERP)
		return ("INTERP");
	if (type == PT_LOAD)
		return ("LOAD");
	if (type == PT_DYNAMIC)
		return ("DYNAMIC");
	if (type == PT_NOTE)
		return ("NOTE");
	if (type == PT_GNU_EH_FRAME)
		return ("GNU_EH_FRAME");
	if (type == PT_GNU_STACK)
		return ("GNU_STACK");
	if (type == PT_GNU_RELRO)
		return ("GNU_RELRO");

	return ("UNIMPLEMENTED");
}

/**
* display_p_prompt - prints the top prompt for 2-hreadelf
* @header: reference to ELF header
* @bits: either 32 or 64
*
* Return: -1 when e_phnum is 0, else 0
*/
int display_p_prompt(header_t *header, int bits)
{
	char *p[2];

	if (header->e_phnum == 0)
	{
		printf("\nThere are no program headers in this file.\n");
		return (-1);
	}

	p[0] = bits == 32 ? "%-11s%-11s" : "%-19s%-19s";
	p[1] = bits == 32 ? "%-8s%-8s" : "%-9s%-9s";

	printf("\nElf file type is %s\n", fetch_e_type(header->e_type));
	printf("Entry point %#lx\n", header->e_entry);
	printf("There are %u program headers, ", header->e_phnum);
	printf("starting at offset %lu\n", header->e_phoff);
	printf("\nProgram Headers:\n");

	printf("  Type           Offset   ");
	printf(p[0], "VirtAddr", "PhysAddr");
	printf(p[1], "FileSiz", "MemSiz");
	printf("Flg Align\n");

	return (0);
}
