typedef unsigned short int16;
typedef unsigned long long int64;
typedef struct
{
	int16 size;
	int64* digits;
}*bigint_ptr, bigint[1];
typedef bigint* element;
bigint p;

void init(bigint);
int init_p(const char*);
int init_str(bigint, const char*);
void set(bigint, const bigint);
void clear(bigint);
char* get_str(const bigint);
void add(bigint, const bigint, const bigint);
void sub(bigint, const bigint, const bigint);
void sub_n(bigint, const bigint, const bigint);
void sub_p(bigint);
//void mul(bigint, const bigint, const bigint);
//void div(bigint, const bigint, const bigint);
//void mod(bigint, const bigint, const bigint);
//void div_qr(bigint, bigint, const bigint, const bigint);
//void pow_(bigint, const bigint, unsigned long);
//int sgn(const bigint);
int cmp(const bigint, const bigint);
//
//
//void add_fp(bigint, const bigint, const bigint);
//void sub_fp(bigint, const bigint, const bigint);
//void mul_fp(bigint, const bigint, const bigint);
//void inv_fp(bigint, bigint);
//void pow_fp(bigint, const bigint, const bigint);
//
