#include<stdlib.h>
#include<stdio.h>
#include "bigint.h"

#define ADD_MUL(x, y) prod = mul_int64(x, y);\
s[j] += prod[0];	\
b = s[j] < prod[0];\
carry[0] += prod[1] + b;\
carry[1] += b ? carry[0] <= prod[1] : carry[0] < prod[1]

#define ADD_MUL_0(x, y) prod = mul_int64(x, y);\
s[0] += prod[0];	\
b = s[0] < prod[0];\
carry[0] += prod[1] + b;\
carry[1] += b ? carry[0] <= prod[1] : carry[0] < prod[1]

void init(bigint r)
{
	r->size = 1;
	r->digits = (int64*)malloc(BYTES * p->size);
}

int init_p(const char* str)
{
	int count = 0, i = 0, j = 0;
	while (*str)
		count++, str++;
	p->size = (count >> BITS_OF_HEX_PER_UNIT) + count % HEX_PER_UNIT;
	p->digits = (int64*)malloc(BYTES * p->size);
	p_inv_mod_b = 937367889255526401;
	for (int k = 0; k < count; i++)
		for (j = 0; j < HEX_PER_UNIT && k < count; k++)
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
	r->digits = (int64*)malloc(BYTES * p->size);
	for (int k = 0; k < count; i++)
		for (j = 0; j < HEX_PER_UNIT && k < count; k++)
			if (*(--str) <= '9' && *str >= '0')
				r->digits[i] += (int64)(*str - '0') << (j++ << 2);
			else if (*str <= 'F' && *str >= 'A')
				r->digits[i] += (int64)(*str - 'A' + 10) << (j++ << 2);
			else if (*str <= 'f' && *str >= 'a')
				r->digits[i] += (int64)(*str - 'a' + 10) << (j++ << 2);
			else
				return 0;
	printf("%d\n", i);
	return (r->size = i);
}

void init_copy(bigint r, const bigint x)
{
	r->digits = (int64*)malloc(BYTES * p->size);
	for (int i = 0; i < x->size; i++)
		r->digits[i] = x->digits[i];
	r->size = x->size;
}

void copy(bigint r, const bigint x)
{
	for (int i = 0; i < x->size; i++)
		r->digits[i] = x->digits[i];
	r->size = x->size;
}

void set_int(bigint r, int64 x)
{
	r->size = 1;
	r->digits[0] = x;
}

void clear(bigint r)
{
	r->size = 0;
	free(r->digits);
}

char* get_str(const bigint x)
{
	char* r = (char*)calloc((x->size << BITS_OF_HEX_PER_UNIT) + 1, 1);
	char hex[16] = "0123456789abcdef";
	for (int i = x->size - 1, k = 0; i >= 0; i--)
		for (int j = BITS_SUB_4; j >= 0; j -= 4)
			r[k++] = hex[x->digits[i] >> j & 15];
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
		carry = carry ? t <= a->digits[i] : t < a->digits[i];
		r->digits[i++] = t;
	}
	while (i < a->size)
	{
		t = a->digits[i] + carry;
		carry = t < carry;
		r->digits[i++] = t;
	}
	r->size = a->size;
	if (a->size < p->size)
	{
		if (carry)
		{
			r->digits[a->size] = 1;
			r->size += 1;
			if (cmp(r, p) >= 0)
				sub_p(r);
		}
	}
	else if (carry || cmp(r, p) >= 0)
		sub_p(r);
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
	int borrow = 0, i = 0;
	int64 t;
	while (i < y->size)
	{
		t = x->digits[i] - y->digits[i] - borrow;
		borrow = borrow ? x->digits[i] <= t : x->digits[i] < t;
		if (r->digits[i++] = t)
			r->size = i;
	}
	while (i < x->size)
	{
		t = x->digits[i] - borrow;
		borrow = borrow > x->digits[i];
		if (r->digits[i++] = t)
			r->size = i;
	}
}

void sub_p(bigint r)
{
	int borrow = 0, i = 0;
	int64 t;
	while (i < p->size)
	{
		t = r->digits[i] - p->digits[i] - borrow;
		borrow = borrow ? r->digits[i] <= t : r->digits[i] < t;
		if (r->digits[i++] = t)
			r->size = i ;
	}
}

void mul(bigint r, const bigint x, const bigint y)
{
	int i = 0, j = 0;
	int64 t;
	bigint a, b;
	init_copy(a, x);
	init_copy(b, y);
	for (set_int(r, 0); i < a->size - 1; i++)
		for (t = a->digits[i], j = 0; j < BITS; j++)
		{
			if (t & 1)
				add(r, r, b);
			t >>= 1;
			double_(b, b);
		}
	if ((t = a->digits[i]) & 1)
		add(r, r, b);
	while (t >>= 1)
	{
		double_(b, b);
		if (t & 1)
			add(r, r, b);
	}
	clear(a);
	clear(b);
}

void double_(bigint r, const bigint x)
{
	int64 s = 0, t = 0;
	for (int i = 0; i < x->size; i++)
	{
		t = x->digits[i];
		r->digits[i] = (t << 1) + s;
		s = t >> BITS_SUB_1;
	}
	r->size = x->size;
	if (x->size < p->size)
	{
		if (s)
		{
			r->digits[x->size] = 1;
			r->size += 1;
			if (cmp(r, p) >= 0)
				sub_p(r);
		}
	}
	else if (s || cmp(r, p) >= 0)
		sub_p(r);
}

