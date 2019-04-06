#include <stdio.h>
#include "bigint.h"
//#include "rdtsc.h"
#include <time.h>
#include <stdlib.h>

//void test()
//{
//	init_p("aaa000abcde432431bbbcccdddeeefff");
//	bigint x, y, t;
//	init_str(x, "aaa000abcde432431bbbcccddd");
//	init_str(y, "12a2313179779878000");
//	init(t);
//	int64 t0, t1;
//	t0 = rdtsc();
//	power(t, x, y);
//	t1 = rdtsc();
//	printf("%s\n", get_str(t));
//	printf("Time: %llu\n", t1 - t0);
//}

int main()
{
	init_p("cf64d76b4d94dc2b");
	bigint x, y, t;
	init_str(x, "3f0dc1184192264f");
	init_str(y, "ce556f4f5a2a7e08");
	power(x, x, y);
	printf("%s\n", get_str(x));
	return 0;
}

void rand_str(char * hex, int l)
{
	int j, k;
	while (!(k = rand() % 16));
	hex[0] = k < 10 ? k + '0' : k - 10 + 'a';
	for (j = 1; j < l; j++)
	{
		k = rand() % 16;
		hex[j] = k < 10 ? k + '0' : k - 10 + 'a';
	}
	hex[l] = 0;
}

//int diff(bigint x, mpz_t y)
//{
//	if (x->size != y->_mp_size)
//		return 1;
//	else
//		for (int i = 0; i < x->size; i++)
//			if (x->digits[i] != y->_mp_d[i])
//				return 1;
//	return 0;
//}
//
//void testing()
//{
//	int len = 64;
//	int i, j, k, l, m;
//	bigint p, a[10], x;
//	mpz_t q, b[10], y;
//	FILE* output = fopen("/root/projects/C/output.txt", "w+");
//	srand(time(NULL));
//	l = 1 + rand() % len;
//	char* hex = (char*)calloc(l + 1, 1);
//	rand_str(hex, l);
//	mpz_init_set_str(q, hex, 16);
//	init_p(hex);
//	printf("%s, %s", hex, get_str(p));
//	for (i = 0; i < 10; )
//	{
//		rand_str(hex, 1 + rand() % l);
//		mpz_init_set_str(b[i], hex, 16);
//		if (mpz_cmp(q, b[i]) <= 0)
//			continue;
//		init_str(a[i], hex);
//		i++;
//	}
//	for (i = 0; i < 10; i++)
//		for (j = 0; j < 10; j++)
//		{
//			add(x, a[i], a[j]);
//			mpz_add(y, b[i], b[j]);
//			mpz_mod(y, y, q);
//			if (diff(x, y))
//			{
//				fputs(get_str(a[i]), output);
//				fputc(',', output);
//				fputs(get_str(a[j]), output);
//				fputc('\n', output);
//			}
//		}
//	free(hex);
//}
