#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

unsigned short* __cdecl fcn_00508e40(int id);
int __cdecl gm_RandomMod(unsigned short n);
void __cdecl fcn_00500bb0(void* clock, int arg2, int arg3, int arg4);
void __cdecl fcn_005100f0(int a, int b);
void __cdecl fcn_0051af00(int a, int b, ...);
void __cdecl fcn_00545d40(int a, int b, void* buf, int d, int e, void* f);
void __cdecl fcn_00546190(char* a);


void __cdecl fcn_0057d9e0(char* a)
{
	unsigned short* e;
	int v;
	char buf[0x400];

	e = fcn_00508e40(*(int*) (a + 0xc));
	if (*(int*) (a + 0x70) == -1 || *(int*) (a + 0x70) == -2 || *(int*) (a + 0x70) > 3 || e == 0) {
		fcn_00546190(a);
		return;
	}
	*(int*) (a + 0x70) = *(int*) (a + 0x70) + 1;
	fcn_00500bb0(a + 0x52, (gm_RandomMod(3) & 0xffff) + 3, 0, 0);
	v = *(int*) ((char*) e + 0x194);
	if (v <= 0)
		return;
	if ((int) ((gm_RandomMod(2) & 0xffff) + 1) < v)
		v = (int) ((gm_RandomMod(2) & 0xffff) + 1);
	fcn_005100f0(*(int*) ((char*) e + 4), -v);
	if (*(char*) ((char*) e + 2) == 6 || *(char*) ((char*) e + 2) == 7) {
		fcn_0051af00((int) buf, 0x1008, v);
		fcn_00545d40(*(int*) ((char*) e + 4), -1, buf, 0, 0x5fb, 0);
	}
	if (*(int*) (a + 0x70) <= 3)
		return;
	*(pos14_7f4c00*) (a + 0x52) = g_7f4c00;
}
