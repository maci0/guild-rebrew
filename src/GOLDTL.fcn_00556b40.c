#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_00508e40(int);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_00500bb0(void*, int, int, int);
int __cdecl fcn_004c5620(int, char*);
int __cdecl fcn_004c4450(int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00546ef0(int, char*, int, int);

/* ADDRESS: GOLDTL 0x00556b40 */
void __cdecl fcn_00556b40(char* e)
{
	char buf[0x200];
	char* a;
	char* b;
	int r;

	a = fcn_00508e40(*(int*) (e + 0xb0));
	b = fcn_00508e40(*(int*) (e + 0xac));
	if (*(int*) (e + 0x70) == -1) {
		fcn_00546190(e);
		return;
	}
	if (*(int*) (e + 0x70) == -2) {
		if ((e[0x78] & 4) != 0) {
			fcn_00546190(e);
			return;
		}
		if (a != 0) {
			fcn_004c5420(*(int*) (a + 4), 0x1c8, 4, 0, 0x800000);
			if (b != 0) {
				fcn_004c54c0(*(int*) (b + 4), *(int*) (a + 4), (-8 - *(int*) (e + 0xb4)) * 5, 1);
			}
		}
		fcn_00546190(e);
		return;
	}
	if ((e[0x78] & 4) != 0) {
		return;
	}
	if (a == 0) {
		fcn_00500bb0(e + 0x52, 0, 2, 0);
		*(int*) (e + 0x84) = fcn_004c5620(-1, e);
		return;
	}
	if (*(int*) (e + 0x70) == 2) {
		r = fcn_004c4450(*(int*) (e + 0x84));
		if (r == 0) {
			return;
		}
		if (r == 1) {
			fcn_00500bb0(e + 0x52, 0, 2, 0);
			fcn_004c5620(0, e);
			return;
		}
		if (r == 2) {
			fcn_00500bb0(e + 0x52, 0, 2, 0);
			fcn_004c5620(-1, e);
		}
		return;
	}
	if (b != 0 && b[8] != 0) {
		if (*(int*) (e + 0x70) == 1) {
			fcn_004c5420(*(int*) (a + 4), 0x1c8, 4, 0, 0x800000);
			fcn_004c54c0(*(int*) (b + 4), *(int*) (a + 4), (-2 - *(int*) (e + 0xb4)) * 5, 1);
			fcn_00500bb0(e + 0x52, 0, 2, 0);
			*(int*) (e + 0x84) = fcn_004c5620(-1, e);
			return;
		}
		if (*(int*) (e + 0x70) == 3) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_004c5620(0, e);
			return;
		}
		if (a[9] == 1) {
			fcn_0051af00(buf, 0xb4, *(unsigned short*) a);
		} else {
			fcn_0051af00(buf, 0xb5, *(unsigned short*) a);
		}
		fcn_00546ef0(*(unsigned short*) (e + 8), buf, -*(int*) (e + 0xb8), 0);
		(*(int*) (e + 0xb4))++;
		fcn_00500bb0(e + 0x52, 0x18, 0, 0);
		*(int*) (e + 0x84) = fcn_004c5620(0, e);
		return;
	}
	fcn_004c5420(*(int*) (a + 4), 0x1c8, 4, 0, 0x800000);
	fcn_00500bb0(e + 0x52, 0, 2, 0);
	*(int*) (e + 0x84) = fcn_004c5620(-1, e);
}
