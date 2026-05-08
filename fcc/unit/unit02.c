/*
 * Unit test for io.h
 */
#include <stdio.h>
#include "io.h"

#define TEST_FNAME "test.dict"

int main(void)
{
	char *args[] = { "a", "b" };
	BOOL wf, rf;
	int rmf;

	printf("Test 02:\tI/O\n");
	wf = add_record(TEST_FNAME, 2, args);
	rf = read_file(TEST_FNAME);
	rmf = remove(TEST_FNAME);

	if (wf && rf && (0 == rmf)) {
		printf("Test 02:\tOk.\n");
		return 0;
	} else {
		printf("Test 02:\tFail.\n");
		return 1;
	}
}
