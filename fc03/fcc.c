/*
 * Flash Cards v0.03
 *
 * Command-line interface for Flash Cards
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dict.h"
#include "io.h"
#include "test.h"

char usage[] = "fcc DICTIONARY";

int
main(int argc, char **argv)
{
	const char *fname = argv[1];
	char buf[MAXLEN];
        struct record *r;

        if (argc != 2) {
                fprintf(stderr, "Wrong number of parameters.\n");
                fprintf(stderr, "Usage: %s\n", usage);
                return(-1);
        }

	if (!read_file(fname))
		return(-1);

        init_test();
        r = roll();
	assert(r <= rec);
        printf("%s: ", r->a);
        scanf("%31s", buf);
        if (test(r, buf))
        	printf("Succ.\n");
        else
        	printf("Fail. Answer: %s\n", r->b);

	if (write_file(fname))
		return(0);
	return -1;
}
