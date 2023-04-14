CC = gcc
TARGET = main
OBJS = main.o module_1.o module_2.o util.o mem.o

all : $(TARGET)

main : main.o module_1.o module_2.o util.o mem.o
	$(CC) -o $(TARGET) $(OBJS)
main.o : main.c mem.o
	$(CC) -c main.c
module_1 : module_1.c mem.o
	$(CC) -c module_1.c
module_2 : module_2.c mem.o
	$(CC) -c module_2.c
util.o : util.c
	$(CC) -c util.c
mem.o : mem.c
	$(CC) -c mem.c

clean :
	rm $(OBJS) $(TARGET)