void square(bigint r, const bigint x)
{

}

//void shift_left(bigint r, const bigint x, int16 b)
//{
//	int64 t = 0;
//	int16 d = b >> 6;
//	b = b & 63;
//	for (int i = 0; i < x->size; i++)
//	{
//		r->digits[i] = (x->digits[i] << b) + t;
//		t = x->digits[i] >> 64 - b;
//	}
//	r->size = x->size + (x->size < p->size && (r->digits[x->size] = t));
//}

//void shift_right(bigint r, const bigint x, int16 b)
//{
//	int64 t = 0;
//	int16 d = b >> 6;
//	b = b & 63;
//	for (int i = x->size - 1 - d; i >= 0; i--)
//	{
//		r->digits[i] = (x->digits[i + d] >> b) + t;
//		t = x->digits[i + d] << 64 - b;
//	}
//	r->size = x->size - d - (r->digits[x->size - d - 1] == 0);
//}

void pow(bigint r, const bigint x, const bigint y)
{
	int i = 0, j = 0;
	int64 t;
	bigint a, b;
	init_copy(a, x);
	init_copy(b, y);
	for (set_int(r, 1); i < a->size - 1; i++)
		for (t = a->digits[i], j = 0; j < BITS; j++)
		{
			if (t & 1)
				mul (r, r, b);
			t >>= 1;
			mul(b, b, b);
		}
	if ((t = a->digits[i]) & 1)
		mul(r, r, b);
	while (t >>= 1)
	{
		mul(b, b, b);
		if (t & 1)
			mul(r, r, b);
	}
	clear(a);
	clear(b);
}

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

void redc_0(bigint r)
{
	int64 m;
	int64 carry[2];
	bigint t;
	//assert(t->size<r_size+p->size)
	t->digits = (int64*)calloc((r_size + p->size) * BYTES, BYTES);
	for (int i = 0; i < r->size; i++)
		t->digits[i] = r->digits[i];
	for (int i = 0; i < r_size; i++)
	{
		int b = 0, c = 0;
		int j = 0;
		int64* x;
		carry[0] = 0, carry[1] = 0;
		m = t->digits[i] * p_inv_mod_b;
		for (j = 0; j < p->size; j++)
		{
			x = mul_int64(m, p->digits[j]);
			x[0] += t->digits[i + j];
			b = x[0] < t->digits[i + j];
			x[1] += b;
			c = x[1] < b;
			x[0] += carry[0];
			b = x[0] < carry[0];
			x[1] += carry[1] + b;
			c += b ? x[1] <= carry[1] : x[1] < carry[1];
			t->digits[i + j] = x[0];
			carry[0] = x[1];
			carry[1] = c;
		}
		for (; j < r_size + p->size; j++)
		{
			t->digits[i + j] += carry[0];
			carry[0] = carry[1] + (t->digits[i + j] < carry[0]);
			carry[1] = carry[0] < carry[1];
		}
	}
	t->digits += r_size;
	t->size = p->size;
	if (cmp(t, p) >= 0)
		sub_p(t);
	r->digits = t->digits;
	int i = p->size;
	for (; !r->digits[i-1]; i--);
	r->size = i;
}

void redc(bigint r, const bigint x, const bigint y)
{
	int64 b, m, x_i;
	int64 h = 0;
	int64* prod, carry[2];
	int64* s = r->digits;
	for (int i = 0; i < p->size; i++)
		s[i] = 0;
	for (int i = 0, j = 0; i < p->size; i++)
	{
		m = (x->digits[i] * y->digits[0] + s[0]) * p_inv_mod_b;
		x_i = x->digits[i];
		carry[0] = 0, carry[1] = 0;
		ADD_MUL_0(m, p->digits[0]);
		ADD_MUL_0(x_i, y->digits[0]);
		for (j = 0; j < p->size - 1; j++)
		{
			s[j] = s[j + 1] + carry[0];
			b = s[j] < carry[0];
			carry[0] = carry[1] + b;
			carry[1] = carry[0] < b;
			ADD_MUL(m, p->digits[j + 1]);
			ADD_MUL(x_i, y->digits[j + 1]);
		}
		s[j] += carry[0];
		h += carry[1] + (s[j] < carry[0]);
	}
	r->size = p->size;
	if (h || cmp(r, p) >= 0)
		sub_p(r);
}

int64* mul_int64(int64 x, int64 y)
{
	int64 r[2], x0, x1, y0, y1, r0, r1, r2;
	x0 = x & one_32;
	x1 = x >> 32;
	y0 = y & one_32;
	y1 = y >> 32;
	r0 = x0 * y0;
	r1 = x1 * y1;
	//if (x0 > x1)
	//	if (y0 > y1)
	//		r2 = r0 + r1 - (x0 - x1) * (y0 - y1);
	//	else
	//		r2 = r0 + r1 + (x0 - x1) * (y1 - y0);
	//else
	//	if (y0 > y1)
	//		r2 = r0 + r1 + (x1 - x0) * (y0 - y1);
	//	else
	//		r2 = r0 + r1 - (x1 - x0) * (y1 - y0);
	r2 = x0 * y1 + x1 * y0;
	r[0] = r0 + (r2 << 32);
	r[1] = r1 + (r2 >> 32) + (r[0] < r0);
	return r;
}
