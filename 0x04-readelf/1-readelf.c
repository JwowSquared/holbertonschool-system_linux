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
			print_section_32(file);
		else if (magic[EI_CLASS] == ELFCLASS64)
			print_section_64(file);
	}

	fclose(file);

	return (0);
}

void print_section_32(FILE *file)
{
	Elf32_Ehdr header;
	Elf32_Shdr section;

	fread(&header, sizeof(header), 1, file);
	fseek(file, (unsigned int)header.e_shoff, SEEK_SET);
	fread(&section, sizeof(section), 1, file);

	printf("TEST name = %u\n", (unsigned int)section.sh_name);
	printf("TEST type = %u\n", (unsigned int)section.sh_type);
	printf("TEST flags = %u\n", (unsigned int)section.sh_flags);
	printf("TEST addr = %u\n", (unsigned int)section.sh_addr);
	printf("TEST offset = %u\n", (unsigned int)section.sh_offset);
	printf("TEST size = %u\n", (unsigned int)section.sh_size);
	printf("TEST link = %u\n", (unsigned int)section.sh_link);
	printf("TEST info = %u\n", (unsigned int)section.sh_info);
	printf("TEST addralign = %u\n", (unsigned int)section.sh_addralign);
	printf("TEST entsize = %u\n", (unsigned int)section.sh_entsize);
}

void print_section_64(FILE *file)
{
	Elf64_Ehdr header;
	Elf64_Shdr str_table;
	Elf64_Shdr section;
	char *names = NULL, f_left, f_right, *cur = NULL;
	int i;

	fread(&header, sizeof(header), 1, file);
	fseek(file, (unsigned int)header.e_shoff + sizeof(section) * (unsigned int)header.e_shstrndx, SEEK_SET);
	fread(&str_table, sizeof(str_table), 1, file);
	fseek(file, (unsigned int)str_table.sh_offset, SEEK_SET);
	names = malloc(sizeof(char) * str_table.sh_size); /* malloc error unhandled */
	fread(names, str_table.sh_size, 1, file);
	fseek(file, header.e_shoff, SEEK_SET);

	printf("There are %d section headers, starting at offset 0x%04x:\n", header.e_shnum, (unsigned int)header.e_shoff);
	printf("\nSection Headers:\n");
	printf("  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al\n");
	for (i = 0; i < header.e_shnum; i++)
	{
		fread(&section, sizeof(section), 1, file);
		printf("  [%2d] ", i);
		printf("%-17s ", names + section.sh_name);
		if (section.sh_type == SHT_NULL)
			printf("NULL            ");
		else if (section.sh_type == SHT_PROGBITS)
			printf("PROGBITS        ");
		else if (section.sh_type == SHT_SYMTAB)
			printf("SYMTAB          ");
		else if (section.sh_type == SHT_STRTAB)
			printf("STRTAB          ");
		else if (section.sh_type == SHT_RELA)
			printf("RELA            ");
		else if (section.sh_type == SHT_HASH)
			printf("HASH            ");
		else if (section.sh_type == SHT_DYNAMIC)
			printf("DYNAMIC         ");
		else if (section.sh_type == SHT_NOTE)
			printf("NOTE            ");
		else if (section.sh_type == SHT_NOBITS)
			printf("NOBITS          ");
		else if (section.sh_type == SHT_REL)
			printf("REL             ");
		else if (section.sh_type == SHT_SHLIB)
			printf("SHLIB           ");
		else if (section.sh_type == SHT_DYNSYM)
			printf("DYNSYM          ");
		else if (section.sh_type == SHT_GNU_HASH)
			printf("GNU_HASH        ");
		else if (section.sh_type == SHT_GNU_versym)
			printf("VERSYM          ");
		else if (section.sh_type == SHT_GNU_verneed)
			printf("VERNEED         ");
		else if (section.sh_type == SHT_INIT_ARRAY)
			printf("INIT_ARRAY      ");
		else if (section.sh_type == SHT_FINI_ARRAY)
			printf("FINI_ARRAY      ");
		else
			printf("UNKNOWN         ");

		printf("%016lx ", (unsigned long int)section.sh_addr);
		printf("%06lx ", (unsigned long int)section.sh_offset);
		printf("%06x ", (unsigned int)section.sh_size);
		printf("%02x ", (unsigned int)section.sh_entsize);
		cur = &f_right;
		f_left = ' ';
		f_right = ' ';
		if (section.sh_flags & SHF_ALLOC)
		{
			*cur = 'A';
			cur = &f_left;
		}
		if (section.sh_flags & SHF_WRITE)
		{
			*cur = 'W';
			cur = &f_left;
		}
		if (section.sh_flags & SHF_EXECINSTR)
		{
			*cur = 'X';
			cur = &f_left;
		}
		if (section.sh_flags & SHF_MERGE)
		{
			*cur = 'M';
			cur = &f_left;
		}
		if (section.sh_flags & SHF_STRINGS)
		{
			*cur = 'S';
			cur = &f_left;
		}
		printf("%c%c ", f_left, f_right);
		printf("%2u ", (unsigned int)section.sh_link);
		printf("%3u ", (unsigned int)section.sh_info);
		printf("%2u\n", (unsigned int)section.sh_addralign);
	}

printf("Key to Flags:\n");
printf("  W (write), A (alloc), X (execute), M (merge), S (strings), l (large)\n");
printf("  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)\n");
printf("  O (extra OS processing required) o (OS specific), p (processor specific)\n");

	free(names);
}
