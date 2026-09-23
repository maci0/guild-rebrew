// GLOBAL: GOLDTL 0x6629c8
extern double g_6629c8;
// GLOBAL: GOLD 0x5eb928
extern double g_6629c8;
// GLOBAL: GOLDTL 0x6640e8
extern double g_6640e8;
// GLOBAL: GOLD 0x5ece60
extern double g_6640e8;
extern unsigned char g_773d75;
// FUNCTION: GOLDTL 0x4b6f00
// SIZE: 216
// FUNCTION: GOLDTL 0x4b6ce0
// SIZE: 216
// FUNCTION: GOLD 0x4b6d30
// SIZE: 216
// FUNCTION: GOLD 0x4b6b10
// SIZE: 216
// FUNCTION: GOLD 0x4b6ef0
// SIZE: 216

#include <string.h>

unsigned char* __cdecl fcn_00508e40(int);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_0050dac0(short);
int __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);

int __cdecl fcn_004b6f00(void* a1)
{
	int n;
	double d;
	char buf[0x100];
	unsigned char* p;
	int r;
	unsigned int len;

	p = fcn_00508e40(*(int*) a1);
	if (p == 0) {
		return 1;
	}
	n = fcn_0042e410(3) & 0xffff;
	d = (double) n + g_6629c8;
	n = fcn_0050dac0(*(short*) p);
	r = (int) (((double) n * d) * g_6640e8);
	fcn_0051af00(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7, r);
	fcn_004c51a0(*(int*) a1, -1, g_773d75, r);
	len = strlen(buf);
	fcn_00545d40(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    0x100 < len, 0x603, 0);
	return 0;
}
