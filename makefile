CC = gcc
CFLAGS = -Wall -g

all: student_shell

student_shell: shell.o
	$(CC) $(CFLAGS) -o student_shell shell.o

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c

clean:
	rm -f student_shell *.o
