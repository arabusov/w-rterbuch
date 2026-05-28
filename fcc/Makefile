# Flash Cards v0.04
# Makefile for flashcards
CC=cc
LD=cc
CFLAGS=-O
LDFLAGS=
TUICF=-DBS=127 -DENTER=10
TUILF=-lcurses
PREFIX ?=/usr/local

all: fcadd fcc fctui fc2anki

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

fcc: io.o mc.o random.o fccli.o fcc.o
	$(LD) $(LDFLAGS) -o fcc fcc.o fccli.o $(FCLIB)

fcadd: fcadd.o add.o io.o
	$(LD) $(LDFLAGS) -o fcadd fcadd.o add.o io.o

fc2anki: fc2anki.o export.o io.o
	$(LD) $(LDFLAGS) -o fc2anki fc2anki.o export.o io.o

random.o: random.h random.c
fccli.o: mc.h io.h dict.h fccli.c
fcc.o: fccli.h fcc.c
mc.o: dict.h io.h mc.c
add.o: add.h dict.h io.h add.c
fcadd.o: add.h fcadd.c
io.o: dict.h io.h io.c
export.o: bool.h dict.h export.h io.h export.c
fc2anki.o: export.h fc2anki.c

install: $(PREFIX)/bin/fcadd $(PREFIX)/bin/fcc $(PREFIX)/bin/fctui $(PREFIX)/bin/fc2anki

$(PREFIX)/bin/fcadd: fcadd
	install -cs fcadd $@

$(PREFIX)/bin/fcc: fcc
	install -cs fcc $@

$(PREFIX)/bin/fctui: fctui
	install -cs fctui $@

$(PREFIX)/bin/fc2anki: fc2anki
	install -cs fc2anki $@

clean:
	rm -f *.bak *.o *.s core fcc fcadd fctui fc2anki
	make -C unit clean
