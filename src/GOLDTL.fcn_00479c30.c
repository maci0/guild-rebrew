// FUNCTION: GOLDTL 0x479c30
// SIZE: 307

#include <stdio.h>
#include <stdlib.h>

extern int g_100ef80;
extern int g_67d96c;
extern short g_7725f0;
extern short g_7725f2;
extern char g_67da68[];

int __cdecl fcn_00478cb0(int a1, int a2, char* a3, char* e, int s);
int __cdecl fcn_004789e0(int a1, int a2, char* a3, char* e, int s);

int __cdecl fcn_00479c30(int a1, int a2, char* a3, char* h, int idx, char scale, int alt)
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
		sprintf(buf, g_67da68, h + 0xa);
		return 0;
	}
	e = h + *(int*) (h + idx * 4 + 0x45);
	if (g_100ef80 == 0) {
		save = g_67d96c;
		g_67d96c = *(int*) (a3 + 0x10);
		switch (*(unsigned char*) (e + 0xc)) {
		case 0:
			return 0;
		case 1:
			if (scale < 0) {
				if (alt != 0) {
					r = fcn_00478cb0(a1, a2, a3, e, abs(scale));
				} else {
					r = fcn_004789e0(a1, a2, a3, e, abs(scale));
				}
			}
			return r;
		case 2:
			return r;
		}
		g_67d96c = save;
	}
	s = abs(scale);
	g_7725f0 = *(unsigned short*) (e + 6) / s;
	g_7725f2 = *(unsigned short*) (e + 0xa) / s;
	return r;
}
