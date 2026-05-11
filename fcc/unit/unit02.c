/*
 * Unit test for io.h
 */
#include <stdio.h>
#include <assert.h>
#include "io.h"
#include "dict.h"

#define TEST1_FNAME "test1.dict"
#define TEST2_FNAME "test2.dict"

BOOL wf, rf, cmp;

void test_init(void)
{
	char lang1[MAXLEN], lang2[MAXLEN];
	char *args1[] = { lang1, lang2 };
	char *args2[] = { lang2, lang1 };
	int i;
	BOOL ar;

	for (i = 0; i < MAXLEN - 1; i++) {
		lang1[i] = 'a' + i;
		lang2[i] = 'A' + i;
	}

	remove(TEST1_FNAME);
	remove(TEST2_FNAME);

	ar = add_record(TEST1_FNAME, 2, args1);
	assert(ar);
	ar = add_record(TEST1_FNAME, 2, args1);
	assert(!ar);
	ar = add_record(TEST1_FNAME, 2, args2);
	assert(ar);
}

BOOL test_add_record(void)
{
	char *args[3];
	return (FALSE == add_record(TEST1_FNAME, 3, args));
}

BOOL test_cmp(void)
{
	BOOL res = TRUE;
	FILE *f1, *f2;
	int pos = 0, c1, c2;

	f1 = fopen(TEST1_FNAME, "r");
	f2 = fopen(TEST2_FNAME, "r");

	do {
		pos++;
		c1 = fgetc(f1);
		c2 = fgetc(f2);
		if (c1 != c2) {
			fprintf(stderr, "Unmatched chars @%d: %c %c\n",
				pos, c1, c2);
			res = FALSE;
			goto cmp_end;
		}
	} while (!feof(f1) && !feof(f2));

	if (!feof(f1) || !feof(f2)) {
		res = FALSE;
		goto cmp_end;
	}

      cmp_end:
	fclose(f1);
	fclose(f2);
	return (res);
}

void test_routine(void)
{
	test_init();
	rf = read_file(TEST1_FNAME);
	wf = write_file(TEST2_FNAME);

	cmp = test_cmp();

	assert(remove(TEST1_FNAME) == 0);
	assert(remove(TEST2_FNAME) == 0);
}

BOOL test_empty(void)
{
	FILE *f;

	remove(TEST1_FNAME);
	f = fopen(TEST1_FNAME, "w");
	fclose(f);

	return (read_file(TEST1_FNAME));
}

BOOL test_rep_occur(const char *s, BOOL res)
{
	printf("%5s:                         ", s);
	if (res) {
		printf("     Ok.\n");
		return TRUE;
	}
	printf("   Fail.\n");
	return (FALSE);
}

BOOL test_report(void)
{
	BOOL test_res = TRUE;

	printf("Test 02:\tI/O\n");
	printf("---------------------------------------\n");
	test_res = test_rep_occur("empty", test_empty()) && test_res;
	test_res = test_rep_occur("arec", test_add_record()) && test_res;
	test_res = test_rep_occur("read", rf) && test_res;
	test_res = test_rep_occur("write", wf) && test_res;
	test_res = test_rep_occur("cmp", cmp) && test_res;
	printf("---------------------------------------\n");

	remove(TEST1_FNAME);
	remove(TEST2_FNAME);

	if (test_res) {
		printf("Test 02:\tOk.\n");
		return (TRUE);
	}
	printf("Test 02:\tFail.\n");

	return (FALSE);
}

int main(void)
{
	test_routine();

	return !test_report();
}
