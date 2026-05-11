/*
 * Flash Cards v0.04
 *
 * Test facility for flash cards
 */
#include <string.h>
#include <time.h>
#include "random.h"
#include "dict.h"
#include "io.h"

float sum_fail;

static float prob(struct record *r)
{
	if (r->all >= r->succ) {
		return (r->all - r->succ + 1.) / (r->all + 1.);
	}
	r->succ = r->all;
	return 1. / (r->all + 1.);
}

extern void init_mc(void)
{
	struct record *r;
	time_t unix_time;
	/* init rng */
	time(&unix_time);
	randomize(unix_time);
	/* calc number of fails and shift by one */
	sum_fail = 0.;		/* allows us to reinit the MC engine in one session */
	for (r = dict; r <= rec; r++) {
		sum_fail += prob(r);
	}
}

extern struct record *roll(void)
{
	struct record *r;
	float dice = next_random(sum_fail);
	float pos = 0.;
	for (r = dict; r <= rec; r++) {
		pos += prob(r);
		if (dice < pos)
			break;
	}
	return r;
}

extern int mc(struct record *r, const char *buf, int record_result)
{
	int res = 0;
	if (0 == strcmp(buf, r->b)) {
		res = 1;
		if (record_result)
			r->succ++;
	}
	if (record_result)
		r->all++;
	return (res);
}
