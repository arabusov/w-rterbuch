TESTS=unit01.exe unit02.exe
CC=gcc
LD=$(CC)
CFLAGS=-g -ggdb -I.. --coverage
LDFLAGS=-g -ggdb --coverage

all: test

test: $(TESTS) test.sh
	@bash test.sh

indent:
	indent -kr -i8 *.[ch]
	rm -f *~
.PHONY: random.o io.o unit01.o unit02.o unit01.exe unit02.exe
random.o: ../random.c ../random.h
	$(CC) $(CFLAGS) -c -o $@ $<
io.o: ../io.c ../io.h
	$(CC) $(CFLAGS) -c -o $@ $<
unit01.o: unit01.c
	$(CC) $(CFLAGS) -c -o $@ $<
unit02.o: unit02.c
	$(CC) $(CFLAGS) -c -o $@ $<

unit01.exe: unit01.o random.o
	$(LD) $(LDFLAGS) -lm -o $@ $^

unit02.exe: unit02.o io.o
	$(LD) $(LDFLAGS) -o $@ $^

unit01_cov:
	gcov -o ./ ../random.c unit01.c -m

unit02_cov:
	gcov -o ./ ../io.c unit02.c -m

cov: test unit01_cov unit02_cov
	mkdir -p coverage
	@rm -rf unit*.gc*
	@gcovr -r ../ --txt
	@gcovr -r ../ --html-self-contained --html-details -o coverage/fcc.html

clean:
	rm -f $(TESTS)
	rm -f *.gc*
	rm -rf coverage
	rm -f *.o
