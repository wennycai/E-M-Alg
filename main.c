#include <stdio.h>
#include "bigint.h"
#include "rdtsc.h"

void test()
{
	init_p("aaa000abcde432431bbbcccdddeeefff");
	r_size = p->size;
	bigint r, s, t;
	init_str(r, "aaa000abcde432431bbbcccddd");
	init_str(s, "12a2313179779878");
	init(t);
	int64 t0, t1;
	t0 = rdtsc();
	mul(t, s, r);
	t1 = rdtsc();
	printf("%s\n", get_str(t));
	printf("Time: %llu\n", t1 - t0);
}

int main()
{
	test();
	return 0;
}
