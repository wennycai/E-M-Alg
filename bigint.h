#if 1
#define BITS 64
#define BITS_SUB_1 63
#define BYTES 8
#define HEX_PER_UNIT 16
#define BITS_OF_HEX_PER_UNIT 4
typedef unsigned long long int64;
#else
#define BITS 32
#define BITS_SUB_1 31
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

/*Allocate memory for bigint struct's array of integers.*/
void init(bigint);
/*Initial the prime p, as well as the base field, return the size.*/
int init_p(const char*);
/*Allocate memory and assign values with a hex string, return the size.*/
int init_str(bigint, const char*);
/*Allocate memory and assign values with another bigint.*/
void init_copy(bigint, const bigint);
/*Assign values with another bigint.*/
void copy(bigint, const bigint);
/*Assign values with an integers.*/
void set_int(bigint, const int64);
/*Assign values with a hex string, return the size.*/
int set_str(bigint, const char*);
/*Get the hex string of a bigint.*/
void get_str(char*, const bigint);
/*Print the hex string of a bigint.*/
void print(const bigint);
/*Free the allocated memory of a bigint, which will be unavailable until initialized again.*/
void clear(bigint);
void add(bigint, const bigint, const bigint);
void sub(bigint, const bigint, const bigint);
/*Substract one bigint from another, when the former is greater than the latter*/
void sub_n(bigint, const bigint, const bigint);
void mul(bigint, const bigint, const bigint);
void twice(bigint, const bigint);
void square(bigint, const bigint);
void power(bigint, const bigint, const bigint);
void power_int(bigint, const bigint, int64);
int cmp(const bigint, const bigint);
void mul_int(int64*, int64, int64);
void euclid(int64*, int64, int64);
