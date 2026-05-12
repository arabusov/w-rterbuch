TESTS=unit01.exe unit02.exe unit03.exe unit04.exe unit05.exe
CC=gcc
LD=$(CC)
CFLAGS=-g -ggdb -I.. --coverage
LDFLAGS=-g -ggdb --coverage

all: test

test: $(TESTS) test.sh
	@bash test.sh
	@rm -rf unit*.gc*

indent:
	indent -kr -i8 *.[ch]
	rm -f *~
.PHONY: mc.o random.o io.o add.o fccli.o
.PHONY: unit01.o unit02.o unit01.exe unit02.exe
.PHONY: unit03.o unit04.o unit03.exe unit04.exe
.PHONY: unit05.o unit05.o
random.o: ../random.c ../random.h
	$(CC) $(CFLAGS) -c -o $@ $<
io.o: ../io.c ../io.h
	$(CC) $(CFLAGS) -c -o $@ $<
mc.o: ../mc.c ../mc.h
	$(CC) $(CFLAGS) -c -o $@ $<
add.o: ../add.c ../add.h
	$(CC) $(CFLAGS) -c -o $@ $<
fccli.o: ../fccli.c ../fccli.h
	$(CC) $(CFLAGS) -c -o $@ $<
unit01.o: unit01.c
	$(CC) $(CFLAGS) -c -o $@ $<
unit02.o: unit02.c
	$(CC) $(CFLAGS) -c -o $@ $<
unit03.o: unit03.c
	$(CC) $(CFLAGS) -c -o $@ $<
unit04.o: unit04.c
	$(CC) $(CFLAGS) -c -o $@ $<
unit05.o: unit05.c
	$(CC) $(CFLAGS) -c -o $@ $<

unit01.exe: unit01.o random.o
	$(LD) $(LDFLAGS) -o $@ $^

unit02.exe: unit02.o io.o
	$(LD) $(LDFLAGS) -o $@ $^

unit03.exe: unit03.o mc.o io.o random.o
	$(LD) $(LDFLAGS) -o $@ $^ -lm

unit04.exe: unit04.o add.o io.o
	$(LD) $(LDFLAGS) -o $@ $^

unit05.exe: unit05.o fccli.o io.o mc.o add.o random.o
	$(LD) $(LDFLAGS) -o $@ $^

cov: test
	mkdir -p coverage
	@rm -rf unit*.gc*
	@gcovr -r ../ --txt
	@gcovr -r ../ --html-self-contained --html-details -o coverage/fcc.html

clean:
	rm -f $(TESTS)
	rm -f *.gc*
	rm -rf coverage
	rm -f *.o
