#include <string.h>

unsigned short* __cdecl fcn_00508e40(int);
int __cdecl fcn_005c6270(void*, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_004bac00(unsigned short*, int*, float);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

// FUNCTION: GOLD 0x004ba960
// FUNCTION: GOLDTL 0x4bad30

int __cdecl fcn_004bad30(int* a1)
{
	float f;
	int id;
	char buf[0x200];
	unsigned short* e;
	char* s;

	f = (gm_RandomMod(0xd) + 13.0) * 0.01;
	e = fcn_00508e40(a1[0]);
	if (e == 0)
		return 1;
	if (fcn_005c6270(e, 0x290) != 0)
		goto fail;
	if (fcn_004bac00(e, &id, f) == 0)
		goto fail;
	s = gm_StartFilteredEntitySearch(1, 1, id);
	if (s != 0) {
		fcn_0051af00(buf, *(unsigned short*) (a1 + 1) + 0x12e7, s, (int) (f * 100.0f));
		fcn_00545d40(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
		return 0;
	}
fail:
	return 0x400;
}
