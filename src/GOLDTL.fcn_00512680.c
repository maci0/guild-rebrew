// FUNCTION: GOLDTL 0x512680

#include <string.h>

extern unsigned char g_773d75;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned char* __cdecl gm_AddObjekt(void);
char* __cdecl fcn_00502cd0(int, int, int, int);
char* __cdecl fcn_00502fe0(int, int, int);
void __cdecl fcn_004c51f0(int, int, int, int, char, int);
unsigned short __cdecl gm_RandomMod(int);

void __cdecl fcn_00512680(void)
{
	int kinds[4];
	int ids[8];
	int* p;
	int kind;
	unsigned char* s;
	char* a;
	char* b;
	int v;
	int i;

	kinds[0] = 0x20;
	kind = 0x20;
	kinds[1] = 0x1f;
	kinds[2] = 0x1e;
	kinds[3] = 0;
	p = kinds;
	do {
		for (s = gm_StartFilteredEntitySearch(1, 0, kind); s != 0; s = gm_AddObjekt()) {
			a = fcn_00502cd0(*(int*) (s + 0x5d), 1, 0, 0xff);
			b = fcn_00502cd0(*(int*) (s + 0x5d), 1, 0, 0xfe);
			if (a == 0) {
				a = fcn_00502fe0(*(int*) (s + 1), 0xff, 1);
			}
			if (b == 0) {
				b = fcn_00502fe0(*(int*) (s + 1), 0xfe, 1);
			}
			memset(ids, 0, sizeof(ids));
			switch (kind) {
			case 0x1e:
				ids[0] = 0x1b7;
				ids[1] = 0x1b8;
				ids[2] = 0x1b9;
				break;
			case 0x1f:
				ids[0] = 0x1ba;
				ids[1] = 0x1bb;
				ids[2] = 0x1bc;
				break;
			case 0x20:
				ids[0] = 0x1bd;
				ids[1] = 0x1bf;
				ids[2] = 0x1be;
				ids[3] = 0x1c0;
				break;
			}
			for (i = 0; i < 8; i++) {
				if (ids[i] == 0) {
					continue;
				}
				if (*s == 0x1e) {
					fcn_004c51f0(*(int*) (a + 2), -1, ids[i], 2, (*(char*)&g_773d75), 0);
				} else {
					fcn_004c51f0(*(int*) (a + 2), -1, ids[i], 2 - (i != 0), (*(char*)&g_773d75), 0);
					if (i == 0) {
						fcn_004c51f0(*(int*) (b + 2), -1, ids[0], gm_RandomMod(0x14) + 0x14, (*(char*)&g_773d75), 0);
					}
				}
				switch (ids[i]) {
				case 0x1bd:
					v = 0x1d0;
					break;
				case 0x1bf:
					v = 0x1d2;
					break;
				case 0x1be:
					v = 0x1d1;
					break;
				case 0x1c0:
					v = 0x1d3;
					break;
				case 0x1b7:
					v = 0x1ca;
					break;
				case 0x1b8:
					v = 0x1cb;
					break;
				case 0x1b9:
					v = 0x1cc;
					break;
				case 0x1bb:
					v = 0x1ce;
					break;
				case 0x1bc:
					v = 0x1cf;
					break;
				default:
					continue;
				}
				fcn_004c51f0(*(int*) (a + 2), -1, v, 2 - (i != 0), (*(char*)&g_773d75), 0);
			}
		}
	} while ((kind = *++p) != 0);
}
