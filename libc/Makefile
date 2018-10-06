CC = clang
AR = ar

CFLAGS 	= -target i686-elf -c -Wall -Wextra -ffreestanding -Iinclude
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)

all: libc

libc: $(OBJ)
	$(AR) cvq ../dist/flibc.a $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) $^

clean:
	@rm -rf $(OBJ)
