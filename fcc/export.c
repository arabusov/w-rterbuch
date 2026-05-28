/*
 * Flash Cards v0.04
 */
#include <libgen.h>
#include <stdio.h>
#include <string.h>

#include "bool.h"
#include "dict.h"
#include "export.h"
#include "io.h"

static void trim(const char *word, FILE *ofile)
{
	int i;
	for (i = 0; (i < strlen(word)) && (i < MAXLEN); i++) {
		switch (word[i]) {
		case '_':
			fputc(' ', ofile);
			break;
		default:
			fputc(word[i], ofile);
			break;
		}
	}
}

const char *header =
    "#separator:Semicolon\n" "#html:false\n" "#columns:LangA;LangB\n";

void write2anki(FILE *ofile)
{
	struct record *ptr;

	fputs(header, ofile);
	for (ptr = dict; ptr < rec; ptr++) {
		trim(ptr->a, ofile);
		fputc(';', ofile);
		trim(ptr->b, ofile);
		fputc('\n', ofile);
	}
}

static void rename_fname(char *oname, const char *iname)
{
	int i;

	for (i = 0; (i < strlen(iname))
	     && (i < FNAME_MAX)
	     && (iname[i] != '.'); i++) {
		oname[i] = iname[i];
	}
	oname[i++] = '.';
	oname[i++] = 't';
	oname[i++] = 'x';
	oname[i++] = 't';
	oname[i] = '\0';
}

static BOOL fc2anki(char *fname)
{
	FILE *ofile;
	char oname[FNAME_MAX + 4 + 1];

	/* Input: open file and read */
	if (!read_file(fname))
		return (FALSE);

	/* Output: open file */
	rename_fname(oname, basename(fname));
	ofile = fopen(oname, "w");
	if (NULL == ofile) {
		fprintf(stderr, "Cannot create %s file\n", oname);
		return (FALSE);
	}

	/* Write to file */
	write2anki(ofile);

	/* Close output file and exit */
	fclose(ofile);
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
