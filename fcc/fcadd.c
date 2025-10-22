/*
 * Flash Cards v0.04
 */
#include "io.h"
#include <stdio.h>

char usage[] = "add DICTIONARY WORD1 WORD2";

int
main(int argc, char **argv)
{
        if (argc != 4) {
                fprintf(stderr, "Wrong number of parameters.\n");
                fprintf(stderr, "Usage: %s\n", usage);
                return(-1);
        }
        add_record(argv[1], argc - 2, argv + 2);
        return(0);
}
