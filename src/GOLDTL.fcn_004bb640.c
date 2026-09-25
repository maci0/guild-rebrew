#include <string.h>

typedef struct {
	short v[7];
} stamp14;
// SIZE 0xe

extern stamp14 g_7f4c00;

unsigned char* __cdecl fcn_00508e40(int);
void __cdecl fcn_00500d60(stamp14*, void*);
int __cdecl fcn_004fe330(void*);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

struct date_4bb640 {
	int a;
	int b;
	int c;
};
// SIZE 0xc

// FUNCTION: GOLDTL 0x4bb640
// SIZE: 222

int __cdecl fcn_004bb640(int* a1)
{
	stamp14 st;
	struct date_4bb640 d;
	char buf[0x100];
	unsigned char* e;

	e = fcn_00508e40(a1[0]);
	if (e == 0)
		return 1;
	if (*(int*) (e + 0x2c) == 0)
		return 0x400;
	st = g_7f4c00;
	fcn_00500d60(&st, &d);
	fcn_0051af00(buf, *(unsigned short*) (a1 + 1) + 0x12e7, fcn_004fe330(&d) + 0x4c);
	fcn_00545d40(*(int*) (e + 4), *(int*) (e + 4), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
