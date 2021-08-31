#include "hbtn_elf.h"

unsigned long int flipEndian(unsigned long int num, int size)
{
	unsigned long int left, right;

	if (size == 8)
		return (num);

	right = num & ((1 << (size / 2)) - 1);
	left = num >> (size / 2);

	right = flipEndian(right, size / 2);
	left = flipEndian(left, size / 2);

	return (left & (right << (size / 2)));
}
