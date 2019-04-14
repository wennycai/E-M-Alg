#include <stdarg.h>
#include<stdlib.h>
#include<stdio.h>
#include "bigint.h"

#define ADD_MUL(s, x, y) \
mul_int(prod, x, y); \
s += prod[0]; \
k = s < prod[0]; \
carry[0] += prod[1] + k; \
carry[1] += k ? carry[0] <= prod[1] : carry[0] < prod[1]

#define ADD_MUL_0(x, y) \
mul_int(prod, x, y); \
s[0] += prod[0];	\
k = s[0] < prod[0]; \
carry[0] = prod[1] + k; \
carry[1] = k ? carry[0] <= prod[1] : carry[0] < prod[1]

static const int bigint_size = sizeof(bigint_struct);
static int64 neg_p_inv_mod_b;
static bigint r_square;

void init(bigint r)
{
	r->size = 1;
	r->digits = (int64*)malloc(BYTES * p->size);
}

void init_m(bigint x, ...)
{
	va_list va;
	bigint_ptr a;
	va_start(va, x);
	init(x);
	while ((a = va_arg(va, bigint_ptr)) != NULL)
		init(a);
	va_end(va);
}

int init_p(const char* str)
{
	int16 count, i, j, k;
	for (count = 0; *str; str++)
		count++;
	p->size = (count >> BITS_OF_HEX_PER_UNIT) + (count % HEX_PER_UNIT > 0);
	p->digits = (int64*)calloc(BYTES * p->size, BYTES);
	for (i = 0, k = 0; k < count; i++)
		for (j = 0; j < HEX_PER_UNIT && k < count; k++)
			if (*(--str) <= '9' && *str >= '0')
				p->digits[i] += (int64)(*str - '0') << (j++ << 2);
			else if (*str <= 'F' && *str >= 'A')
				p->digits[i] += (int64)(*str - 'A' + 10) << (j++ << 2);
			else if (*str <= 'f' && *str >= 'a')
				p->digits[i] += (int64)(*str - 'a' + 10) << (j++ << 2);
			else
				return 0;
	int64 s = p->digits[0];
	int64 t = (-1 % s + 1) % s;
	int64 r[3];
	euclid(r, s, t);
	neg_p_inv_mod_b = (-t) / s * r[1] - r[0];
	r_square->digits = (int64*)calloc(BYTES * i, BYTES);
	if (i == 1)
	{
		r_square->digits[0] = ((-1 % p->digits[0]) + (r_square->size = 1)) % p->digits[0];
		square(r_square, r_square);
	}
	else
	{
		r_square->digits[1] = 1;
		r_square->size = 2;
		power_init(r_square, r_square, 2 * p->size);
	}
	return i;
}

