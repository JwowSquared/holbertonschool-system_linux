#include <stdio.h>

/**
* main - entrypoint for hnm and hobjdump
* @ac: argc
* @av: argv
*
* Return: 0 on success, else 1
*/
int main(int ac, char **av)
{
	if (ac != 2)
	{
		printf("Usage: hnm [objfile ...]\n");
		return (1);
	}

	printf("Something with %s!!!\n", av[1]);

	return (0);
}
