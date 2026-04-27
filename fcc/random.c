#include <assert.h>

#include "random.h"

static unsigned index = 0;

#define LOG2_N_RTABLE 8u
#define N_RTABLE (1u<<LOG2_N_RTABLE)
#define N_RTABLE_MASK (N_RTABLE-1)

static unsigned char rtable[N_RTABLE] = {

};

#define RTABLE_MAXVAL

extern void
randomize(int seed)
{
        index = seed & N_RTABLE_MASK;
}

extern float
next_random(float scale)
{
        index = (index + 1) & N_RTABLE_MASK;
        assert(rtable[index] <= RTABLE_MAXVAL);
        return rtable[index]/(float)RTABLE_MAXVAL*scale;
}
