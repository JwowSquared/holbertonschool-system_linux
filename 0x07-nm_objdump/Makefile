all: hnm hobjdump

files-0 = \
main.c

files-1 = \
main.c

hnm: $(files-0)
	gcc -Wall -Werror -Wextra -pedantic $(files-0) -o hnm

hobjdump: $(files-1)
	gcc -Wall -Werror -Wextra -pedantic $(files-1) -o hobjdump

clean:
	rm hnm hobjdump
