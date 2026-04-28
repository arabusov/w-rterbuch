# Flash Cards v0.04
# Makefile for flashcards
CC=cc
LD=cc
CFLAGS=-O
LDFLAGS=
TUICF=-DBS=127 -DENTER=10
TUILF=-lcurses
PREFIX ?=/usr/local

all: fcadd fcc fctui

FCLIB=test.o random.o io.o

fctui: io.o test.o random.o fctui.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(TUICF) -o $@ fctui.c $(FCLIB) $(TUILF)

fcc: io.o test.o random.o fcc.o
	$(LD) $(LDFLAGS) -o fcc fcc.o $(FCLIB)

fcadd: fcadd.o io.o
	$(LD) $(LDFLAGS) -o fcadd fcadd.o io.o

random.o: random.h random.c
fcc.o: test.h io.h dict.h fcc.c
test.o:	dict.h io.h test.c
fcadd.o: dict.h io.h fcadd.c
io.o: dict.h io.h io.c

install: $(PREFIX)/bin/fcadd $(PREFIX)/bin/fcc $(PREFIX)/bin/fctui

$(PREFIX)/bin/fcadd: fcadd
	install -cs fcadd $@

$(PREFIX)/bin/fcc: fcc
	install -cs fcc $@

$(PREFIX)/bin/fctui: fctui
	install -cs fctui $@
clean:
	rm -f *.bak *.o *.s core fcc fcadd fctui
