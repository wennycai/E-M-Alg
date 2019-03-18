#include<stdlib.h>
#include<stdio.h>
#include "bigint.h"

void init(bigint r)
{
	r->size = 1;
	r->digits = (int64*)malloc(8 * p->size);
}

int init_p(const char* str)
{
	int count = 0, i = 0, j = 0;
	while (*str)
		count++, str++;
	p->size = (count >> 4) + 1;
	p->digits = (int64*)malloc(8 * p->size);
	for (int k = 0; k < count; i++)
		for (j = 0; j < 16 && k < count; k++)
			if (*(--str) <= '9' && *str >= '0')
				p->digits[i] += (int64)(*str - '0') << (j++ << 2);
			else if (*str <= 'F' && *str >= 'A')
				p->digits[i] += (int64)(*str - 'A' + 10) << (j++ << 2);
			else if (*str <= 'f' && *str >= 'a')
				p->digits[i] += (int64)(*str - 'a' + 10) << (j++ << 2);
			else
				return 0;
	return p->size;
}

int init_str(bigint r, const char* str)
{
	int count = 0, i = 0, j = 0;
	while (*str)
		count++, str++;
	r->digits = (int64*)malloc(8 * p->size);
	for (int k = 0; k < count; i++)
		for (j = 0; j < 16 && k < count; k++)
			if (*(--str) <= '9' && *str >= '0')
				r->digits[i] += (int64)(*str - '0') << (j++ << 2);
			else if (*str <= 'F' && *str >= 'A')
				r->digits[i] += (int64)(*str - 'A' + 10) << (j++ << 2);
			else if (*str <= 'f' && *str >= 'a')
				r->digits[i] += (int64)(*str - 'a' + 10) << (j++ << 2);
			else
				return 0;
	return (r->size = i);
}

void set(bigint r, const bigint x)
{
	for (int i = 0; i < x->size; i++)
		r->digits[i] = x->digits[i];
	r->size = x->size;
}

void clear(bigint r)
{
	r->size = 0;
	free(r->digits);
}

char* get_str(const bigint x)
{
	char* r = (char*)calloc((x->size << 4) + 1, 1);
	char hex[16] = "0123456789abcdef";
	for (int i = x->size - 1, k = 0; i >= 0; i--)
		for (int j = 60; j >= 0; j -= 4)
			r[k++] = hex[(x->digits[i] & (int64)15 << j) >> j];
	for (; *r == '0'; r++);
	return r;
}

void add(bigint r, const bigint x, const bigint y)
{
	int carry = 0, i = 0;
	int64 t = x->size > y->size;
	bigint_ptr a = t ? x : y;
	bigint_ptr b = t ? y : x;
	while (i < b->size)
	{
		t = a->digits[i] + b->digits[i] + carry;
		carry = t <= a->digits[i] && t <= b->digits[i];
		r->digits[i++] = t;
	}
	while (i < a->size)
	{
		t = a->digits[i] + carry;
		carry = t == 0;
		r->digits[i++] = t;
	}
	if (a->size < p->size)
		if (carry)
		{
			r->digits[a->size] = 1;
			r->size = a->size + 1;
			if (cmp(r, p) >= 0)
				sub_n(r, r, p);
		}
		else
			r->size = a->size;
	else if (carry || cmp(r, p) >= 0)
		sub_n(r, r, p);
}

void sub(bigint r, const bigint x, const bigint y)
{
	if (cmp(x, y) >= 0)
		sub_n(r, x, y);
	else
	{
		sub_n(r, p, y);
		add(r, r, x);
	}
}

void sub_n(bigint r, const bigint x, const bigint y)
{
	int borrow = 0;
	int64 t;
	for (int i = 0; i < x->size; i++)
	{
		t = x->digits[i] - y->digits[i] - borrow;
		borrow = x->digits[i] <= t && x->digits[i] <= y->digits[i];
		if (r->digits[i] = t)
			r->size = i + 1;
	}
}

void sub_p(bigint r)
{
	int borrow = 0;
	int64 t;
	for (int i = 0; i < p->size; i++)
	{
		t = r->digits[i] - p->digits[i] - borrow;
		borrow = r->digits[i] <= t && r->digits[i] <= p->digits[i];
		if (r->digits[i] = t)
			r->size = i + 1;
	}
}

void mul(bigint r, const bigint x, const bigint y)
{
	
}

//void div(bigint q, const bigint n, const bigint d)
//{
//	mpz_fdiv_q(q, n, d);
//}
//
//void mod(bigint r, const bigint n, const bigint d)
//{
//	mpz_mod(r, n, d);
//}
//
//void div_qr(bigint q, bigint r, const bigint n, const bigint d)
//{
//	mpz_fdiv_qr(q, r, n, d);
//}
//
//void pow_(bigint r, const bigint b, unsigned long e)
//{
//	mpz_pow_ui(r, b, e);
//}
//
//int sgn(const bigint x)
//{
//	return mpz_sgn(x);
//}
//
int cmp(const bigint x, const bigint y)
{
	if (x->size > y->size)
		return 1;
	if (x->size < y->size)
		return -1;
	for (int i = x->size - 1; i >= 0; i--)
		if (x->digits[i] > y->digits[i])
			return 1;
		else if (x->digits[i] < y->digits[i])
			return -1;
	return 0;
}

//
//void add_fp(bigint r, const bigint x, const bigint y)
//{
//	mpz_add(r, x, y);
//	mpz_mod(r, r, p);
//}
//
//void sub_fp(bigint r, const bigint x, const bigint y)
//{
//	mpz_sub(r, x, y);
//	mpz_mod(r, x, p);
//}
//
//void mul_fp(bigint r, const bigint x, const bigint y)
//{
//	mpz_mul(r, x, y);
//	mpz_mod(r, r, p);
//}
//
//void inv_fp(bigint r, bigint x)
//{
//	mpz_invert(r, x, p);
//}
//
//void pow_fp(bigint r, const bigint b, const bigint e)
//{
//	mpz_powm(r, b, e, p);
//}
