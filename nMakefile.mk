.SUFFIXES : .c

CC = cl.exe
LINK = link.exe
CFLAGS = /O2
CFLAGS2 = /Oi
CFLAGS3 = /GL

TARGET = main.exe
OBJS = main.o module_1.o module_2.o util.o mem.o

all : $(TARGET)

$(TARGET) : $(OBJS)
	$(LINK) /OUT:main.exe $(OBJS)

main.o : main.c mem.o
	$(CC) /c main.c /Fomain.o $(CFLAGS) $(CFLAGS2) $(CFLAGS3)

module_1.o : module_1.c mem.o
	$(CC) /c module_1.c /Fomodule_1.o $(CFLAGS) $(CFLAGS2) $(CFLAGS3)

module_2.o : module_2.c mem.o
	$(CC) /c module_2.c /Fomodule_2.o $(CFLAGS) $(CFLAGS2) $(CFLAGS3)

util.o : util.c
	$(CC) /c util.c /Foutil.o $(CFLAGS) $(CFLAGS2) $(CFLAGS3)

mem.o : mem.c
	$(CC) /c mem.c /Fomem.o $(CFLAGS) $(CFLAGS2) $(CFLAGS3)

clean :
	del $(OBJS) $(TARGET)