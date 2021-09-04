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
		fseek(file, 0, SEEK_SET);
		if (magic[EI_CLASS] == ELFCLASS32)
			print32_Shdr(file);
		else if (magic[EI_CLASS] == ELFCLASS64)
			print64_Shdr(file);
	}

	fclose(file);

	return (0);
}

/**
* print32_Shdr - prints an Elf32_Shdr. Almost identical to print64_Shdr -- see README
* @file: open file pointer to ELF
*/
void print32_Shdr(FILE *file)
{
	Elf32_Ehdr header;
	Elf32_Shdr section;
	char *names = NULL;
	int i;

	fread(&header, sizeof(header), 1, file);
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		flip32_Ehdr(&header);
	fseek(file, header.e_shoff + sizeof(section) * header.e_shstrndx, SEEK_SET);
	fread(&section, sizeof(section), 1, file);
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		flip32_Shdr(&section);
	fseek(file, section.sh_offset, SEEK_SET);
	names = malloc(sizeof(char) * section.sh_size); /* malloc error unhandled */
	fread(names, section.sh_size, 1, file);
	fseek(file, header.e_shoff, SEEK_SET);

	printf("There are %d section headers, starting at offset %#x:\n", header.e_shnum, header.e_shoff); /*%lx*/
	printf("\nSection Headers:\n");
	printf("  [Nr] Name              Type            Addr     Off    Size   ES Flg Lk Inf Al\n"); /*diff prompt*/
	for (i = 0; i < header.e_shnum; i++)
	{
		fread(&section, sizeof(section), 1, file);
		if (header.e_ident[EI_DATA] == ELFDATA2MSB)
			flip32_Shdr(&section);
		printf("  [%2d] ", i);
		printf("%-17s ", names + section.sh_name);
		printf("%-15s ", fetch_sh_type(section.sh_type)); /*%-17s*/
		printf("%08x ", section.sh_addr); /*%016lx*/
		printf("%06x ", section.sh_offset); /*%lx*/
		printf("%06x ", section.sh_size); /*%lx*/
		printf("%02x ", section.sh_entsize); /*%lx*/
		print_sh_flags(section.sh_flags);
		printf("%2u ", section.sh_link);
		printf("%3u ", section.sh_info);
		printf("%2u\n", section.sh_addralign); /*%lu*/
	}

	printf("Key to Flags:\n"); /*diff prompt*/
	printf("  W (write), A (alloc), X (execute), M (merge), S (strings)\n");
	printf("  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)\n");
	printf("  O (extra OS processing required) o (OS specific), p (processor specific)\n");

	free(names);
}

/**
* print64_Shdr - prints an Elf64_Shdr. Almost identical to print32_Shdr -- see README
* @file: open file pointer to ELF
*/
void print64_Shdr(FILE *file)
{
	Elf64_Ehdr header;
	Elf64_Shdr section;
	char *names = NULL;
	int i;

	fread(&header, sizeof(header), 1, file);
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		flip64_Ehdr(&header);
	fseek(file, header.e_shoff + sizeof(section) * header.e_shstrndx, SEEK_SET);
	fread(&section, sizeof(section), 1, file);
	if (header.e_ident[EI_DATA] == ELFDATA2MSB)
		flip64_Shdr(&section);
	fseek(file, section.sh_offset, SEEK_SET);
	names = malloc(sizeof(char) * section.sh_size); /* malloc error unhandled */
	fread(names, section.sh_size, 1, file);
	fseek(file, header.e_shoff, SEEK_SET);

	printf("There are %d section headers, starting at offset %#lx:\n", header.e_shnum, header.e_shoff); /*%x*/
	printf("\nSection Headers:\n");
	printf("  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al\n"); /*diff prompt*/
	for (i = 0; i < header.e_shnum; i++)
	{
		fread(&section, sizeof(section), 1, file);
		if (header.e_ident[EI_DATA] == ELFDATA2MSB)
			flip64_Shdr(&section);
		printf("  [%2d] ", i);
		printf("%-17s ", names + section.sh_name);
		printf("%-17s ", fetch_sh_type(section.sh_type));
		printf("%016lx ", section.sh_addr); /*%08x*/
		printf("%06lx ", section.sh_offset); /*%x*/
		printf("%06lx ", section.sh_size); /*%x*/
		printf("%02lx ", section.sh_entsize); /*%x*/
		print_sh_flags(section.sh_flags);
		printf("%2u ", section.sh_link);
		printf("%3u ", section.sh_info);
		printf("%2lu\n", section.sh_addralign); /*%x*/
	}

	printf("Key to Flags:\n"); /*diff prompt*/
	printf("  W (write), A (alloc), X (execute), M (merge), S (strings), l (large)\n");
	printf("  I (info), L (link order), G (group), T (TLS), E (exclude), x (unknown)\n");
	printf("  O (extra OS processing required) o (OS specific), p (processor specific)\n");

	free(names);
}

char *fetch_sh_type(unsigned int type)
{
	if (type == SHT_NULL)
		return ("NULL");
	if (type == SHT_PROGBITS)
		return ("PROGBITS");
	if (type == SHT_SYMTAB)
		return ("SYMTAB");
	if (type == SHT_STRTAB)
		return ("STRTAB");
	if (type == SHT_RELA)
		return ("RELA");
	if (type == SHT_HASH)
		return ("HASH");
	if (type == SHT_DYNAMIC)
		return ("DYNAMIC");
	if (type == SHT_NOTE)
		return ("NOTE");
	if (type == SHT_NOBITS)
		return ("NOBITS");
	if (type == SHT_REL)
		return ("REL");
	if (type == SHT_SHLIB)
		return ("SHLIB");
	if (type == SHT_DYNSYM)
		return ("DYNSYM");
	if (type == SHT_GNU_HASH)
		return ("GNU_HASH");
	if (type == SHT_GNU_versym)
		return ("VERSYM");
	if (type == SHT_GNU_verneed)
		return ("VERNEED");
	if (type == SHT_INIT_ARRAY)
		return ("INIT_ARRAY");
	if (type == SHT_FINI_ARRAY)
		return ("FINI_ARRAY");
	if (type == 0x6ffffffc)
		return ("VERDEF");
	if (type == 0x6ffffff1)
		return ("LOOS+ffffff1");
	if (type == 0x6ffffff3)
		return ("LOOS+ffffff3");

	return ("UNIMPLEMENTED");
}

void print_sh_flags(unsigned long int raw)
{
	int i = 2;
	char flags[3];

	if (raw & SHF_EXECINSTR)
		flags[i--] = 'X';
	if (raw & SHF_INFO_LINK)
		flags[i--] = 'I';
	if (raw & SHF_STRINGS)
		flags[i--] = 'S';
	if (raw & SHF_MERGE)
		flags[i--] = 'M';
	if (raw & SHF_ALLOC)
		flags[i--] = 'A';
	if (raw & SHF_WRITE)
		flags[i--] = 'W';
	if (raw & SHF_EXCLUDE)
		flags[i--] = 'E';
	while (i >= 0)
		flags[i--] = ' ';

	printf("%c%c%c ", flags[0], flags[1], flags[2]);
}
