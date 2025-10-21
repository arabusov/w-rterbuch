/*
 * Flash Cards v0.02
 */
#ifndef _TEST_H_
#define _TEST_H_
#include "dict.h"

extern void
init_test(void);

extern struct record *
roll(void);

extern int
test(struct record *, const char *);

#endif
