#include <stdio.h>
#include "bigint.h"

struct timeval 
{
	long tv_sec; 
	long tv_usec; 
};

void test()
{
	init_p("aaa000abcde43243254346abcde1123123abc123424bcdef1212412419980874091ab");
	bigint r, s, t;
	init_str(r, "aaa000abcde43243254346abcde1123123abc123424bcdef1212412419980874091a");
	init_str(s, "12a2313179779878");
	init(t);
	struct timeval t0, t1;
	long timeuse;
	gettimeofday(&t0, NULL);
	for (int i = 0; i < 1; i++)
		mul(t, r, r);//7,15
	gettimeofday(&t1, NULL);
	printf("%s\n", get_str(t));
	timeuse = t1.tv_sec - t0.tv_sec + (t1.tv_usec - t0.tv_usec);
	printf("Time: %lu\n", timeuse);
}

int main()
{
	test();
	return 0;
}
