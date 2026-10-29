#include <string.h>

int __cdecl fcn_00508e40(int);
unsigned short __cdecl fcn_0042e410(int);
int __cdecl fcn_0050dac0(unsigned short);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_004c51a0(int, int, unsigned char, int);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x004b6a00 */
int __cdecl fcn_004b6a00(int* a1)
{
	unsigned char* f;
	char buf[0x100];
	double d;
	double t;
	int r;
	int n;

	f = (unsigned char*) fcn_00508e40(a1[0]);
	if (f == 0) {
		return 1;
	}
	if (f[0x166] == 0xe) {
		return 0x400;
	}
	r = fcn_0042e410(3);
	d = (double) r + *(double*) 0x6629c8;
	t = (double) fcn_0050dac0(*(unsigned short*) f) * d;
	n = (int) (t * *(double*) 0x6640e8);
	fcn_0051af00(buf, *(unsigned short*) ((char*) a1 + 4) + 0x12e7, n);
	fcn_004c51a0(a1[0], -1, *(unsigned char*) 0x773d75, n);
	fcn_00545d40(*(int*) (f + 4), *(int*) (f + 4), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
