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
		rewind(file);
		if (magic[EI_CLASS] == ELFCLASS32)
			print32_Phdr(file);
		else if (magic[EI_CLASS] == ELFCLASS64)
			print64_Phdr(file);
	}

	fclose(file);

	return (0);
}

void print32_Phdr(FILE *file)
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

void print64_Phdr(FILE *file)
{
	Elf64_Ehdr header;
	Elf64_Phdr program;
	Elf64_Shdr section;
	int i, j;
	unsigned long int position, upper, lower;
	char *names;

	fread(&header, sizeof(header), 1, file);
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		flip64_Ehdr(&header);

	if (print_prompt_Phdr(header.e_type, header.e_entry, header.e_phnum, header.e_phoff) == -1)
		return;
	fseek(file, header.e_phoff, SEEK_SET);
	for (i = 0; i < header.e_phnum; i++)
	{
		fread(&program, sizeof(program), 1, file);
		if (header.e_ident[EI_DATA] == ELFDATA2MSB)
			flip64_Phdr(&program);
		printf("  %-14s ", fetch_p_type(program.p_type));
		printf("0x%06lx ", program.p_offset);
		printf("0x%016lx ", program.p_vaddr);
		printf("0x%016lx ", program.p_paddr);
		printf("0x%06lx ", program.p_filesz);
		printf("0x%06lx ", program.p_memsz);
		print_p_flags(program.p_flags);
	if (program.p_align > 0)
			printf("0x");
		printf("%lx\n", program.p_align);
		if (program.p_type == PT_INTERP)
			print_interp(file, program.p_offset, program.p_filesz);
	}


	names = fetch_strtab(file, header.e_shoff, header.e_shstrndx);

	printf("\n Section to Segment mapping:\n  Segment Sections...\n");
	fseek(file, header.e_phoff, SEEK_SET);
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
int print_prompt_Phdr()
{
	if (header.e_phnum == 0)
	{
		printf("\nThere are no program headers in this file.\n");
		return (-1);
	}

	printf("\nElf file type is %s\n", fetch_e_type(header.e_type));
	printf("Entry point 0x%x\n", )header.e_entry);
	printf("There are %u program headers, ", header.e_phnum);
	printf("starting at offset %lu\n", header.e_phoff);
	printf("\nProgram Headers:\n");
	printf("  Type           Offset   VirtAddr           PhysAddr           FileSiz  MemSiz   Flg Align\n");	
	return (0);
}

void print_p_flags(unsigned long int raw)
{
	char flags[3] = {' ', ' ', ' '};

	if (program.p_flags & PF_R)
		flags[0] = 'R';
	if (program.p_flags & PF_W)
		flags[1] = 'W';
	if (program.p_flags & PF_X)
		flags[2] = 'E';

	printf("%c%c%c ", flags[0], flags[1], flags[2]);
}

void print_interp(FILE *file, unsigned long int offset, unsigned long int size)
{
	char *interp;
	unsigned long int position;

	position = ftell(file);

	interp = malloc(sizeof(char) * size); /* malloc error unhandled */
	fseek(file, offset, SEEK_SET);
	fread(interp, size, 1, file);
	printf("      [Requesting program interpreter: %s]\n", interp);

	fseek(file, position, SEEK_SET);
	free(interp);
}


char *fetch_strtab32(FILE *file, Elf32_Ehdr *header)
{
	ELf32_Shdr section;
	unsigned long int position;

	position = ftell(file);

	fseek(file, header->e_shoff + sizeof(section) * header->e_shstrndx, SEEK_SET);
	fread(&section, sizeof(section), 1, file);
	if (header->e_ident[EI_DATA] == ELFDATA2MSB)
		flip32_Shdr(&section);
	fseek(file, section.sh_offset, SEEK_SET);
	names = malloc(sizeof(char) * section.sh_size); /* malloc error unhandled */
	fread(names, section.sh_size, 1, file);

	fseek(file, position, SEEK_SET);
	return (names);
}

char *fetch_strtab64(FILE *file, Elf64_Ehdr *header)
{
	ELf64_Shdr section;
	unsigned long int position;

	position = ftell(file);

	fseek(file, header->e_shoff + sizeof(section) * header->e_shstrndx, SEEK_SET);
	fread(&section, sizeof(section), 1, file);
	if (header->e_ident[EI_DATA] == ELFDATA2MSB)
		flip64_Shdr(&section);
	fseek(file, section.sh_offset, SEEK_SET);
	names = malloc(sizeof(char) * section.sh_size); /* malloc error unhandled */
	fread(names, section.sh_size, 1, file);

	fseek(file, position, SEEK_SET);
	return (names);
}

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
