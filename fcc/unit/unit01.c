#include <stdio.h>
#include <math.h>

#include "random.h"
#include "bool.h"

#define RANGE 1.f
#define N 100
#define THR 0.01

BOOL print_test(const char *s, float exp, float obt)
{
	float delta = fabs(exp - obt);
        printf("%3s: %1.6f %1.6f %+1.5f",
	       s, exp, obt, delta);
	if (delta < THR) {
		printf("     Ok.\n");
		return TRUE;
	}
	printf("   Fail.\n");
	return FALSE;
}

int main(void)
{
        int i;
        float av, sm;
	const float exp_av = RANGE/2., exp_sm = RANGE*RANGE/12.;
	BOOL test_res = TRUE;
        randomize(0);
        for (i = 0; i < N; i++) {
                float x = next_random(RANGE);
                av += x;
                sm += x*x;
        }
        av /= (float)N;
        sm = sm/(float)N - av*av;
	printf("Test 01: RNG\n");
	printf("-------\n");
	printf("         exp.     obt.   |diff| Passed?\n");
	test_res = print_test("avg", exp_av, av) && test_res;
	test_res = print_test("var", exp_sm, sm) && test_res;
        return !test_res;
}
