#include "hbtn_elf.h"

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
			print_elf_32(file);
		else if (magic[EI_CLASS] == ELFCLASS64)
			print_elf_64(file);
	}

	fclose(file);

	return (0);
}

void print_elf_32(FILE *file)
{
	Elf32_Ehdr header;
	int i;

	fread(&header, sizeof(header), 1, file);
	printf("ELF Header:\n");
	/* Magic */
	printf("  Magic:  "); /* confirmed */
	for (i = 0; i < EI_NIDENT; i++)
		printf(" %02x", header.e_ident[i]);
	printf(" \n");
	/* Class */
	printf("  Class:                             ");
	printf("ELF32\n");
	/* Data */
	printf("  Data:                              ");
	if (header.e_ident[EI_DATA] == ELFDATA2LSB)
		printf("2's complement, little endian\n"); /* confirmed */
	else if (header.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		printf("2's complement, big endian\n");
		flip32_0(&header);
	}
	else
		printf("UNKNOWN\n");
	/* Version */
	printf("  Version:                           ");
	if (header.e_ident[EI_VERSION] == EV_CURRENT)
		printf("1 (current)\n"); /* confirmed */
	else
		printf("UNKNOWN\n");
	/* OS/ABI */
	printf("  OS/ABI:                            ");
	if (header.e_ident[EI_OSABI] == ELFOSABI_SYSV)
		printf("UNIX - System V\n"); /* confirmed */
	else if (header.e_ident[EI_OSABI] == ELFOSABI_HPUX)
		printf("HP-UX\n");
	else if (header.e_ident[EI_OSABI] == ELFOSABI_NETBSD)
		printf("UNIX - NetBSD\n"); /* confirmed */
	else if (header.e_ident[EI_OSABI] == ELFOSABI_LINUX)
		printf("Linux\n");
	else if (header.e_ident[EI_OSABI] == ELFOSABI_SOLARIS)
		printf("UNIX - Solaris\n"); /* confirmed */
	else if (header.e_ident[EI_OSABI] == ELFOSABI_IRIX)
		printf("IRIX\n");
	else if (header.e_ident[EI_OSABI] == ELFOSABI_FREEBSD)
		printf("FreeBSD\n");
	else if (header.e_ident[EI_OSABI] == ELFOSABI_TRU64)
		printf("TRU64 UNIX\n");
	else if (header.e_ident[EI_OSABI] == ELFOSABI_ARM)
		printf("ARM architecture\n");
	else if (header.e_ident[EI_OSABI] == ELFOSABI_STANDALONE)
		printf("Stand-alone (embedded)\n");
	else
		printf("<unknown: %02x>\n", header.e_ident[EI_OSABI]);
	/* ABI Version */
	printf("  ABI Version:                       ");
	printf("%u\n", (unsigned int)header.e_ident[EI_ABIVERSION]);
	/* Type */
	printf("  Type:                              ");
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
	/* Machine */
	printf("  Machine:                           ");
	if (header.e_machine == EM_M32)
		printf("AT&T WE 32100\n");
	else if (header.e_machine == EM_SPARC)
		printf("Sparc\n");
	else if (header.e_machine == EM_386)
		printf("Intel 80386\n"); /* confirmed */
	else if (header.e_machine == EM_68K)
		printf("Motorola 68000\n");
	else if (header.e_machine == EM_88K)
		printf("Motorola 88000\n");
	else if (header.e_machine == EM_860)
		printf("Intel 80860\n");
	else if (header.e_machine == EM_MIPS)
		printf("MIPS RS3000\n");
	else if (header.e_machine == EM_PARISC)
		printf("HP/PA\n");
	else if (header.e_machine == EM_SPARC32PLUS)
		printf("SPARC with enhanced instruction set\n");
	else if (header.e_machine == EM_PPC)
		printf("PowerPC\n");
	else if (header.e_machine == EM_PPC64)
		printf("PowerPC 64-bit\n");
	else if (header.e_machine == EM_S390)
		printf("IBM S/390\n");
	else if (header.e_machine == EM_ARM)
		printf("Advanced RISC Machines\n");
	else if (header.e_machine == EM_SH)
		printf("Renesas SuperH\n");
	else if (header.e_machine == EM_SPARCV9)
		printf("SPARC v9 64-bit\n");
	else if (header.e_machine == EM_IA_64)
		printf("Intel Itanium\n");
	else if (header.e_machine == EM_X86_64)
		printf("Advanced Micro Devices X86-64\n"); /* confirmed */
	else if (header.e_machine == EM_VAX)
		printf("Dec Vax\n");
	else
		printf("UNKNOWN\n");
	/* Version */
	printf("  Version:                           ");
	if (header.e_version == EV_CURRENT)
		printf("0x1\n");
	else
		printf("UNKNOWN\n");
	printf("  Entry point address:               0x%x\n", (unsigned int)header.e_entry);
	printf("  Start of program headers:          %u (bytes into file)\n", (unsigned int)header.e_phoff);
	printf("  Start of section headers:          %u (bytes into file)\n", (unsigned int)header.e_shoff);
	printf("  Flags:                             0x0\n");
	printf("  Size of this header:               %u (bytes)\n", (unsigned int)header.e_ehsize);
	printf("  Size of program headers:           %u (bytes)\n", (unsigned int)header.e_phentsize);
	printf("  Number of program headers:         %u\n", (unsigned int)header.e_phnum);
	printf("  Size of section headers:           %u (bytes)\n", (unsigned int)header.e_shentsize);
	printf("  Number of section headers:         %u\n", (unsigned int)header.e_shnum);
	printf("  Section header string table index: %u\n", (unsigned int)header.e_shstrndx);
}

