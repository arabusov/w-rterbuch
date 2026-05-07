TESTS=unit01.exe
CFLAGS=-I..

all: test

test: $(TESTS) test.sh
	@bash test.sh

unit01.exe: unit01.c ../random.c ../random.h
	$(CC) $(CFLAGS) $(LDFLAGS) -lm -o $@ $^

clean:
	rm -f $(TESTS)
