CFLAGS = -c -Wall
CC = gcc

all: resolver

resolver: HW02.o
	${CC} HW02.o -o resolver

resolver.o: HW02.c
	${CC} ${CFLAGS} HW02.c

clean:
	rm -f *.o *~