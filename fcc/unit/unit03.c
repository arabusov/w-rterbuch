/*
 * Unit test for test.h
 *
 */
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include "mc.h"
#include "io.h"
#include "bool.h"

void test_init(void)
{
	char *lang1 = "hello", *lang2 = "Hallo";
	char *args1[] = { lang1, lang2 };
	char *args2[] = { lang2, lang1 };

	rec = dict;

	strcpy(rec->a, args1[0]);
	strcpy(rec->b, args1[1]);
	rec->all = rec->succ = 0;
	rec++;

	strcpy(rec->a, args2[0]);
	strcpy(rec->b, args2[1]);
	rec->all = rec->succ = 0;
	rec++;
}

BOOL odd_even_test;

BOOL test_all_correct(BOOL record)
{
	struct record *r;
	int i;
	unsigned flags = 0, pos;
	int n_odd = 0, n_even = 0;
	float mu;

	test_init();
	init_mc();
	for (i = 0; i < 256; i++) {
		r = roll();
		pos = (unsigned) (r - dict);
		if (pos & 1)
			n_odd++;
		else
			n_even++;
		if (pos >= 2) {
			printf("Error at %d: pos = %u\n", i, pos);
			return (FALSE);
		}
		if (!mc(r, r->b, record))
			return (FALSE);
		flags |= 1 << pos;
	}
	mu = (n_odd - n_even) / sqrt(n_odd + n_even);
	printf("mu = %f\n", mu);
	odd_even_test = (fabs(mu) < 5.);
	return (flags == 0x3);
}

BOOL test_rep_occur(const char *s, BOOL res)
{
	printf("%5s:                         ", s);
	if (res) {
		printf("     Ok.\n");
		return TRUE;
	}
	printf("   Fail.\n");

	return FALSE;
}

BOOL all_correct, record_res;

void test_routine(void)
{
	all_correct = test_all_correct(FALSE);
	record_res = test_all_correct(TRUE);
}

BOOL test_report(void)
{
	BOOL test_res = TRUE;

	printf("---------------------------------------\n");
	test_res = test_rep_occur("roll", all_correct) && test_res;
	test_res = test_rep_occur("o/e", odd_even_test) && test_res;
	test_res = test_rep_occur("rec", record_res) && test_res;
	printf("---------------------------------------\n");

	if (test_res) {
		printf("Test 03:\tOk.\n");
		return (TRUE);
	}
	printf("Test 03:\tFail.\n");


	return test_res;
}

int main(void)
{
	printf("\nTest 03:\tMC engine.\n");
	test_routine();

	return !test_report();
}
