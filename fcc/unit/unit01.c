#include <stdio.h>
#include <math.h>

#include "random.h"

#define RANGE 1.f
#define N 1000

int main(void)
{
        int i;
        float av, sm, sigma;
        randomize(0);
        for (i = 0; i < N; i++) {
                float x = next_random(RANGE);
                av += x;
                sm += x*x;
        }
        av /= (float)N;
        sm = sm/(float)N - av*av;
        sigma = sqrt(sm/(float)N);
        printf("%f +- %f\n", av, sigma);
        printf("%f %f\n", sm, 1./12.);
        return 0;
}
