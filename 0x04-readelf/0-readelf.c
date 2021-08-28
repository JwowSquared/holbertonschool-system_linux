#include "hbtn_elf.h"

int main(int ac, char **av)
{
	FILE* file = NULL;
	Elf64_Ehdr header;
	int i;

	if (ac != 2)
	{
		printf("USAGE WRONG DUMBO\n");
		return (2);
	}

	file = fopen(av[1], "rb");
	if (file)
	{
		fread(&header, sizeof(header), 1, file);

		printf("MAGIC =");
		for (i = 0; i < 16; i++)
			printf(" %02x", header.e_ident[i]);
		printf("\n");
	}

	fclose(file);

	return (0);
}
