#include "hbtn_elf.h"

/**
* fetch_ei_data - matches macro with string to display. Only includes enough to match given cases.
* @data: value in the EI_DATA slot of the e_ident member of an ElfN_Ehdr
*
* Return: string to be displayed
*/
char *fetch_ei_data(unsigned int data)
{

	if (data == ELFDATA2LSB)
		return ("2's complement, little endian");
	if (data == ELFDATA2MSB)
		return ("2's complement, big endian");

	return ("UNIMPLEMENTED");
}

/**
* fetch_ei_osabi - matches macro with string to display. Only includes enough to match given cases.
* @osabi: value in the EI_OSABI slot of the e_ident member of an ElfN_Ehdr
*
* Return: string to be displayed
*/
char *fetch_ei_osabi(unsigned int osabi)
{
	if (osabi == ELFOSABI_SYSV)
		return ("UNIX - System V");
	if (osabi == ELFOSABI_NETBSD)
		return ("UNIX - NetBSD");
	if (osabi == ELFOSABI_SOLARIS)
		return ("UNIX - Solaris");
	if (osabi == 0x53)
		return ("<unknown: 53>");

	return ("UNIMPLEMENTED");
}

/**
* fetch_e_machine - matches macro with string to display. Only includes enough to match given cases.
* @machine: e_machine member of an ElfN_Ehdr
*
* Return: string to be displayed
*/
char *fetch_e_machine(unsigned int machine)
{
	if (machine == EM_SPARC)
		return ("Sparc");
	if (machine == EM_386)
		return ("Intel 80386");
	if (machine == EM_X86_64)
		return ("Advanced Micro Devices X86-64");

	return ("UNIMPLEMENTED");
}

/**
* fetch_e_type - matches macro with string to display. Only includes enough to match given cases.
* @type: e_type member of an ElfN_Ehdr
*
* Return: string to be displayed
*/
char *fetch_e_type(unsigned int type)
{
	if (type == ET_REL)
		return ("REL (Relocatable file)");
	if (type == ET_EXEC)
		return ("EXEC (Executable file)");
	if (type == ET_DYN)
		return ("DYN (Shared object file)");

	return ("UNIMPLEMENTED");
}
