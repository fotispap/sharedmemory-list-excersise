CC=gcc
CFLAGS=-o 
LDFLAGS=
SOURCES=sharedlist.c searcher.c inserter.c deleter.c 
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=hello

all: sharedlist deleter searcher inserter

sharedlist: sharedlist.c listmanagement.c listmanagement.h
	$(CC) $(CFLAGS) sharedlist sharedlist.c -g3 listmanagement.c

searcher: searcher.c listmanagement.c listmanagement.h
	$(CC) $(CFLAGS) searcher searcher.c -g3 listmanagement.c
	
deleter: deleter.c listmanagement.c listmanagement.h
	$(CC) $(CFLAGS) deleter deleter.c -g3 listmanagement.c

inserter: inserter.c listmanagement.c listmanagement.h
	$(CC) $(CFLAGS) inserter inserter.c listmanagement.c -g3
	

clean:
	rm sharedlist deleter searcher inserter
