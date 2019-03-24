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
}*bigint_ptr, bigint[1];
typedef bigint* element;
int16 r_size;
int64 p_inv_mod_b;
bigint p;

static const int16 one_16 = ~0;
static const int32 one_32 = ~0;

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
void sub_p(bigint);
void mul(bigint, const bigint, const bigint);    //short one first
void double_(bigint, const bigint);
void square(bigint, const bigint);
//void shift_left(bigint, const bigint, int16);
//void shift_right(bigint, const bigint, int16);
//void mod(bigint, const bigint, const bigint);
void pow(bigint, const bigint, const bigint);
int cmp(const bigint, const bigint);

void redc_0(bigint);
void redc(bigint, const bigint, const bigint);
int64* mul_int64(int64, int64);

