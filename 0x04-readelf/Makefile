all: 0-hreadelf 1-hreadelf 2-hreadelf

files-0 = \
0-readelf.c \
0-fetch.c \
ehdr_flip.c \
flipEndian.c

files-1 = \
1-readelf.c \
1-fetch.c \
ehdr_flip.c \
shdr_flip.c \
flipEndian.c

files-2 = \
2-readelf.c \
ehdr_flip.c \
shdr_flip.c \
phdr_flip.c \
flipEndian.c

0-hreadelf: $(files-0)
	gcc -Wall -Werror -Wextra -pedantic $(files-0) -o 0-hreadelf

1-hreadelf: $(files-1)
	gcc -Wall -Werror -Wextra -pedantic $(files-1) -o 1-hreadelf

2-hreadelf: $(files-2)
	gcc -Wall -Werror -Wextra -pedantic $(files-2) -o 2-hreadelf

clean:
	rm 0-hreadelf 1-hreadelf 2-hreadelf
