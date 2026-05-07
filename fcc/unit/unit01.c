/*
 * Unit test for random.h
 *
 * Checks if yields 1/2 for the average and 1/12 for the variance.
 */

#include <stdio.h>
#include <math.h>

#include "random.h"
#include "bool.h"

#define RANGE 1.f
#define N 100
#define THR 0.01

BOOL test_rep_occur(const char *s, float exp, float obt)
{
	float delta = exp - obt;

        printf("%3s: %1.6f %1.6f %+1.5f",
	       s, exp, obt, delta);
	if (fabs(delta) < THR) {
		printf("     Ok.\n");
		return TRUE;
	}
	printf("   Fail.\n");

	return FALSE;
}

void test_precalc(float *av, float *var)
{
        int i;

        randomize(0);
        for (i = 0; i < N; i++) {
                float x = next_random(RANGE);
                *av += x;
                *var += x*x;
        }
        *av /= (float)N;
        *var = *var/(float)N - *av * *av;
}

BOOL test_report(float av, float var, const float expa, const float expv)
{
	BOOL test_res = TRUE;

	printf("Test 01: RNG\n");
	printf("---------------------------------------\n");
	printf("         exp.     obt.   |diff| Passed?\n");
	printf("---------------------------------------\n");
	test_res = test_rep_occur("avg", expa, av) && test_res;
	test_res = test_rep_occur("var", expv, var) && test_res;
	printf("---------------------------------------\n");

        return test_res;
}

int main(void)
{
        float av, var;
	const float exp_av = RANGE/2., exp_var = RANGE*RANGE/12.;

        test_precalc(&av, &var);

        return !test_report(av, var, exp_av, exp_var);
}
