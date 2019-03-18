#include <stdio.h>
#include<stdlib.h>
#include "bigint.h"

void test()
{
	init_p("aaa000abcde43243254346abcde1");
	bigint r, s, t;
	init_str(r, "aaa000abc6876857658de0");
	init_str(s, "12a23131");
	init(t);
	add(t, r, r);
	printf("%s\n", get_str(t));
}

int main()
{
	test();
	return 0;
}