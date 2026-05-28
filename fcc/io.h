/*
 * Flash Cards v0.04
 */
#ifndef __IO_H__
#define __IO_H__

#include "dict.h"
#ifdef __MSDOS__
#define FNAME_MAX 8		/* without extension */
#define EOL "\r\n"
#else
#define FNAME_MAX 11		/* without extension */
#define EOL "\n"
#endif
extern struct record dict[];
extern struct record *rec;
#define NRECS (65536/4/sizeof(struct record))
#define MAXREC (NRECS-1)

#include "bool.h"

extern BOOL add_record(char *fname, int argc, char **argv);
extern BOOL write_file(const char *fname);
extern BOOL read_file(const char *fname);

#endif				/* __IO_H__ */
