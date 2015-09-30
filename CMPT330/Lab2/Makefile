CC=clang
CFLAGS=-c -Wall
LD=gcc
LDFLAGS=-pthread
LDLIBS=
SOURCES=main.c 
OBJECTS=$(SOURCES:.c=.o)

all: sender receiver

sender: sender.o common.o
	$(LD) $(LDFLAGS) $(LDLIBS) sender.o common.o -o sender

receiver: receiver.o common.o
	$(LD) $(LDFLAGS) $(LDLIBS) receiver.o common.o -o receiver

*.o: *.c common.h
	$(CC) $(CFLAGS) *.c

clean:
	rm -f *.o sender receiver
