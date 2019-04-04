#include <stdio.h>
#include "bigint.h"
#include "rdtsc.h"
#include <time.h>
#include <stdlib.h>

void test()
{
	init_p("aaa000abcde432431bbbcccdddeeefff");
	bigint x, y, t;
	init_str(x, "aaa000abcde432431bbbcccddd");
	init_str(y, "12a2313179779878000");
	init(t);
	int64 t0, t1;
	t0 = rdtsc();
	power(t, x, y);
	t1 = rdtsc();
	printf("%s\n", get_str(t));
	printf("Time: %llu\n", t1 - t0);
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

int main()
{
	init_p("65f19c04cfba45a0e39a8719c");
	bigint x, y, t;
	init_str(x, "42e4a6b04baf73c444601480a");
	init_str(y, "51b7d2c57e55742ecab880a89");
	char b[128];
	int16 c = bin(b, x);
	printf("%d\n", c);
	for (int i = 0; i < c; i++)
		printf("%d", b[i]);
	return 0;
}