int init_str(bigint r, const char* str)
{
	int16 count, i, j, k;
	for (count = 0; *str; str++)
		count++;
	r->digits = (int64*)calloc(BYTES * p->size, BYTES);
	for (i = 0, k = 0; k < count; i++)
		for (j = 0; j < HEX_PER_UNIT && k < count; k++)
			if (*(--str) <= '9' && *str >= '0')
				r->digits[i] += (int64)(*str - '0') << (j++ << 2);
			else if (*str <= 'F' && *str >= 'A')
				r->digits[i] += (int64)(*str - 'A' + 10) << (j++ << 2);
			else if (*str <= 'f' && *str >= 'a')
				r->digits[i] += (int64)(*str - 'a' + 10) << (j++ << 2);
			else
				return 0;
	return r->size = i;
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

int set_str(bigint r, const char* str)
{
	int16 count, i, j, k;
	for (count = 0; *str; str++)
		count++;
	for (i = 0; i < r->size; r->digits[i++] = 0);
	for (i = 0, k = 0; k < count; i++)
		for (j = 0; j < HEX_PER_UNIT && k < count; k++)
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

void get_str(char* r, const bigint x)
{
	static const char hex[16] = "0123456789abcdef";
	int i = x->size - 1, j = BITS, k = 1;
	while (j >= 0 && (r[0] = hex[x->digits[i] >> (j -= 4) & 15]) == '0');
	for (j -= 4; j >= 0; j -= 4)
		r[k++] = hex[x->digits[i] >> j & 15];
	for (i--; i >= 0; i--)
		for (j = BITS - 4; j >= 0; j -= 4)
			r[k++] = hex[x->digits[i] >> j & 15];
	r[k] = 0;
}

void print(const bigint x)
{
	char* str = (char*)malloc((x->size << BITS_OF_HEX_PER_UNIT) + 1);
	get_str(str, x);
	printf("%s\n", str);
	free(str);
}

void clear(bigint r)
{
	r->size = 0;
	free(r->digits);
}

void add(bigint r, const bigint x, const bigint y)
{
	int16 carry = 0, i = 0;
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
		sub_n(y, p, y);
		add(r, x, y);
	}
}

void sub_n(bigint r, const bigint x, const bigint y)
{
	int16 borrow = 0, i = 0, size = 1;
	int64 t;
	while (i < y->size)
	{
		t = x->digits[i] - y->digits[i] - borrow;
		borrow = borrow ? x->digits[i] <= t : x->digits[i] < t;
		if (r->digits[i++] = t)
			size = i;
	}
	while (i < x->size)
	{
		t = x->digits[i] - borrow;
		borrow = borrow > x->digits[i];
		if (r->digits[i++] = t)
			size = i;
	}
	r->size = size;
}

void sub_p(bigint r)
{
	int16 borrow = 0, i = 0;
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
	redc2(r, x, y);
	redc2(r, r, r_square);
}

void mul_b(bigint r, const bigint x, const bigint y)
{
	int i, j, k;
	int64 t;
	int64* a = (int64*)malloc(BYTES * x->size);
	bigint b;
	for (i = 0, k = x->size - 1; i <= k; a[i] = x->digits[i++]);
	init_copy(b, y);
	set_int(r, 0);
	for (i = 0; i < k; i++)
		for (t = a[i], j = 0; j < BITS; j++)
		{
			if (t & 1)
				add(r, r, b);
			t >>= 1;
			twice(b, b);
		}
	if ((t = a[i]) & 1)
		add(r, r, b);
	while (t >>= 1)
	{
		twice(b, b);
		if (t & 1)
			add(r, r, b);
	}
	free(a);
	free(b->digits);
}

void twice(bigint r, const bigint x)
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
	int16 i, j, k;
	int64 t;
	int64* a = (int64*)malloc(BYTES * x->size);
	bigint b;
	for (i = 0, k = x->size - 1; i <= k; a[i] = x->digits[i++]);
	init_copy(b, x);
	set_int(r, 0);
	for (i = 0; i < k; i++)
		for (t = a[i], j = 0; j < BITS; j++)
		{
			if (t & 1)
				add(r, r, b);
			t >>= 1;
			twice(b, b);
		}
	if ((t = a[i]) & 1)
		add(r, r, b);
	while (t >>= 1)
	{
		twice(b, b);
		if (t & 1)
			add(r, r, b);
	}
	free(a);
	free(b->digits);
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

void power_int(bigint r, const bigint b, int64 e)
{
	bigint a;
	init_copy(a, b);
	set_int(r, 1);
	if (e & 1)
		mul(r, r, a);
	while (e >>= 1)
	{
		square(a, a);
		if (e & 1)
			mul(r, r, a);
	}
	free(a->digits);
}

void power_init(bigint r, const bigint b, int64 e)
{
	bigint a;
	init_copy(a, b);
	set_int(r, 1);
	if (e & 1)
		mul_b(r, r, a);
	while (e >>= 1)
	{
		square(a, a);
		if (e & 1)
			mul_b(r, r, a);
	}
	free(a->digits);
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

void redc1(bigint r, const bigint x)
{
	int16 i, j, k;
	int64 m, prod[2], carry[2];
	int64 h = 0, * s = r->digits, * a = (int64*)malloc(BYTES * x->size);
	for (i = 0; i < x->size; a[i] = x->digits[i++]);
	for (i = 0; i < p->size; s[i++] = 0);
	for (i = 0; i < x->size; i++)
	{
		m = (a[i] + s[0]) * neg_p_inv_mod_b;
		ADD_MUL_0(m, p->digits[0]);
		s[0] += a[i];
		k = s[0] < a[i];
		carry[0] += k;
		carry[1] += carry[0] < k;
		for (j = 0; j < p->size - 1; j++)
		{
			s[j] = s[j + 1] + carry[0];
			k = s[j] < carry[0];
			carry[0] = carry[1] + k;
			carry[1] = carry[0] < k;
			ADD_MUL(s[j], m, p->digits[j + 1]);
		}
		s[j] = h + carry[0];
		h = carry[1] + (s[j] < carry[0]);
	}
	for (; i < p->size; i++)
	{
		m = s[0] * neg_p_inv_mod_b;
		ADD_MUL_0(m, p->digits[0]);
		for (j = 0; j < p->size - 1; j++)
		{
			s[j] = s[j + 1] + carry[0];
			k = s[j] < carry[0];
			carry[0] = carry[1] + k;
			carry[1] = carry[0] < k;
			ADD_MUL(s[j], m, p->digits[j + 1]);
		}
		s[j] = h + carry[0];
		h = carry[1] + (s[j] < carry[0]);
	}
	for (r->size = p->size; !s[r->size - 1] && r->size > 1; r->size--);
	if (h || cmp(r, p) >= 0)
		sub_p(r);
	free(a);
}

void redc2(bigint r, const bigint x, const bigint y)
{
	int16 i, j, k;
	int64 m, prod[2], carry[2];
	int64 h = 0, * s = r->digits, * a = (int64*)malloc(BYTES * x->size), * b = (int64*)malloc(BYTES * y->size);
	//int64 h = 0, * s = (int64*)calloc(BYTES * p->size, BYTES), * a = x->digits, * b = y->digits;
	for (i = 0; i < x->size; a[i] = x->digits[i++]);
	for (i = 0; i < y->size; b[i] = y->digits[i++]);
	for (i = 0; i < p->size; s[i++] = 0);
	for (i = 0; i < x->size; i++)
	{
		m = (a[i] * b[0] + s[0]) * neg_p_inv_mod_b;
		ADD_MUL_0(m, p->digits[0]);
		ADD_MUL(s[0], a[i], b[0]);
		for (j = 0; j < y->size - 1; j++)
		{
			s[j] = s[j + 1] + carry[0];
			k = s[j] < carry[0];
			carry[0] = carry[1] + k;
			carry[1] = carry[0] < k;
			ADD_MUL(s[j], m, p->digits[j + 1]);
			ADD_MUL(s[j], a[i], b[j + 1]);
		}
		for (; j < p->size - 1; j++)
		{
			s[j] = s[j + 1] + carry[0];
			k = s[j] < carry[0];
			carry[0] = carry[1] + k;
			carry[1] = carry[0] < k;
			ADD_MUL(s[j], m, p->digits[j + 1]);
		}
		s[j] = h + carry[0];
		h = carry[1] + (s[j] < carry[0]);
	}
	for (; i < p->size; i++)
	{
		m = s[0] * neg_p_inv_mod_b;
		carry[0] = 0, carry[1] = 0;
		ADD_MUL_0(m, p->digits[0]);
		for (j = 0; j < p->size - 1; j++)
		{
			s[j] = s[j + 1] + carry[0];
			k = s[j] < carry[0];
			carry[0] = carry[1] + k;
			carry[1] = carry[0] < k;
			ADD_MUL(s[j], m, p->digits[j + 1]);
		}
		s[j] = h + carry[0];
		h = carry[1] + (s[j] < carry[0]);
	}
	for (r->size = p->size; !s[r->size - 1] && r->size > 1; r->size--);
	//for (i = 0; i < r->size; r->digits[i] = s[i++]);
	if (h || cmp(r, p) >= 0)
		sub_p(r);
	free(a);
	free(b);
	//free(s);
}

void power(bigint r, const bigint b, const bigint e)
{
	if (e->size == 1 && e->digits[0] == 0)
		return set_int(r, 1);
	static int16 thresholds[] = { 0,6,24,80,240,672,1792,4608 };
	int i, j, k, l, m, win_size;
	char* bits = (char*)malloc(BITS * e->size);
	int64 t;
	bigint b_square;
	for (i = 0, k = 0; i < e->size - 1; i++)
		for (j = 0, t = e->digits[i]; j < BITS; j++)
			bits[k++] = t >> j & 1;
	for (j = 0, t = e->digits[i]; j < BITS; j++)
		if (bits[k++] = t >> j & 1)
			i = j;
	i += BITS * (e->size - 1) - 1;
	for (win_size = 1; thresholds[win_size] < i; win_size++);
	bigint_ptr b_power = (bigint_ptr)malloc(bigint_size * (1 << win_size - 1));
	b_square->digits = (int64*)malloc(BYTES * p->size);
	b_power->digits = (int64*)malloc(BYTES * p->size);
	redc2(b_power, b, r_square);
	redc2(b_square, b_power, b_power);
	for (j = 1; j < 1 << win_size - 1; j++)
	{
		(b_power + j)->digits = (int64*)malloc(BYTES * p->size);
		redc2(b_power + j, b_power + j - 1, b_square);
	}
	for (copy(r, b_power); i >= 0; i--)
		if (bits[i])
		{
			l = i - win_size >= -1 ? win_size - 1 : i;
			for (j = l; !bits[i - j]; j--);
			for (k = 0, m = 0; k < j; redc2(r, r, r))
				m += bits[i - k] << j - (++k);
			redc2(r, r, r);
			for (redc2(r, r, b_power + m); k < l; k++)
				redc2(r, r, r);
			i -= win_size - 1;
		}
		else
			redc2(r, r, r);
	redc1(r, r);
	for (i = 0; i < 1 << win_size - 1; i++)
		free((b_power + i)->digits);
	free(b_square->digits);
	free(b_power);
	free(bits);
}

void power_(bigint r, const bigint b, const bigint e, int16 d)
{
	if (e->size == 1 && e->digits[0] == 0)
		return set_int(r, 1);
	int i, j, k, l, m;
	char* bits = (char*)malloc(BITS * e->size);
	int64 t;
	bigint b_square;
	bigint_ptr b_power = (bigint_ptr)malloc(bigint_size * (1 << d - 1));
	b_square->digits = (int64*)malloc(BYTES * p->size);
	b_power->digits = (int64*)malloc(BYTES * p->size);
	redc2(b_power, b, r_square);
	redc2(b_square, b_power, b_power);
	for (i = 1; i < 1 << d - 1; i++)
	{
		(b_power + i)->digits = (int64*)malloc(BYTES * p->size);
		redc2(b_power + i, b_power + i - 1, b_square);
	}
	for (i = 0, k = 0; i < e->size - 1; i++)
		for (j = 0, t = e->digits[i]; j < BITS; j++)
			bits[k++] = t >> j & 1;
	for (j = 0, t = e->digits[i]; j < BITS; j++)
		if (bits[k++] = t >> j & 1)
			i = j;
	copy(r, b_power);
	for (i += BITS * (e->size - 1) - 1; i >= 0; i--)
		if (bits[i])
		{
			l = i - d >= -1 ? d - 1 : i;
			for (j = l; !bits[i - j]; j--);
			for (k = 0, m = 0; k < j; redc2(r, r, r))
				m += bits[i - k] << j - (++k);
			redc2(r, r, r);
			for (redc2(r, r, b_power + m); k < l; k++)
				redc2(r, r, r);
			i -= d - 1;
		}
		else
			redc2(r, r, r);
	redc1(r, r);
	for (i = 0; i < 1 << d - 1; i++)
		free((b_power + i)->digits);
	free(b_square->digits);
	free(b_power);
	free(bits);
}
	

void mul_int(int64* r, int64 x, int64 y)
{
	int64 x0, x1, y0, y1, r0, r1;
	x0 = x & 4294967295;
	x1 = x >> 32;
	y0 = y & 4294967295;
	y1 = y >> 32;
	r0 = x0 * y0;
	x0 *= y1;
	r1 = x0 + x1 * y0;
	r[0] = r0 + (r1 << 32);
	r[1] = x1 * y1 + ((int64)(r1 < x0) << 32) + (r1 >> 32) + (r[0] < r0);
}

void euclid(int64* r, int64 x, int64 y)
{
	if (y)
	{
		euclid(r, y, x % y);
		int64 t = r[0] - x / y * r[1];
		r[0] = r[1];
		r[1] = t;
		return;
	}
	r[0] = 1, r[1] = 0, r[2] = x;
}

int16 bin(char* bits, bigint x)
{
	int16 i, j, k;
	int64 t;
	for (i = 0, k = 0; i < x->size - 1; i++)
		for (j = 0, t = x->digits[i]; j < BITS; j++)
			bits[k++] = t >> j & 1;
	for (j = 0, t = x->digits[i]; j < BITS; j++)
		if (bits[k++] = t >> j & 1)
			i = j;
	return i + BITS * (x->size - 1) + 1;
}

void sw(bigint r, const bigint b, const bigint e, int16 d)
{
	int i, j, k, l, m;
	char* bits = (char*)malloc(BITS * e->size);
	int64 t;
	bigint b_2;
	bigint_ptr b_times = (bigint_ptr)malloc(bigint_size * (1 << d - 1));
	*b_times = *b;
	init(b_2);
	twice(b_2, b_times);
	for (i = 1; i < 1 << d - 1; i++)
	{
		init(b_times + i);
		add(b_times + i, b_times + i - 1, b_2);
	}
	for (i = 0, k = 0; i < e->size - 1; i++)
		for (j = 0, t = e->digits[i]; j < BITS; j++)
			bits[k++] = t >> j & 1;
	for (j = 0, t = e->digits[i]; j < BITS; j++)
		if (bits[k++] = t >> j & 1)
			i = j;
	copy(r, b_times);
	for (i += BITS * (e->size - 1) - 1; i >= 0; i--)
		if (bits[i])
		{
			l = i - d >= -1 ? d - 1 : i;
			for (j = l; !bits[i - j]; j--);
			for (k = 0, m = 0; k < j; twice(r, r))
				m += bits[i - k] << j - (++k);
			twice(r, r);
			for (add(r, r, b_times + m); k < l; k++)
				twice(r, r);
			i -= d - 1;
		}
		else
			twice(r, r);
	for (i = 1; i < 1 << d - 1; i++)
		free((b_times + i)->digits);
	free(b_times);
	free(bits);
}

void power_b(bigint r, const bigint y, const bigint x)
{
	int i, j, k;
	int64 t;
	int64* a = (int64*)malloc(BYTES * x->size);
	bigint b;
	for (i = 0, k = x->size - 1; i <= k; a[i] = x->digits[i++]);
	b->digits = (int64*)malloc(BYTES * p->size);
	redc2(b, y, r_square);
	redc1(r, r_square);
	for (i = 0; i < k; i++)
		for (t = a[i], j = 0; j < BITS; j++)
		{
			if (t & 1)
				redc2(r, r, b);
			t >>= 1;
			redc2(b, b, b);
		}
	if ((t = a[i]) & 1)
		redc2(r, r, b);
	while (t >>= 1)
	{
		redc2(b, b, b);
		if (t & 1)
			redc2(r, r, b);
	}
	redc1(r, r);
	free(a);
	free(b->digits);
}
