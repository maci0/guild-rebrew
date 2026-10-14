#include <string.h>

unsigned short* __cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(void*, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
void __cdecl fcn_005100f0(int, int);

/* ADDRESS: GOLD 0x004b8870 */
/* ADDRESS: GOLDTL 0x004b8c20 */

int __cdecl fcn_004b8c20(int* a1)
{
	char buf[0x200];
	unsigned short* e;
	int n;

	n = gm_RandomMod(3) + 2;
	e = fcn_00508e40(a1[0]);
	if (e == 0)
		return 1;
	if (fcn_005c6270(e, 0x290) != 0)
		return 0x400;
	if (*(int*) (e + 0xca) < n)
		return 0x400;
	fcn_0051af00(buf, *(unsigned short*) (a1 + 1) + 0x12e7, n);
	fcn_00545d40(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
	fcn_005100f0(*(int*) (e + 2), -n);
	return 0;
}
