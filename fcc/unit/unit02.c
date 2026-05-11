/*
 * Unit test for io.h
 */
#include <stdio.h>
#include <assert.h>
#include "io.h"
#include "dict.h"

#define TEST1_FNAME "test1.dict"
#define TEST2_FNAME "test2.dict"

void test_init(void)
{
	char lang1[MAXLEN], lang2[MAXLEN];
	char *args1[] = { lang1, lang2 };
	char *args2[] = { lang2, lang1 };
	int i;
	BOOL ar;

	for (i = 0; i < MAXLEN - 1; i++) {
		lang1[i] = 'a' + i - 1;
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

BOOL test_oom(void)
{
	FILE *f;
	BOOL res = FALSE;
	int i;

	f = fopen(TEST1_FNAME, "w");
	for (i = 0; i < NRECS; i++) {
		fprintf(f, "%d b 0 0\n", i);
	}
	fclose(f);
	res = read_file(TEST1_FNAME);
	remove(TEST1_FNAME);

	return (FALSE == res);
}

FILE *make_ill_formatted(void)
{
	FILE *f;

	f = fopen(TEST1_FNAME, "w");
	fprintf(f, ";ZCDI ;TCID ;:itCd  ;:ICD\n");
	fclose(f);

	return (f);
}

BOOL test_wrong_format(void)
{
	BOOL res = FALSE;
	FILE *f;

	f = make_ill_formatted();

	res = (FALSE == read_file(TEST1_FNAME));
	remove(TEST1_FNAME);

	return (res);
}

BOOL test_add_to_wrong(void)
{
	BOOL res = FALSE;
	FILE *f;
	char *args[2] = { "", "" };

	f = make_ill_formatted();

	res = (FALSE == add_record(TEST1_FNAME, 2, args));
	remove(TEST1_FNAME);

	return (res);
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

BOOL test_empty(void)
{
	FILE *f;

	remove(TEST1_FNAME);
	f = fopen(TEST1_FNAME, "w");
	fclose(f);

	return (read_file(TEST1_FNAME));
}

BOOL test_nonexist(void)
{
	char *args[2];
	return (FALSE == add_record("43f0/0", 2, args));
}

BOOL test_read_nonex(void)
{
	return (FALSE == read_file("43f0/0"));
}

BOOL test_write_nonex(void)
{
	return (FALSE == write_file("43f0/0"));
}

BOOL wf, rf, cmp, empty, addrec, oom, wrong_format, ne, add_to_wrong, rne,
    wne;

void test_routine(void)
{
	test_init();
	rf = read_file(TEST1_FNAME);
	wf = write_file(TEST2_FNAME);

	cmp = test_cmp();
	empty = test_empty();
	addrec = test_add_record();
	wrong_format = test_wrong_format();
	add_to_wrong = test_add_to_wrong();
	oom = test_oom();
	ne = test_nonexist();
	rne = test_read_nonex();
	wne = test_write_nonex();

	remove(TEST1_FNAME);
	remove(TEST2_FNAME);
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

	printf("---------------------------------------\n");
	test_res = test_rep_occur("empty", empty) && test_res;
	test_res = test_rep_occur("arec", addrec) && test_res;
	test_res = test_rep_occur("read", rf) && test_res;
	test_res = test_rep_occur("rne", rne) && test_res;
	test_res = test_rep_occur("write", wf) && test_res;
	test_res = test_rep_occur("wne", wne) && test_res;
	test_res = test_rep_occur("cmp", cmp) && test_res;
	test_res = test_rep_occur("wf", wrong_format) && test_res;
	test_res = test_rep_occur("a2w", add_to_wrong) && test_res;
	test_res = test_rep_occur("oom", oom) && test_res;
	test_res = test_rep_occur("ne", ne) && test_res;
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
	printf("\nTest 02:\tI/O\n");
	test_routine();

	return !test_report();
}
