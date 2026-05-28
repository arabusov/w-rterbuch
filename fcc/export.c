/*
 * Flash Cards v0.04
 */
#include <stdio.h>

#include "bool.h"
#include "dict.h"
#include "export.h"
#include "io.h"

static void trim_word(const char *word)
{
}

const char *header =
"#separator:Semicolon\n"
"#html:false\n"
"#columns:LangA;LangB";

static BOOL fc2anki(const char *fname)
{
	struct record *ptr;

	if (!read_file(fname))
		return (FALSE);
	puts(header);
	for (ptr = dict; ptr < rec; ptr++) {
		printf("%s;%s\n", ptr->a, ptr->b);
	}
	return (TRUE);
}

int export(int argc, char **argv)
{
	char *usage = "fc2anki DICTIONARY";

	if (argc != 2) {
		fprintf(stderr, "Wrong number of parameters.\n");
		fprintf(stderr, "Usage: %s\n", usage);
		return (-1);
	}
	return (TRUE != fc2anki(argv[1]));
}
