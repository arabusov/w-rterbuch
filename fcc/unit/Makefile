TESTS=unit01.exe unit02.exe
CFLAGS=-I..

all: test

test: $(TESTS) test.sh
	@bash test.sh

indent:
	indent -kr -i8 *.[ch]
	rm -f *~

unit01.exe: unit01.c ../random.c ../random.h
	$(CC) $(CFLAGS) $(LDFLAGS) -lm -o $@ $^

unit02.exe: unit02.c ../io.c ../io.h
	$(CC) $(CFLAGS) $(LDFLAGS) -lm -o $@ $^

clean:
	rm -f $(TESTS)
