#include "hbtn_elf.h"
#include <stdlib.h>

int main(int ac, char **av)
{
	FILE *file = NULL;
	unsigned char magic[EI_NIDENT];
	
	if (ac != 2)
	{
		printf("USAGE WRONG DUMBO\n");
		return (2);
	}

	file = fopen(av[1], "rb");
	if (file)
	{
		fread(&magic, sizeof(magic), 1, file);
		fseek(file, 0, SEEK_SET);
		if (magic[EI_CLASS] == ELFCLASS32)
			print_program_32(file);
		else if (magic[EI_CLASS] == ELFCLASS64)
			print_program_64(file);
	}

	fclose(file);

	return (0);
}

void print_program_32(FILE *file)
{
	Elf32_Ehdr header;
	Elf32_Phdr program;
	int i;
	char *temp;

	fread(&header, sizeof(header), 1, file);
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		flip32_0(&header);
	fseek(file, (unsigned int)header.e_phoff, SEEK_SET);

	for (i = 0; i < header.e_phnum; i++)
	{
		fread(&program, sizeof(program), 1, file);
		if (header.e_ident[EI_DATA] == ELFDATA2MSB)
			flip32_2(&program);
		if (program.p_type == PT_PHDR)
			printf("  PHDR           ");
		else if (program.p_type == PT_INTERP)
			printf("  INTERP         ");
		else if (program.p_type == PT_LOAD)
			printf("  LOAD           ");
		else if (program.p_type == PT_DYNAMIC)
			printf("  DYNAMIC        ");
		else if (program.p_type == PT_NOTE)
			printf("  NOTE           ");
		else if (program.p_type == PT_GNU_EH_FRAME)
			printf("  GNU_EH_FRAME   ");
		else if (program.p_type == PT_GNU_STACK)
			printf("  GNU_STACK      ");
		else if (program.p_type == PT_GNU_RELRO)
			printf("  GNU_RELRO      ");
		else
			printf("  UNKNOWN        ");
		printf("0x%06x ", (unsigned int)program.p_offset);
		printf("0x%08x ", (unsigned int)program.p_vaddr);
		printf("0x%08x ", (unsigned int)program.p_paddr);
		printf("0x%06x ", (unsigned int)program.p_filesz);
		printf("0x%06x ", (unsigned int)program.p_memsz);
		if (program.p_flags & PF_R)
			printf("R");
		else
			printf(" ");
		if (program.p_flags & PF_W)
			printf("W");
		else
			printf(" ");
		if (program.p_flags & PF_X)
			printf("E ");
		else
			printf("  ");
		printf("0x%x\n", (unsigned int)program.p_align);
		if (program.p_type == PT_INTERP)
		{
			temp = "THIS IS BROKEN";
			printf("      [Requesting program interpreter: %s]\n", temp);
		}
	}

}

void print_program_64(FILE *file)
{
	Elf64_Ehdr header;
	Elf64_Phdr program;
	int i;

	fread(&header, sizeof(header), 1, file);
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		flip64_0(&header);
	fseek(file, (unsigned int)header.e_phoff, SEEK_SET);

	printf("\nElf file type is ");
	if (header.e_type == ET_REL)
		printf("REL (Relocatable file)\n");
	else if (header.e_type == ET_EXEC)
		printf("EXEC (Executable file)\n"); /* confirmed */
	else if (header.e_type == ET_DYN)
		printf("DYN (Shared object file)\n");
	else if (header.e_type == ET_CORE)
		printf("A core file\n");
	else
		printf("UNKNOWN\n");

	printf("Entry point 0x%x\n", (unsigned int)header.e_entry);
	printf("There are %u program headers, ", header.e_phnum);
	printf("starting at offset %lu\n", header.e_phoff);
	printf("\nProgram Headers:\n");
	printf("  Type           Offset   VirtAddr           PhysAddr           FileSiz  MemSiz   Flg Align\n");
	for (i = 0; i < header.e_phnum; i++)
	{
		fread(&program, sizeof(program), 1, file);
		if (header.e_ident[EI_DATA] == ELFDATA2MSB)
			flip64_2(&program);
		if (program.p_type == PT_PHDR)
			printf("  PHDR           ");
		else if (program.p_type == PT_INTERP)
			printf("  INTERP         ");
		else if (program.p_type == PT_LOAD)
			printf("  LOAD           ");
		else if (program.p_type == PT_DYNAMIC)
			printf("  DYNAMIC        ");
		else if (program.p_type == PT_NOTE)
			printf("  NOTE           ");
		else if (program.p_type == PT_GNU_EH_FRAME)
			printf("  GNU_EH_FRAME   ");
		else if (program.p_type == PT_GNU_STACK)
			printf("  GNU_STACK      ");
		else if (program.p_type == PT_GNU_RELRO)
			printf("  GNU_RELRO      ");
		else
			printf("  UNKNOWN        ");
		printf("0x%06lx ", (unsigned long int)program.p_offset);
		printf("0x%016lx ", (unsigned long int)program.p_vaddr);
		printf("0x%016lx ", (unsigned long int)program.p_paddr);
		printf("0x%06lx ", (unsigned long int)program.p_filesz);
		printf("0x%06lx ", (unsigned long int)program.p_memsz);
		if (program.p_flags & PF_R)
			printf("R");
		else
			printf(" ");
		if (program.p_flags & PF_W)
			printf("W");
		else
			printf(" ");
		if (program.p_flags & PF_X)
			printf("E ");
		else
			printf("  ");
		printf("0x%lx\n", (unsigned long int)program.p_align);
		if (program.p_type == PT_INTERP)
			printf("      [Requesting program interpreter: %s]\n", (char *)program.p_vaddr);
	}

}
