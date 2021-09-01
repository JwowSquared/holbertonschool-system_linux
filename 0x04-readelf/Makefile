all: 0-hreadelf 1-hreadelf

files-0 = \
0-readelf.c \
0-flip.c \
flipEndian.c

files-1 = \
1-readelf.c

0-hreadelf: $(files-0)
	gcc -Wall -Werror -Wextra -pedantic $(files-0) -o 0-hreadelf

1-hreadelf: $(files-1)
	gcc -Wall -Werror -Wextra -pedantic $(files-1) -o 1-hreadelf
clean:
	rm 0-hreadelf 1-hreadelf
