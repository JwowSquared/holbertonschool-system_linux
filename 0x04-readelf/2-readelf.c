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
	Elf32_Shdr section;
	Elf32_Shdr str_table;
	int i, j;
	unsigned long int position, upper, lower;
	char *names, *interp;

	(void)names;
	fread(&header, sizeof(header), 1, file);
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		flip32_0(&header);
	fseek(file, (unsigned int)header.e_phoff, SEEK_SET);

	if (header.e_phnum == 0)
	{
		printf("\nThere are no program headers in this file.\n");
		return;
	}

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
	printf("starting at offset %u\n", header.e_phoff);
	printf("\nProgram Headers:\n");
	printf("  Type           Offset   VirtAddr   PhysAddr   FileSiz MemSiz  Flg Align\n");
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
		else if (program.p_type == 0x6464e550)
			printf("  LOOS+464e550   ");
		else
			printf("  UNKNOWN        ");
		printf("0x%06x ", (unsigned int)program.p_offset);
		printf("0x%08x ", (unsigned int)program.p_vaddr);
		printf("0x%08x ", (unsigned int)program.p_paddr);
		printf("0x%05x ", (unsigned int)program.p_filesz);
		printf("0x%05x ", (unsigned int)program.p_memsz);
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
		if (program.p_align > 0)
			printf("0x");
		printf("%x\n", (unsigned int)program.p_align);
		if (program.p_type == PT_INTERP)
		{
			position = ftell(file);
			interp = malloc(sizeof(char) * program.p_filesz); /* malloc error unhandled */
			fseek(file, (unsigned int)program.p_offset, SEEK_SET);
			fread(interp, program.p_filesz, 1, file);
			printf("      [Requesting program interpreter: %s]\n", interp);
			fseek(file, position, SEEK_SET);
			free(interp);
		}
	}

	fseek(file, (unsigned int)header.e_shoff + sizeof(section) * (unsigned int)header.e_shstrndx, SEEK_SET);
	fread(&str_table, sizeof(str_table), 1, file);
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		flip32_1(&str_table);
	fseek(file, (unsigned int)str_table.sh_offset, SEEK_SET);
	names = malloc(sizeof(char) * str_table.sh_size); /* malloc error unhandled */
	fread(names, str_table.sh_size, 1, file);
	fseek(file, header.e_phoff, SEEK_SET);

	printf("\n Section to Segment mapping:\n  Segment Sections...\n");
	for (i = 0; i < header.e_phnum; i++)
	{
		fread(&program, sizeof(program), 1, file);
		if (header.e_ident[EI_DATA] == ELFDATA2MSB)
			flip32_2(&program);
		position = ftell(file);
		fseek(file, header.e_shoff, SEEK_SET);
		printf("   %02d     ", i);
		for (j = 0; j < header.e_shnum; j++)
		{
			fread(&section, sizeof(section), 1, file);
			if (header.e_ident[EI_DATA] == ELFDATA2MSB)
				flip32_1(&section);
			if (section.sh_addr == 0 || section.sh_size == 0)
				continue;
			lower = section.sh_offset;
			upper = section.sh_offset + section.sh_size;
			if (lower >= program.p_offset && upper <= program.p_offset + program.p_memsz)
				printf("%s ", names + section.sh_name);
		}
		printf("\n");
		fseek(file, position, SEEK_SET);
	}

	free(names);
}

void print_program_64(FILE *file)
{
	Elf64_Ehdr header;
	Elf64_Phdr program;
	Elf64_Shdr section;
	Elf64_Shdr str_table;
	int i, j;
	unsigned long int position, upper, lower;
	char *names, *interp;

	fread(&header, sizeof(header), 1, file);
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		flip64_0(&header);
	fseek(file, (unsigned int)header.e_phoff, SEEK_SET);

	if (header.e_phnum == 0)
	{
		printf("\nThere are no program headers in this file.\n");
		return;
	}

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
		if (program.p_align > 0)
			printf("0x");
		printf("%lx\n", (unsigned long int)program.p_align);
		if (program.p_type == PT_INTERP)
		{
			position = ftell(file);
			interp = malloc(sizeof(char) * program.p_filesz); /* malloc error unhandled */
			fseek(file, (unsigned long int)program.p_offset, SEEK_SET);
			fread(interp, program.p_filesz, 1, file);
			printf("      [Requesting program interpreter: %s]\n", interp);
			fseek(file, position, SEEK_SET);
			free(interp);
		}

	}

	fseek(file, (unsigned int)header.e_shoff + sizeof(section) * (unsigned int)header.e_shstrndx, SEEK_SET);
	fread(&str_table, sizeof(str_table), 1, file);
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		flip64_1(&str_table);
	fseek(file, (unsigned long int)str_table.sh_offset, SEEK_SET);
	names = malloc(sizeof(char) * str_table.sh_size); /* malloc error unhandled */
	fread(names, str_table.sh_size, 1, file);
	fseek(file, header.e_phoff, SEEK_SET);

	printf("\n Section to Segment mapping:\n  Segment Sections...\n");
	for (i = 0; i < header.e_phnum; i++)
	{
		fread(&program, sizeof(program), 1, file);
		if (header.e_ident[EI_DATA] == ELFDATA2MSB)
			flip64_2(&program);
		position = ftell(file);
		fseek(file, header.e_shoff, SEEK_SET);
		printf("   %02d     ", i);
		for (j = 0; j < header.e_shnum; j++)
		{
			fread(&section, sizeof(section), 1, file);
			if (header.e_ident[EI_DATA] == ELFDATA2MSB)
				flip64_1(&section);
			if (section.sh_addr == 0 || section.sh_size == 0)
				continue;
			lower = section.sh_offset;
			upper = section.sh_offset + section.sh_size;
			if (lower >= program.p_offset && upper <= program.p_offset + program.p_memsz)
				printf("%s ", names + section.sh_name);
		}
		printf("\n");
		fseek(file, position, SEEK_SET);
	}

	free(names);
}
