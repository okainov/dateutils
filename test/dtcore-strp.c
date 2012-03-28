#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include "dt-core.h"

#define CHECK(pred, args...)			\
	if (pred) {				\
		fprintf(stderr, args);		\
		res = 1;			\
	}

static int
test_d_only_no_fmt(void)
{
	static const char str[] = "2012-03-28";
	struct dt_dt_s d;
	int res = 0;

	/* 2012-03-28 (using no format) */
	fprintf(stderr, "testing %s ...\n", str);
	d = dt_strpdt(str, NULL, NULL);

	CHECK(d.typ != DT_SANDWICH_D_ONLY(DT_YMD),
	      "  TYPE DIFFERS %u ... should be %u\n",
	      (unsigned int)d.typ,
	      (unsigned int)DT_SANDWICH_D_ONLY(DT_YMD));
	CHECK(d.t.u,
	      "  TIME COMPONENT NOT NAUGHT %" PRIu64 "\n",
	      (uint64_t)d.t.u);
	CHECK(d.dur, "  DURATION BIT SET\n");
	CHECK(d.neg, "  NEGATED BIT SET\n");

	CHECK(d.d.ymd.y != 2012,
	      "  YEAR %u ... should be 2012\n",
	      (unsigned int)d.d.ymd.y);
	CHECK(d.d.ymd.m != 3,
	      "  MONTH %u ... should be 3\n",
	      (unsigned int)d.d.ymd.m);
	CHECK(d.d.ymd.d != 28,
	      "  DAY %u ... should be 28\n",
	      (unsigned int)d.d.ymd.d);
	/* make sure the padding leaves no garbage */
	CHECK(d.d.ymd.u & ~0x1fffff,
	      "  PADDING NOT NAUGHT %u\n",
	      (unsigned int)(d.d.ymd.u & ~0x1fffff));
	return res;
}

static int
test_t_only_no_fmt(void)
{
	static const char str[] = "12:34:56";
	struct dt_dt_s d;
	int res = 0;

	/* 12:34:56 (using no format) */
	fprintf(stderr, "testing %s ...\n", str);
	d = dt_strpdt(str, NULL, NULL);

	CHECK(d.typ != DT_SANDWICH_T_ONLY(DT_HMS),
	      "  TYPE DIFFERS %u ... should be %u\n",
	      (unsigned int)d.typ,
	      (unsigned int)DT_SANDWICH_T_ONLY(DT_HMS));
	CHECK(d.t.typ != DT_HMS,
	      "  TIME TYPE DIFFERS %u ... should be %u\n",
	      (unsigned int)d.t.typ,
	      (unsigned int)DT_HMS);
	CHECK(d.d.u,
	      "  DATE COMPONENT NOT NAUGHT %" PRIu64 "\n",
	      (uint64_t)d.d.u);
	CHECK(d.dur, "  DURATION BIT SET\n");
	CHECK(d.neg, "  NEGATED BIT SET\n");
	CHECK(d.t.hms.h != 12,
		"  HOUR %u ... should be 12\n",
	      (unsigned int)d.t.hms.h);
	CHECK(d.t.hms.m != 34,
	      "  MINUTE %u ... should be 34\n",
	      (unsigned int)d.t.hms.m);
	CHECK(d.t.hms.s != 56,
	      "  SECOND %u ... should be 56\n",
	      (unsigned int)d.t.hms.s);
	CHECK(d.t.hms.ns != 0,
	      "  NANOSECOND %u ... should be 0\n",
	      (unsigned int)d.t.hms.ns);
	/* make sure the padding leaves no garbage */
	CHECK(d.t.hms.u & ~0x1f3f3f3fffffff,
	      "  PADDING NOT NAUGHT %u\n",
	      (unsigned int)(d.t.hms.u & ~0x1f3f3f3fffffff));
	return res;
}

int
main(void)
{
	int res = 0;

	if (test_d_only_no_fmt() != 0) {
		res = 1;
	}

	if (test_t_only_no_fmt() != 0) {
		res = 1;
	}

	return res;
}

/* dtcore-strpd.c ends here */
