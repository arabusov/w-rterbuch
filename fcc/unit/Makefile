TESTS=unit01.exe unit02.exe
CFLAGS=-I.. --coverage

all: test

test: $(TESTS) test.sh
	@bash test.sh

indent:
	indent -kr -i8 *.[ch]
	rm -f *~

unit01.exe: unit01.c ../random.h ../random.c
	$(CC) $(CFLAGS) $(LDFLAGS) -lm -o $@ $^

unit02.exe: unit02.c ../io.h ../io.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

unit01_cov: 
	@gcov -o ./ ../random.c unit01.c -m

unit02_cov: 
	@gcov -o ./ ../io.c unit02.c -m

cov: test unit01_cov unit02_cov
	mkdir -p coverage
	@gcovr -r ../ --txt --branches
	@gcovr -r ../ --html-self-contained --html-details -o coverage/fcc.html

clean:
	rm -f $(TESTS)
	rm -f *.gc*
	rm -rf coverage
