#include <string.h>

extern unsigned char g_773d75;

char* __cdecl fcn_00508e40(int id);
unsigned short __cdecl fcn_0042e410(int a);
int __cdecl fcn_0050b750(int a, char b);
void __cdecl fcn_0051af00(char* buf, int fmt, ...);
void __cdecl fcn_00545d40(int a, int b, char* buf, int c, int d, int e);
void __cdecl fcn_005100f0(int a, int b);

/* ADDRESS: GOLDTL 0x004b8d00 */
int __cdecl fcn_004b8d00(int* a0)
{
	char buf[0x200];
	char* p;
	int n;

	p = fcn_00508e40(*a0);
	if (p == 0) {
		return 1;
	}
	fcn_0051af00(buf, 0x12e7 + *(unsigned short*) ((char*) a0 + 4),
		fcn_0050b750(1, g_773d75),
		n = (unsigned short) fcn_0042e410(3) + 3);
	fcn_00545d40(*(int*) (p + 4), *(int*) (p + 4), buf,
		strlen(buf) > 0x100, 0x603, 0);
	fcn_005100f0(*(int*) (p + 4), n);
	return 0;
}
