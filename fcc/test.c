/*
 * Flash Cards v0.04
 *
 * Test facility for flash cards
 */
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dict.h"
#include "io.h"

float sum_fail;

static float
prob(struct record *r)
{
	if (r->all >= r->succ) {
		return (r->all - r->succ + 1.)/
			(r->all + 1.);
	}
	r->succ = r->all;
	return 1./(r->all + 1.);
}

void
init_test(void)
{
	struct record *r;
	time_t unix_time;
	/* init rng */
	time(&unix_time);
	srand(unix_time);
	/* calc number of fails and shift by one */
	sum_fail = 0.; /* allows us to reinit the test in one session */
	for (r = dict; r <= rec; r++) {
		sum_fail += prob(r);
	}
}

struct record *
roll(void)
{
	struct record *r;
	float dice = (float)rand()/(float)RAND_MAX*sum_fail;
	float pos = 0.;
	for (r = dict; r <= rec; r++) {
		pos += prob(r);
		if (dice < pos)
			break;
	}
	return r;
}

int
test(struct record *r, const char *buf)
{
	int res = 0;
	if (0 == strcmp(buf, r->b)) {
		res = 1;
		r->succ ++;
	}
	r->all++;
	return(res);
}
