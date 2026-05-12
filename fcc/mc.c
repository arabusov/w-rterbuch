/*
 * Flash Cards v0.04
 *
 * The Monte-Carlo engine for the flash cards
 */
#include <assert.h>
#include <string.h>
#include <time.h>
#include "random.h"
#include "dict.h"
#include "io.h"

float sum_fail;

static float prob(struct record *r)
{
	assert(r->all >= r->succ);
	return (r->all - r->succ + 1.) / (r->all + 1.);
}

static void renorm(void)
{
	struct record *r;
	/* allows us to reinit the MC engine in one session */
	sum_fail = 0.;
	for (r = dict; r < rec; r++) {
		sum_fail += prob(r);
	}
}

extern void init_mc(void)
{
	time_t unix_time;
	/* init rng */
	time(&unix_time);
	randomize(unix_time);
	/* calc number of fails and shift by one */
	renorm();
}

extern struct record *roll(void)
{
	struct record *r;
	float dice = next_random(sum_fail);
	float pos = 0.;
	for (r = dict; r < rec; r++) {
		pos += prob(r);
		if (dice < pos)
			break;
	}
	assert(r < rec);
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
	if (record_result) {
		r->all++;
		renorm();
	}
	return (res);
}
