/*
 * Flash Cards v0.03
 *
 * Simple scanner and parser for flash cards to support DICT format
 */
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include "dict.h"
#include "io.h"

struct record dict[NRECS];
struct record *rec = dict;

static int
read_record(struct record *rec, FILE *f)
{
        char *a = rec->a;
        char *b = rec->b;
        int *all = &(rec->all);
        int *succ = &(rec->succ);
        return(fscanf(f, "%s %s %d %d",
                        a, b, all, succ));
}

static int
read_dict(FILE *f)
{
        if (f == NULL)
                return(0);
        while(!feof(f)) {
                int res = read_record(rec, f);
                if (res == EOF) break;
                if (res != 4) {
                        fprintf(stderr, "%td [line]: %d read",
                                        rec-dict + 1, res);
                        return(0);
                }
                rec++;
                if (rec-dict >= (ptrdiff_t)MAXREC) {
                        fprintf(stderr, "Out of memory: ");
                        return(0);
                }
        }
        if (rec == dict) {
                fprintf(stderr, "Empty dict\n");
                return(0);
        }
        rec--;
        return(1);
}

static int
save_dict(FILE *f)
{
        struct record *r;
        int wres = 0;

        if (f == NULL) {
                fprintf(stderr, "Write error\n");
                return(0);
        }
        for (r = dict; r <= rec; r++) {
                wres = fprintf(f, "%s%c%s%c%d%c%d%s", r->a, DELIM, r->b,
                                DELIM, r->all, DELIM, r->succ, EOL);
                if (wres < 8) { /* number of transmitted characters */
                	fprintf(stderr, "I/O error saving %s\n", r->a);
                }
        }
        return(1);
}

static int
present(char *name)
{
	struct record *r;

	for (r = dict; r <= rec; r++) {
		if (0 == strcmp(r->a, name)) {
			fprintf(stderr,
			"Word \"%s\" is already present\n", name);
			return(1);
		}
	}
	return(0);
}

extern int
add_record(char *fname, int argc, char **argv)
{
        FILE *f;

        if (argc != 2)
                return(0);

        f = fopen(fname, "r");
        if (f == NULL) {
                f = fopen(fname, "w");
                fprintf(f, "%s%c%s%c0%c0%s", argv[0],
                                DELIM, argv[1], DELIM, DELIM, EOL);
                fclose(f);
                return(1);
        }
        if (read_dict(f)) {
                fclose(f);
                if (rec-dict < (ptrdiff_t)MAXREC) {
                	if (present(argv[0])) {
                		return(0);
                	}
                        rec++;
                        memset(rec->a, '\0', MAXLEN); /* caution */
                        memset(rec->b, '\0', MAXLEN);
                        strcpy(rec->a, argv[0]);
                        strcpy(rec->b, argv[1]);
                        rec->all = rec->succ = 0;
                } else {
                        fprintf(stderr, "Not enough memory or RAM\n");
                        return(0);
                }
                f = fopen(fname, "w");
                if (save_dict(f) == 0) {
                        fprintf(stderr, "File %s is not written\n",
                                        fname);
                        return(0);
                }
                fclose(f);
                return(1);
        }
        fprintf(stderr, " Read error.\n");
        return(0);
}

extern int
read_file(const char *fname)
{
	FILE *f;
	f = fopen(fname, "r");
        if (!read_dict(f)) {
                fprintf(stderr, "Bad format in %s file\n", fname);
                return(0);
        }
        return(1);
}

extern int
write_file(const char *fname)
{
	FILE *f;
        f = fopen(fname, "w");
        if (0 == save_dict(f)) {
        	fprintf(stderr, "I/O error while saving dictionary\n");
        	return(0);
        }
        fclose(f);
	return(1);
}
