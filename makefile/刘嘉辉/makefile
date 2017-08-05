#刘嘉辉的makefile 
LIBS = -lm
cc = gcc
OBJS = test
all:
		$(cc) -S ./*.c #.c -> .s
		$(cc) -c ./*.s #.s -> .o
		$(cc) -o  $(OBJS) ./*.o  $(LIBS)   #.o-> 可执行文件
