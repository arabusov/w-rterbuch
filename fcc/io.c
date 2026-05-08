/*
 * Flash Cards v0.04
 *
 * Simple scanner and parser for flash cards to support DICT format
 */
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "bool.h"
#include "dict.h"
#include "io.h"

struct record dict[NRECS];
struct record *rec = dict;

static BOOL read_record(struct record *rec, FILE *f)
{
	char *a = rec->a;
	char *b = rec->b;
	int *all = &(rec->all);
	int *succ = &(rec->succ);
	return (fscanf(f, "%s %s %d %d", a, b, all, succ));
}

static BOOL read_dict(FILE *f)
{
	if (f == NULL) {
		fprintf(stderr, "Input file couldn't be opened\n");
		return (FALSE);
	}
	while (!feof(f)) {
		int res = read_record(rec, f);
		if (res == EOF)
			break;
		if (res != 4) {
			fprintf(stderr, "%ld [line]: %d read",
				rec - dict + 1, res);
			return (FALSE);
		}
		rec++;
		if (rec - dict >= (ptrdiff_t) MAXREC) {
			fprintf(stderr, "Out of memory: ");
			return (FALSE);
		}
	}
	if (rec == dict) {
		fprintf(stderr, "Empty dict\n");
		return (FALSE);
	}
	rec--;
	return (TRUE);
}

static BOOL save_dict(FILE *f)
{
	struct record *r;
	int wres = 0;

	if (f == NULL) {
		fprintf(stderr, "Write error\n");
		return (FALSE);
	}
	for (r = dict; r <= rec; r++) {
		wres = fprintf(f, "%s%c%s%c%d%c%d%s", r->a, DELIM, r->b,
			       DELIM, r->all, DELIM, r->succ, EOL);
		if (wres < 8) {	/* number of transmitted characters */
			fprintf(stderr, "I/O error saving %s\n", r->a);
		}
	}
	return (TRUE);
}

static BOOL present(char *name)
{
	struct record *r;

	for (r = dict; r <= rec; r++) {
		if (0 == strcmp(r->a, name)) {
			fprintf(stderr,
				"Word \"%s\" is already present\n", name);
			return (TRUE);
		}
	}
	return (FALSE);
}

extern BOOL add_record(char *fname, int argc, char **argv)
{
	FILE *f;

	if (argc != 2)
		return (FALSE);

	f = fopen(fname, "r");
	if (f == NULL) {
		f = fopen(fname, "w");
		fprintf(f, "%s%c%s%c0%c0%s", argv[0],
			DELIM, argv[1], DELIM, DELIM, EOL);
		fclose(f);
		return (TRUE);
	}
	if (read_dict(f)) {
		fclose(f);
		if (rec - dict < (ptrdiff_t) MAXREC) {
			if (present(argv[0])) {
				return (FALSE);
			}
			rec++;
			memset(rec->a, '\0', MAXLEN);	/* caution */
			memset(rec->b, '\0', MAXLEN);
			strcpy(rec->a, argv[0]);
			strcpy(rec->b, argv[1]);
			rec->all = rec->succ = 0;
		} else {
			fprintf(stderr, "Not enough memory or RAM\n");
			return (FALSE);
		}
		f = fopen(fname, "w");
		if (save_dict(f) == 0) {
			fprintf(stderr, "File %s is not written\n", fname);
			return (FALSE);
		}
		fclose(f);
		return (TRUE);
	}
	fprintf(stderr, " Read error.\n");
	return (FALSE);
}

extern BOOL read_file(const char *fname)
{
	FILE *f;
	f = fopen(fname, "r");
	if (NULL == f) {
		fprintf(stderr, "Cannot open %s\n", fname);
		return (FALSE);
	}
	if (!read_dict(f)) {
		fprintf(stderr, "Bad format in %s file\n", fname);
		return (FALSE);
	}
	return (TRUE);
}

extern BOOL write_file(const char *fname)
{
	FILE *f;
	f = fopen(fname, "w");
	if (0 == save_dict(f)) {
		fprintf(stderr, "I/O error while saving dictionary\n");
		return (FALSE);
	}
	fclose(f);
	return (TRUE);
}
