# Flash Cards v0.02
# Makefile for flashcards
CC=cc
LD=cc
CFLAGS=-O
LDFLAGS=

OBJ = io.o fcadd.o test.o fcc.o

all: fcadd fcc fctui

fctui: io.o test.o fctui.o
	$(LD) $(LDFLAGS) -o fctui fctui.o test.o io.o -lcurses

fcc: io.o test.o fcc.o
	$(LD) $(LDFLAGS) -o fcc fcc.o test.o io.o

fcadd: fcadd.o io.o
	$(LD) $(LDFLAGS) -o fcadd fcadd.o io.o

fcc.o: test.h io.h dict.h fcc.c
test.o:	dict.h io.h test.c
fcadd.o: dict.h io.h fcadd.c
io.o: dict.h io.h io.c

clean:
	rm -f *.bak *.o *.s core fcc fcadd fctui
