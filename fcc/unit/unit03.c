/*
 * Unit test for test.h
 *
 */
#include <assert.h>
#include <stdio.h>
#include <math.h>

#include "mc.h"
#include "io.h"
#include "bool.h"

#define TEST_FNAME "test.dict"

void test_init(void)
{
	char *lang1 = "hello", *lang2 = "Hallo";
	char *args1[] = { lang1, lang2 };
	char *args2[] = { lang2, lang1 };

	remove(TEST_FNAME);
	assert(add_record(TEST_FNAME, 2, args1));
	assert(add_record(TEST_FNAME, 2, args2));
	remove(TEST_FNAME);
}

BOOL test_routine(void)
{
	struct record *r;

	test_init();
	init_mc();
	r = roll();
	return (mc(r, r->b, TRUE));
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


BOOL test_report(void)
{
	BOOL test_res = TRUE;

	printf("---------------------------------------\n");
	test_res = test_rep_occur("roll", test_routine()) && test_res;
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
