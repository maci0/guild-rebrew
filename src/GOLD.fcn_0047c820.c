// FUNCTION: GOLD 0x0047c820

#include <stdio.h>
#include <stdlib.h>

extern int g_00f8a630; /* 0x00f8a630 */
extern int g_005fed64; /* 0x005fed64 */
extern short g_006f044c; /* 0x006f044c */
extern short g_006f044e; /* 0x006f044e */
extern char g_005feea8[]; /* 0x005feea8 */

int __cdecl fcn_0047b630(int a1, int a2, char* a3, char* e, int s);
int __cdecl fcn_0047b340(int a1, int a2, char* a3, char* e, int s);

int __cdecl fcn_0047c820(int a1, int a2, char* a3, char* h, unsigned char idx, char scale, int alt)
{
	char buf[0x80];
	char* e;
	int save;
	int s;
	int r;

	r = 1;
	if (h == 0) {
		return 0;
	}
	if (idx > *(unsigned short*) (h + 0x2a)) {
		sprintf(buf, g_005feea8, h + 0xa);
		return 0;
	}
	e = h + *(int*) (h + idx * 4 + 0x45);
	if (g_00f8a630 == 0) {
		save = g_005fed64;
		g_005fed64 = *(int*) (a3 + 0x10);
		switch (*(unsigned char*) (e + 0xc)) {
		case 0:
			return 0;
		case 1:
			if (scale < 0) {
				if (alt != 0) {
					r = fcn_0047b630(a1, a2, a3, e, abs(scale));
				} else {
					r = fcn_0047b340(a1, a2, a3, e, abs(scale));
				}
			}
			return r;
		case 2:
			return r;
		}
		g_005fed64 = save;
	}
	s = abs(scale);
	g_006f044c = *(unsigned short*) (e + 6) / s;
	g_006f044e = *(unsigned short*) (e + 0xa) / s;
	return r;
}
