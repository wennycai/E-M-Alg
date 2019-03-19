#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include "bigint.h"

void test()
{
	init_p("aaa000abcde43243254346abcde1");
	bigint r, s, t;
	init_str(r, "aaa000abc6876857658de0");
	init_str(s, "12a2313179779878");
	init(t);
	mul(t, s, r);
	printf("%s\n", get_str(r));
}

int main()
{
	clock_t t = clock();
	test();
	printf("%d\n", clock() - t);
	return 0;
}