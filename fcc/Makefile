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

test:
	@make -C unit
cov:
	@make -C unit cov

indent:
	indent -kr -i8 *.[ch]
	rm -f *~
	make -C unit indent

FCLIB=mc.o random.o io.o

fctui: $(FCLIB) fctui.o
	$(CC) $(CFLAGS) $(LDFLAGS) $(TUICF) -o $@ fctui.c $(FCLIB) $(TUILF)

fcc: io.o mc.o random.o fcc.o
	$(LD) $(LDFLAGS) -o fcc fcc.o $(FCLIB)

fcadd: fcadd.o io.o
	$(LD) $(LDFLAGS) -o fcadd fcadd.o io.o

random.o: random.h random.c
fcc.o: mc.h io.h dict.h fcc.c
mc.o:	dict.h io.h mc.c
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
	make -C unit clean
