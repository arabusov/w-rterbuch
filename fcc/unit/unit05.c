#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#include "add.h"
#include "bool.h"
#include "dict.h"
#include "io.h"
#include "fccli.h"

#define TEST_NO 5
#define TEST_NAME "FC cli"

BOOL test_npar(void)
{
	char **argv;
	return (-1 == fccli(3, argv));
}

BOOL test_nofile(void)
{
	char *fcc_argv[2] = { "fcc", "0T320/AOEI" };

	return (-1 == fccli(2, fcc_argv));
}

#define TEST_FNAME "test.dict"

BOOL test_one(BOOL correct_answer)
{
	char *argv[4] = { "fcadd", TEST_FNAME, "hello", "Hallo" };
	char *fcc_argv[2] = { "fcc", TEST_FNAME };
	BOOL res;
	pid_t pid;
	int fds[2];

	remove(TEST_FNAME);
	rec = dict;
	if (0 != add(4, argv))
		return (FALSE);
	rec = dict;

	pipe(fds);
	pid = fork();
	if (0 == pid) {
		dup2(fds[1], 1);
		close(fds[0]);
		if (correct_answer)
			printf("Hallo\n");
		else
			printf("ollaH\n");
		exit(0);
	}
	dup2(fds[0], 0);
	close(fds[1]);
	res = fccli(2, fcc_argv);
	remove(TEST_FNAME);

	return (0 == res);
}

BOOL npar, one, wans, nofile;

void test_routine(void)
{
	npar = test_npar();
	one = test_one(TRUE);
	wans = test_one(FALSE);
	nofile = test_nofile();
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
	test_res = test_rep_occur("word", npar) && test_res;
	test_res = test_rep_occur("wrong", wans) && test_res;
	test_res = test_rep_occur("!file", nofile) && test_res;
	printf("---------------------------------------\n");

	if (test_res) {
		printf("Test %02d:\tOk.\n", TEST_NO);
		return (TRUE);
	}
	printf("Test %02d:\tFail.\n", TEST_NO);


	return test_res;
}

int main(void)
{
	printf("\nTest %02d:\t%s.\n", TEST_NO, TEST_NAME);
	test_routine();

	return !test_report();
}
