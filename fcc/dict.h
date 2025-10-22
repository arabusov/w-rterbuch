/*
 * Flash Cards v0.04
 *
 * dict.h: a record structure for flash cards
 */
#ifndef __DICT_H__
#define __DICT_H__

#define MAXLEN          32
#define DELIM           ' '

struct record
{
        char a[MAXLEN], b[MAXLEN];
        int all, succ;
        unsigned time;
};

#endif
