#if 1
#define BITS 64
#define BITS_SUB_1 63
#define BITS_SUB_4 60
#define BYTES 8
#define HEX_PER_UNIT 16
#define BITS_OF_HEX_PER_UNIT 4
typedef unsigned long long int64;
#else
#define BITS 32
#define BITS_SUB_1 31
#define BITS_SUB_4 28
#define BYTES 4
#define HEX_PER_UNIT 8
#define BITS_OF_HEX_PER_UNIT 3
typedef unsigned int int64;
#endif

typedef unsigned short int16;
typedef unsigned int int32;
typedef struct
{
	int16 size;
	int64* digits;
}bigint_struct;
typedef bigint_struct* bigint_ptr, bigint[1];
typedef bigint* element;
bigint p;

void init(bigint);
int init_p(const char*);
int init_str(bigint, const char*);
void init_copy(bigint, const bigint);
void copy(bigint, const bigint);
void set_int(bigint, const int64);
void clear(bigint);
char* get_str(const bigint);
void add(bigint, const bigint, const bigint);
void sub(bigint, const bigint, const bigint);
void sub_n(bigint, const bigint, const bigint);
void mul(bigint, const bigint, const bigint);    //short one first
void twice(bigint, const bigint);
void square(bigint, const bigint);
//void shift_left(bigint, const bigint, int16);
//void shift_right(bigint, const bigint, int16);
//void mod(bigint, const bigint, const bigint);
void power(bigint, const bigint, const bigint, int16);
int cmp(const bigint, const bigint);

void mul_int(int64*, int64, int64);
void euclid(int64*, int64, int64);


