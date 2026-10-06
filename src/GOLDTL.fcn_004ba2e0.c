#include <string.h>

extern char g_7f4ca0[];

unsigned short* __cdecl fcn_00508e40(int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);
int __cdecl fcn_00504bd0(int);
unsigned short __cdecl fcn_0042e410(unsigned short);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

// FUNCTION: GOLDTL 0x4ba2e0
// FUNCTION: GOLD 0x004b9f20

int __cdecl fcn_004ba2e0(int* a1)
{
	char* ents[8];
	char buf[0x200];
	unsigned short* e;
	unsigned char* it;
	char* chosen;
	char* sel;
	char* rec;
	int n;
	int m;
	int k;
	int i;
	int x;

	n = 0;
	sel = 0;
	e = fcn_00508e40(a1[0]);
	if (e == 0)
		return 1;
	for (it = gm_StartFilteredEntitySearch(1, 3, *e); it != 0 && n < 8; it = gm_AddObjekt()) {
		k = fcn_00504bd0(it[0]);
		if (k == 1 || k == 2)
			ents[n++] = (char*) it;
	}
	if (n == 0)
		return 0x400;
	m = 0;
	chosen = ents[fcn_0042e410(n)];
	for (i = 0; i < 768; i++) {
		if (m >= 6)
			break;
		rec = g_7f4ca0 + i * 540;
		if (rec[2] == 0 && *(char**) (rec + 0x16c) == chosen && rec[0x165] != 0)
			ents[m++] = rec;
	}
	if (m > 1)
		sel = ents[fcn_0042e410(m)];
	if (chosen == 0 || sel == 0)
		return 0x400;
	x = (sel[9] != 0 ? 0x230 : 0x20d) + *(unsigned char*) (sel + 0x165);
	fcn_0051af00(buf, *(unsigned short*) (a1 + 1) + 0x12e7, x,
	    *(unsigned short*) sel, *(unsigned short*) sel, x);
	fcn_00545d40(*(int*) (e + 2), *(int*) (e + 2), buf, strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
