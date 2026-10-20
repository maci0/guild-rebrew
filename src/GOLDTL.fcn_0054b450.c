#include "client_types.h"

unsigned short* __cdecl fcn_00508e40(int);
float __cdecl fcn_00507e70(char*, char*, int);
float __cdecl gm_RandomFloat01(void);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_00545780(char*);
int __cdecl fcn_00545670(char*, int, int, char*, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);
void __cdecl fcn_0051af00(int, int, ...);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_004727a0(int, int);
int __cdecl fcn_004c3030(int, int, char*, int);
void __cdecl fcn_004c54c0(int, int, int, int);
int __cdecl fcn_00500cb0(void*, void*);
void __cdecl fcn_00500bb0(void*, int, int, int);

extern pos14_7f4c00 g_7f4c00;

/* ADDRESS: GOLDTL 0x0054b450 */
void __cdecl fcn_0054b450(char* a0)
{
	float dist;
	char buf[0x100];
	unsigned short* v3;
	unsigned short* v4;
	unsigned short* v5;
	char* a;

	a = a0;
	v3 = fcn_00508e40(*(int*) (a + 0xac));
	v4 = fcn_00508e40(*(int*) (a + 0xb0));
	v5 = fcn_00508e40(*(int*) (a + 0xb4));
	if (*(int*) (a + 0x70) == -2 || v3 == 0 || v4 == 0 || v5 == 0) {
		fcn_00546190(a);
		if (*(int*) (a + 0x74) != 0)
			fcn_00545780(a);
		return;
	}
	if (*(int*) (a + 0x70) == -1 ||
	    (*(char*) (v5 + 1) != 6 && *(char*) (v5 + 1) != 7))
		*(int*) (a + 0x70) = 2;
	switch (*(int*) (a + 0x70)) {
	case 0:
		fcn_00545670(a, 0, 0, (char*) 0x6a5a10, 0x5ec);
		if (*(int*) (a + 0x74) == 0) {
			fcn_00546190(a);
			return;
		}
		fcn_004727a0(*(int*) (*(int*) (a + 0x74) + 8), 0);
		fcn_00519190(0x1763, *(unsigned short*) v4, *(unsigned short*) v3);
		*(pos14_7f4c00*) (a + 0x44) = g_7f4c00;
		*(pos14_7f4c00*) (a + 0x52) = g_7f4c00;
		fcn_00500bb0(a + 0x52, 0x18, 0, 0);
		fcn_004c3030(-7, 0, (char*) 0x6a59fc, 0);
		(*(int*) (a + 0x70))++;
		return;
	case 1:
		if (fcn_00500cb0((void*) 0x7f4c00, a0 + 0x52) > 0) {
			fcn_00545780(a);
			*(int*) (a + 0x70) = 2;
			return;
		}
		if (*(int*) 0x100f884 == *(int*) (*(int*) (a + 0x74) + 8) &&
		    *(int*) 0x100f1dc != -1) {
			if (*(int*) 0x100f1dc == 2) {
				fcn_0051af00((int) buf, 0x1764, *(unsigned short*) v5,
				             *(unsigned short*) v3);
				fcn_00545d40(*(int*) (v4 + 2), *(int*) (v4 + 2), buf, 0, 0x5fa, 0);
				fcn_004c54c0(*(int*) (v3 + 2), *(int*) (v5 + 2), -0x14, 1);
				fcn_00545780(a);
				fcn_00546190(a);
				return;
			}
			if (*(int*) 0x100f1dc == 1) {
				fcn_0051af00((int) buf, 0x1765, *(unsigned short*) v5,
				             *(unsigned short*) v3);
				fcn_00545d40(*(int*) (v4 + 2), *(int*) (v4 + 2), buf, 0, 0x5fa, 0);
				fcn_004c54c0(*(int*) (v4 + 2), *(int*) (v5 + 2), -0xf, 1);
				fcn_004c54c0(*(int*) (v5 + 2), *(int*) (v4 + 2), -0xf, 1);
			}
			fcn_00545780(a);
			fcn_00546190(a);
			return;
		}
		return;
	case 2:
		dist = fcn_00507e70((char*) v4, (char*) v3, 4);
		if (0x6628a0f <= (float) (gm_RandomFloat01() + dist)) {
			fcn_0051af00((int) buf, 0x1764, *(unsigned short*) v5, *(unsigned short*) v3);
			v4 = (unsigned short*) *(int*) (v4 + 2);
			fcn_00545d40((int) v4, (int) v4, buf, 0, 0x5fa, 0);
			fcn_004c54c0(*(int*) (v3 + 2), *(int*) (v5 + 2), -0x14, 1);
		} else {
			fcn_0051af00((int) buf, 0x1765, *(unsigned short*) v5, *(unsigned short*) v3);
			fcn_00545d40(*(int*) (v4 + 2), *(int*) (v4 + 2), buf, 0, 0x5fa, 0);
			fcn_004c54c0(*(int*) (v4 + 2), *(int*) (v5 + 2), -0xf, 1);
			fcn_004c54c0(*(int*) (v5 + 2), *(int*) (v4 + 2), -0xf, 1);
		}
		fcn_00546190(a);
	}
}
