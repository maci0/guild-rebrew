#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_00508e40(int);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
char* __cdecl fcn_005462a0(void);
char* __cdecl fcn_005463a0(int, int, int);
void __cdecl fcn_0054c720(char*, unsigned short*, unsigned short*);
int __cdecl fcn_005d2a40(int, int);

/* ADDRESS: GOLDTL 0x0054c800 */
void __cdecl fcn_0054c800(char* e)
{
	char* a;
	char* b;
	char* f;

	*(int*) (e + 0x70) = 0;
	if ((e[0x78] & 2) == 0) {
		return;
	}
	a = fcn_00508e40(*(int*) (e + 0xac));
	b = fcn_00508e40(*(int*) (e + 0xb0));
	if (a == 0 || b == 0 || a[9] == b[9]) {
		*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
		*(int*) (e + 0x84) = fcn_004c5620(-1, e);
		return;
	}
	if (*(int*) (a + 0x5c) != -1) {
		int v = -1;

		fcn_004c4510(a, *(int*) (a + 4));
		fcn_004c4570(4, 1, 0x5c, &v);
		fcn_004c5360();
	}
	if (*(int*) (b + 0x5c) != -1) {
		int v = -1;

		fcn_004c4510(b, *(int*) (b + 4));
		fcn_004c4570(4, 1, 0x5c, &v);
		fcn_004c5360();
	}
	f = fcn_005463a0(1, 0, 0x41);
	for (; f != 0; f = fcn_005462a0()) {
		if (*(int*) (f + 0xb0) == *(int*) (a + 4)) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
			*(int*) (e + 0x84) = fcn_004c5620(-1, e);
			return;
		}
	}
	*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0x18, 0, 0);
	*(int*) (e + 0x58) = 0;
	*(int*) (e + 0x70) = 0;
	e[0xb8] = 0;
	*(short*) (e + 0x56) = 8;
	e[0xb9] = (char) fcn_005d2a40(*(int*) (e + 0xac), *(int*) (e + 0xb0));
	e[0xba] = 0;
	fcn_0054c720(e, (unsigned short*) a, (unsigned short*) b);
	e[0xbb] = 0;
	*(int*) (e + 0x84) = -1;
	fcn_004c5620(0, e);
}
