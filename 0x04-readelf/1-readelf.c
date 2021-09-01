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
	Elf32_Shdr str_table;
	Elf32_Shdr section;
	char *names = NULL, flags[3];
	int i, j;

	fread(&header, sizeof(header), 1, file);
	fseek(file, (unsigned int)header.e_shoff + sizeof(section) * (unsigned int)header.e_shstrndx, SEEK_SET);
	fread(&str_table, sizeof(str_table), 1, file);
	fseek(file, (unsigned int)str_table.sh_offset, SEEK_SET);
	names = malloc(sizeof(char) * str_table.sh_size); /* malloc error unhandled */
	fread(names, str_table.sh_size, 1, file);
	fseek(file, header.e_shoff, SEEK_SET);

	printf("There are %d section headers, starting at offset 0x%x:\n", header.e_shnum, (unsigned int)header.e_shoff);
	printf("\nSection Headers:\n");
	printf("  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n");
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
		else if (section.sh_type == SHT_GNU_verdef)
			printf("VERDEF          ");
		else if (section.sh_type == LOOS_1)
			printf("LOOS+ffffff1    ");
		else if (section.sh_type == LOOS_3)
			printf("LOOS+ffffff3    ");
		else
			printf("UNKNOWN         ");

		printf("%08x ", (unsigned int)section.sh_addr);
		printf("%06x ", (unsigned int)section.sh_offset);
		printf("%06x ", (unsigned int)section.sh_size);
		printf("%02x ", (unsigned int)section.sh_entsize);
		for (j = 0; j < 3; j++)
			flags[j] = ' ';
		j = 2;
		if (section.sh_flags & SHF_EXECINSTR)
			flags[j--] = 'X';
		if (section.sh_flags & SHF_INFO_LINK)
			flags[j--] = 'I';
		if (section.sh_flags & SHF_STRINGS)
			flags[j--] = 'S';
		if (section.sh_flags & SHF_MERGE)
			flags[j--] = 'M';
		if (section.sh_flags & SHF_ALLOC)
			flags[j--] = 'A';
		if (section.sh_flags & SHF_WRITE)
			flags[j--] = 'W';
		if (section.sh_flags & SHF_EXCLUDE)
			flags[j--] = 'E';
		printf("%c%c%c ", flags[0], flags[1], flags[2]);
		printf("%2u ", (unsigned int)section.sh_link);
		printf("%3u ", (unsigned int)section.sh_info);
		printf("%2u\n", (unsigned int)section.sh_addralign);
	}

printf("Key to Flags:\n");
printf("  W (write), A (alloc), X (execute), M (merge), S (strings)\n");
printf("  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)\n");
printf("  O (extra OS processing required) o (OS specific), p (processor specific)\n");

	free(names);
}

void print_section_64(FILE *file)
{
	Elf64_Ehdr header;
	Elf64_Shdr str_table;
	Elf64_Shdr section;
	char *names = NULL, flags[3];
	int i, j;

	fread(&header, sizeof(header), 1, file);
	fseek(file, (unsigned int)header.e_shoff + sizeof(section) * (unsigned int)header.e_shstrndx, SEEK_SET);
	fread(&str_table, sizeof(str_table), 1, file);
	fseek(file, (unsigned int)str_table.sh_offset, SEEK_SET);
	names = malloc(sizeof(char) * str_table.sh_size); /* malloc error unhandled */
	fread(names, str_table.sh_size, 1, file);
	fseek(file, header.e_shoff, SEEK_SET);

	printf("There are %d section headers, starting at offset 0x%x:\n", header.e_shnum, (unsigned int)header.e_shoff);
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
		else if (section.sh_type == SHT_GNU_verdef)
			printf("VERDEF          ");
		else if (section.sh_type == LOOS_1)
			printf("LOOS+ffffff1    ");
		else if (section.sh_type == LOOS_3)
			printf("LOOS+ffffff3    ");
		else
			printf("UNKNOWN         ");

		printf("%016lx ", (unsigned long int)section.sh_addr);
		printf("%06lx ", (unsigned long int)section.sh_offset);
		printf("%06x ", (unsigned int)section.sh_size);
		printf("%02x ", (unsigned int)section.sh_entsize);
		for (j = 0; j < 3; j++)
			flags[j] = ' ';
		j = 2;
		if (section.sh_flags & SHF_EXECINSTR)
			flags[j--] = 'X';
		if (section.sh_flags & SHF_INFO_LINK)
			flags[j--] = 'I';
		if (section.sh_flags & SHF_STRINGS)
			flags[j--] = 'S';
		if (section.sh_flags & SHF_MERGE)
			flags[j--] = 'M';
		if (section.sh_flags & SHF_ALLOC)
			flags[j--] = 'A';
		if (section.sh_flags & SHF_WRITE)
			flags[j--] = 'W';
		if (section.sh_flags & SHF_EXCLUDE)
			flags[j--] = 'E';
		printf("%c%c%c ", flags[0], flags[1], flags[2]);
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
