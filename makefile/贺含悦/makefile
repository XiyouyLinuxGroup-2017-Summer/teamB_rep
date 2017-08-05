CC = gcc
DLIBS = -lm

count:main.o jisuan.o
	$(CC) -o count main.o jisuan.o $(DLIBS)
main.o:main.c jisuan.h
	$(CC) -c main.c
jisuan.o:jisuan.h
	$(CC) -c jisuan.c

clean:
	rm count main.o jisuan.o
