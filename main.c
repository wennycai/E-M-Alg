#include <stdio.h>
#include "bigint.h"
#include "rdtsc.h"

void test()
{
	init_p("aaa000abcde432431bbbcccdddeeefffaaa000abcde432431bbbcccdddeeefffaaa000abcde432431bbbcccdddeeefffaaa000abcde432431bbbcccdddeeefff");
	bigint x, y, t;
	init_str(x, "aaa000abcde432431bbbcccddd");
	init_str(y, "12a2313179779878000");
	init(t);
	int64 t0, t1;
	t0 = rdtsc();
	power_b(t,x,y);
	t1 = rdtsc();
	printf("%s\n", get_str(t));
	printf("Time: %llu\n", t1 - t0);
}

int main()
{
	test();
	return 0;
}
