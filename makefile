all: prog
use_bisection: prog_bisection

prog: main.o functions.o
	gcc -m32 functions.o main.o -lm -o prog

prog_bisection: main.o_bisection functions.o
	gcc -m32 functions.o main.o -lm -o prog

main.o: main.c
	gcc -m32 -c main.c -o main.o

main.o_bisection: main.c
	gcc -m32 -c main.c -Dbi -o main.o

functions.o: functions.asm
	nasm -f elf32 -o functions.o functions.asm
	
clean:
	rm -rf *.o prog