void print_elf_64(FILE *file)
{
	Elf64_Ehdr header;
	int i;

	fread(&header, sizeof(header), 1, file);

	printf("ELF Header:\n");
	/* Magic */
	printf("  Magic:  "); /* confirmed */
	for (i = 0; i < EI_NIDENT; i++)
		printf(" %02x", header.e_ident[i]);
	printf(" \n");
	/* Class */
	printf("  Class:                             ");
	printf("ELF64\n"); /* confirmed */
	/* Data */
	printf("  Data:                              ");
	if (header.e_ident[EI_DATA] == ELFDATA2LSB)
		printf("2's complement, little endian\n"); /* confirmed */
	else if (header.e_ident[EI_DATA] == ELFDATA2MSB)
	{
		printf("2's complement, big endian\n");
		flip64_0(&header);
	}
	else
		printf("UNKNOWN\n");
	/* Version */
	printf("  Version:                           ");
	if (header.e_ident[EI_VERSION] == EV_CURRENT)
		printf("1 (current)\n"); /* confirmed */
	else
		printf("UNKNOWN\n");
	/* OS/ABI */
	printf("  OS/ABI:                            ");
	if (header.e_ident[EI_OSABI] == ELFOSABI_SYSV)
		printf("UNIX - System V\n"); /* confirmed */
	else if (header.e_ident[EI_OSABI] == ELFOSABI_HPUX)
		printf("HP-UX\n");
	else if (header.e_ident[EI_OSABI] == ELFOSABI_NETBSD)
		printf("UNIX - NetBSD\n"); /* confirmed */
	else if (header.e_ident[EI_OSABI] == ELFOSABI_LINUX)
		printf("Linux\n");
	else if (header.e_ident[EI_OSABI] == ELFOSABI_SOLARIS)
		printf("UNIX - Solaris\n"); /* confirmed */
	else if (header.e_ident[EI_OSABI] == ELFOSABI_IRIX)
		printf("IRIX\n");
	else if (header.e_ident[EI_OSABI] == ELFOSABI_FREEBSD)
		printf("FreeBSD\n");
	else if (header.e_ident[EI_OSABI] == ELFOSABI_TRU64)
		printf("TRU64 UNIX\n");
	else if (header.e_ident[EI_OSABI] == ELFOSABI_ARM)
		printf("ARM architecture\n");
	else if (header.e_ident[EI_OSABI] == ELFOSABI_STANDALONE)
		printf("Stand-alone (embedded)\n");
	else
		printf("<unknown: %02x>\n", header.e_ident[EI_OSABI]);
	/* ABI Version */
	printf("  ABI Version:                       ");
	printf("%u\n", (unsigned int)header.e_ident[EI_ABIVERSION]);
	/* Type */
	printf("  Type:                              ");
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
	/* Machine */
	printf("  Machine:                           ");
	if (header.e_machine == EM_M32)
		printf("AT&T WE 32100\n");
	else if (header.e_machine == EM_SPARC)
		printf("Sparc\n");
	else if (header.e_machine == EM_386)
		printf("Intel 80386\n"); /* confirmed */
	else if (header.e_machine == EM_68K)
		printf("Motorola 68000\n");
	else if (header.e_machine == EM_88K)
		printf("Motorola 88000\n");
	else if (header.e_machine == EM_860)
		printf("Intel 80860\n");
	else if (header.e_machine == EM_MIPS)
		printf("MIPS RS3000\n");
	else if (header.e_machine == EM_PARISC)
		printf("HP/PA\n");
	else if (header.e_machine == EM_SPARC32PLUS)
		printf("SPARC with enhanced instruction set\n");
	else if (header.e_machine == EM_PPC)
		printf("PowerPC\n");
	else if (header.e_machine == EM_PPC64)
		printf("PowerPC 64-bit\n");
	else if (header.e_machine == EM_S390)
		printf("IBM S/390\n");
	else if (header.e_machine == EM_ARM)
		printf("Advanced RISC Machines\n");
	else if (header.e_machine == EM_SH)
		printf("Renesas SuperH\n");
	else if (header.e_machine == EM_SPARCV9)
		printf("SPARC v9 64-bit\n");
	else if (header.e_machine == EM_IA_64)
		printf("Intel Itanium\n");
	else if (header.e_machine == EM_X86_64)
		printf("Advanced Micro Devices X86-64\n"); /* confirmed */
	else if (header.e_machine == EM_VAX)
		printf("Dec Vax\n");
	else
		printf("UNKNOWN\n");
	/* Version */
	printf("  Version:                           ");
	if (header.e_version == EV_CURRENT)
		printf("0x1\n");
	else
		printf("UNKNOWN\n");
	printf("  Entry point address:               0x%x\n", (unsigned int)header.e_entry);
	printf("  Start of program headers:          %u (bytes into file)\n", (unsigned int)header.e_phoff);
	printf("  Start of section headers:          %u (bytes into file)\n", (unsigned int)header.e_shoff);
	printf("  Flags:                             0x0\n");
	printf("  Size of this header:               %u (bytes)\n", (unsigned int)header.e_ehsize);
	printf("  Size of program headers:           %u (bytes)\n", (unsigned int)header.e_phentsize);
	printf("  Number of program headers:         %u\n", (unsigned int)header.e_phnum);
	printf("  Size of section headers:           %u (bytes)\n", (unsigned int)header.e_shentsize);
	printf("  Number of section headers:         %u\n", (unsigned int)header.e_shnum);
	printf("  Section header string table index: %u\n", (unsigned int)header.e_shstrndx);
}
