CC = clang
CFLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic -I./inc

LIB_NAME = libmx.a

all: LIBMX CREATE_LIB

LIBMX:
	mkdir obj
	$(CC) $(CFLAGS) -c src/*.c
	mv *.o obj/

CREATE_LIB:
	ar -rc $(LIB_NAME) obj/*.o
	ranlib $(LIB_NAME)

clean:
	rm -rf obj

uninstall:
	rm -rf obj
	rm -rf $(LIB_NAME)

reinstall: 
	make uninstall
	make
