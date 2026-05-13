/*
 * Flash Cards v0.04
 */
#include <stdio.h>
#include "io.h"
#include "add.h"
#include "bool.h"

int add(int argc, char **argv)
{
	char *usage = "fcadd DICTIONARY WORD1 WORD2";

	if (argc != 4) {
		fprintf(stderr, "Wrong number of parameters.\n");
		fprintf(stderr, "Usage: %s\n", usage);
		return (-1);
	}
	return (TRUE != add_record(argv[1], argc - 2, argv + 2));
}
