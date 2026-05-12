#include <stdio.h>

#include "add.h"
#include "bool.h"

BOOL test_npar(void)
{
	char **argv;
	return (-1 == add(2, argv));
}

#define TEST_FNAME "test.dict"

BOOL test_add_one(void)
{
	char *argv[] = { "fcadd", TEST_FNAME, "hello", "Hallo" };
	BOOL res;

	if (0 != add(4, argv))
		return (FALSE);
	res = read_file(TEST_FNAME);
	remove(TEST_FNAME);

	return (res);
}

BOOL npar, add_one;

void test_routine(void)
{
	npar = test_npar();
	add_one = test_add_one();
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
	test_res = test_rep_occur("npar", npar) && test_res;
	printf("---------------------------------------\n");

	if (test_res) {
		printf("Test 04:\tOk.\n");
		return (TRUE);
	}
	printf("Test 04:\tFail.\n");


	return test_res;
}

int main(void)
{
	printf("\nTest 04:\tfcadd cli.\n");
	test_routine();

	return !test_report();
}
