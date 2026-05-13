/*
 * Flash Cards v0.04
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
#include "mc.h"
#include "bool.h"

int fccli(int argc, char **argv)
{
	char *usage = "fcc DICTIONARY";
	const char *fname;
	char buf[MAXLEN];
	struct record *r;

	if (argc != 2) {
		fprintf(stderr, "Wrong number of parameters.\n");
		fprintf(stderr, "Usage: %s\n", usage);
		return (-1);
	}

	fname = argv[1];

	if (!read_file(fname))
		return (-1);

	init_mc();
	r = roll();
	assert(r < rec);
	printf("%s: ", r->a);
	scanf("%31s", buf);
	if (mc(r, buf, TRUE))
		printf("Succ.\n");
	else
		printf("Fail. Answer: %s\n", r->b);

	return (TRUE != write_file(fname));
}
