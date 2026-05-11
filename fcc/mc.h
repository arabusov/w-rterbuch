/*
 * Flash Cards v0.04
 */
#ifndef _TEST_H_
#define _TEST_H_
#include "dict.h"

extern void init_mc(void);

extern struct record *roll(void);

extern int mc(struct record *, const char *, int);

#endif
