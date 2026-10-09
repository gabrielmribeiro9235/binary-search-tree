CC = gcc
CFLAGS = -Wall -Wextra

all = my_program

my_program: main.o binary_search_tree.o
	  $(CC) $(CFLAGS) -o my_program main.o binary_search_tree.o

main.o: main.c binary_search_tree.h
	  $(CC) $(CFLAGS) -c -o main.o main.c

binary_search_tree.o: binary_search_tree.c binary_search_tree.h
	  $(CC) $(CFLAGS) -c -o binary_search_tree.o binary_search_tree.c

clean:
	  rm -f my_program main.o binary_search_tree.o