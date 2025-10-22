/*
 * Flash Cards v0.04
 */
#ifndef __IO_H__
#define __IO_H__

#include "dict.h"
#ifdef __MSDOS__
#define EOL "\r\n"
#else
#define EOL "\n"
#endif
extern struct record dict[];
extern struct record *rec;
#define NRECS (65536/4/sizeof(struct record))
#define MAXREC (NRECS-1)

#include <stdio.h>

extern int add_record(char *fname, int argc, char **argv);
extern int write_file(const char *fname);
extern int read_file(const char *fname);

#endif /* __IO_H__ */
