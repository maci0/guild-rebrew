#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca4[];
extern char g_869480[0x300][0x300];
extern unsigned short g_774970;
extern float g_664174;
extern char g_6a5a48[];

char* __cdecl fcn_00508e40(int);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_005d2950(int, int);
int __cdecl fcn_005d2a40(int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
int __cdecl fcn_004c5620(char, char*);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c4ef0(char*);
void __cdecl fcn_004c4510(void*, int);
void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_004c5480(int, int, float);
void __cdecl fcn_00546190(char*);
void __cdecl fcn_0054c720(char*, char*, char*);
int __cdecl fcn_004c5980(void*);
int __cdecl fcn_004f46e0(int, unsigned char**, void**);
int __cdecl fcn_004f1790(int, void*);
int __cdecl fcn_004f2a10(int*, char*, int, int);
unsigned short __cdecl gm_RandomMod(int);

#pragma optimize("y", off)
/* ADDRESS: GOLDTL 0x0054ca10 */
void __cdecl fcn_0054ca10(char* e)
{
	char* a;
	char* b;
	char* pa;
	char* pb;
	unsigned char* rec;
	void* hit;
	int v;
	char msg[0x114];
	char line[0xec];
	char text[0x200];
	char buf[0x200];

	a = fcn_00508e40(*(int*) (e + 0xac));
	b = fcn_00508e40(*(int*) (e + 0xb0));
	if (*(int*) (e + 0x70) == -1 || *(int*) (e + 0x70) == -2) {
		goto tail;
	}
	if ((e[0x78] & 4) != 0) {
		return;
	}
	if (a == 0 || b == 0 || a[9] == b[9]) {
		*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
		*(int*) (e + 0x84) = fcn_004c5620(-1, e);
		return;
	}
	if (*(int*) (e + 0x84) != -1 && fcn_004c4450(*(int*) (e + 0x84)) == 0) {
		return;
	}
	*(int*) (e + 0x84) = -1;
	switch (*(int*) (e + 0x70)) {
	case 0:
		v = fcn_005d2950(*(int*) (e + 0xac), *(int*) (e + 0xb0));
		if (v == -0x405) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
			*(int*) (e + 0x84) = fcn_004c5620(-1, e);
			fcn_0051af00(text, 0x42f6, *(unsigned short*) b);
			fcn_00545d40(*(int*) (a + 4), *(int*) (a + 4), text, 1, 0x5f4, 0);
			return;
		}
		if (v == -0x406) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
			*(int*) (e + 0x84) = fcn_004c5620(-1, e);
			fcn_0051af00(text, 0x42f7, *(unsigned short*) b);
			fcn_00545d40(*(int*) (a + 4), *(int*) (a + 4), text, 1, 0x5f4, 0);
			return;
		}
		if (v == -0x400 || v == -0x401 || v == -0x402) {
			goto Lneg;
		}
		if (v != -0x403) {
			if (v == 0) {
				if (a[2] == 6) {
					pa = fcn_00508e40(*(int*) (b + 0x60));
					pb = fcn_00508e40(*(int*) (b + 0x5c));
					if (pa != 0 && pa[8] > 0 && b[2] != 5) {
						fcn_0051af00(line, 0x1ceb, *(unsigned short*) pa, *(unsigned short*) a);
						fcn_0051af00(line + strlen(line), 0x1cec);
						fcn_0051af00(line + strlen(line), 0x1cf2, *(unsigned short*) b);
						fcn_0051af00(line + strlen(line), 0x1ced, *(unsigned short*) pb);
						fcn_0051af00(line + strlen(line), 0x1cf0, *(unsigned short*) pa);
					} else {
						fcn_0051af00(line, 0x1ceb, *(unsigned short*) b, *(unsigned short*) a);
						fcn_0051af00(line + strlen(line), 0x1cec);
						fcn_0051af00(line + strlen(line), 0x1cf1);
						fcn_0051af00(line + strlen(line), 0x1ced, *(unsigned short*) pb);
						fcn_0051af00(line + strlen(line), 0x1cf0, *(unsigned short*) b);
					}
					fcn_00545d40(*(int*) (a + 4), *(int*) (a + 4), line, 1, 0x5f4, 0);
				}
				*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
				goto Lsend;
			}
			if (v == 1) {
				e[0xb9] = (char) fcn_005d2a40(*(int*) (e + 0xac), *(int*) (e + 0xb0));
				e[0xb8] = e[0xb8] + 1;
			}
			if (e[0xb8] >= e[0xb9]) {
				*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
				fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
				*(int*) (e + 0x84) = fcn_004c5620(1, e);
				return;
			}
			if (a[2] == 6) {
				fcn_0051af00(line, 0x1cf3);
				fcn_0051af00(line + strlen(line), 0x1cf4, *(unsigned short*) b, 0x5d,
				    (int) e[0xb9] - (int) e[0xb8], 0x5d);
				fcn_00545d40(*(int*) (a + 4), *(int*) (a + 4), line, 0, 0x5f4, 0);
			} else if (a[2] == 5) {
				e[0xb8] = e[0xb8] + (char) gm_RandomMod(2) + 1;
			} else if (gm_RandomMod(4) == 0) {
				e[0xb8] = e[0xb8] + 1;
			}
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0x18, 0, 0);
			*(unsigned short*) (e + 0x56) = 8;
			e[0xba] = 1;
			fcn_0054c720(e, a, b);
			*(int*) (e + 0x84) = -1;
			fcn_004c5620(0, e);
			return;
		}
		if (a[2] != 6) {
			goto Lneg;
		}
		pa = fcn_00508e40(*(int*) (b + 0x60));
		pb = fcn_00508e40(*(int*) (b + 0x5c));
		if (pa != 0 && pa[8] > 0 && b[2] != 5) {
			fcn_0051af00(line, 0x1ceb, *(unsigned short*) pa, *(unsigned short*) a);
			fcn_0051af00(line + strlen(line), 0x1cee);
			fcn_0051af00(line + strlen(line), 0x1cf2, *(unsigned short*) b);
			fcn_0051af00(line + strlen(line), 0x1cef, *(unsigned short*) pb);
			fcn_0051af00(line + strlen(line), 0x1cf0, *(unsigned short*) pa);
		} else {
			fcn_0051af00(line, 0x1ceb, *(unsigned short*) b, *(unsigned short*) a);
			fcn_0051af00(line + strlen(line), 0x1cee);
			fcn_0051af00(line + strlen(line), 0x1cf1);
			fcn_0051af00(line + strlen(line), 0x1cef, *(unsigned short*) pb);
			fcn_0051af00(line + strlen(line), 0x1cf0, *(unsigned short*) b);
		}
		fcn_00545d40(*(int*) (a + 4), *(int*) (a + 4), line, 1, 0x5f4, 0);
		goto Lneg;
	case 1:
		fcn_004c4eb0(g_6a5a48);
		fcn_004c4510(b, *(int*) (b + 4));
		fcn_004c4570(4, 1, 0x5c, a + 4);
		fcn_004c4570(2, 1, 0x50, a + 0x50);
		fcn_004c5360();
		fcn_004c4510(a, *(int*) (a + 4));
		fcn_004c4570(4, 1, 0x5c, b + 4);
		fcn_004c5360();
		fcn_004c5420(*(int*) (b + 4), 0x1c8, 4, 0x40000, 0);
		fcn_004c5420(*(int*) (a + 4), 0x1c8, 4, 0x40000, 0);
		fcn_004c4ef0(g_6a5a48);
		*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 1, 0);
		*(int*) (e + 0x84) = fcn_004c5620(5, e);
		return;
	case 2:
	case 3:
		return;
	case 4:
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
		*(int*) (e + 0x84) = fcn_004c5620(-1, e);
		return;
	case 5:
		if (*(int*) (a + 0x5c) != *(int*) (b + 4) || *(int*) (b + 0x5c) != *(int*) (a + 4)) {
			if (a[2] != 6) {
				goto Lneg;
			}
			pa = fcn_00508e40(*(int*) (b + 0x60));
			pb = fcn_00508e40(*(int*) (b + 0x5c));
			if (pa != 0 && pa[8] > 0 && b[2] != 5) {
				fcn_0051af00(line, 0x1ceb, *(unsigned short*) pa, *(unsigned short*) a);
				fcn_0051af00(line + strlen(line), 0x1cee);
				fcn_0051af00(line + strlen(line), 0x1cf2, *(unsigned short*) b);
				fcn_0051af00(line + strlen(line), 0x1cef, *(unsigned short*) pb);
				fcn_0051af00(line + strlen(line), 0x1cf0, *(unsigned short*) pa);
			} else {
				fcn_0051af00(line, 0x1ceb, *(unsigned short*) b, *(unsigned short*) a);
				fcn_0051af00(line + strlen(line), 0x1cee);
				fcn_0051af00(line + strlen(line), 0x1cf1);
				fcn_0051af00(line + strlen(line), 0x1cef, *(unsigned short*) pb);
				fcn_0051af00(line + strlen(line), 0x1cf0, *(unsigned short*) b);
			}
			fcn_00545d40(*(int*) (a + 4), *(int*) (a + 4), line, 1, 0x5f4, 0);
			goto Lneg;
		}
		fcn_004c54c0(*(int*) (a + 4), *(int*) (b + 4), 0x7f - g_869480[*(unsigned short*) a][*(unsigned short*) b], 1);
		fcn_004c54c0(*(int*) (b + 4), *(int*) (a + 4), 0x7f - g_869480[*(unsigned short*) b][*(unsigned short*) a], 1);
		if (a[2] == 6 || a[2] == 5) {
			pb = a;
			if (a[9] != 1) {
				pb = b;
			}
			fcn_0051af00(buf, 0x1d31, *(unsigned short*) b);
			fcn_00545d40(*(int*) (a + 4), *(int*) (a + 4), buf, 0, 0x5f4, 0);
			fcn_004c5480(*(int*) (pb + 4), 0x7c, g_664174 - *(float*) (pb + 0x7c));
		}
		if (fcn_004f46e0((int) b, &rec, &hit) != 0) {
			v = fcn_004f1790(*(int*) (rec + 0x65), hit);
			fcn_004f2a10(0, (char*) rec, *(int*) hit, v);
		}
		memset(msg, 0, sizeof(msg));
		*(int*) (msg + 0x34) = *(int*) (a + 4);
		*(int*) (msg + 0x38) = *(int*) (b + 4);
		*(int*) (msg + 0x18) = g_7f4c00.a;
		msg[8] = 6;
		msg[0x26] = 0xb2;
		*(int*) (msg + 0x14) = -1;
		msg[0x30] = 2;
		*(short*) (msg + 0x24) = g_7f4c00.d;
		*(int*) (msg + 0x0c) = *(int*) (g_7f4ca4 + (unsigned short) g_774970 * 0x21c);
		*(int*) (msg + 0x1c) = g_7f4c00.b;
		*(int*) (msg + 0x20) = g_7f4c00.c;
		fcn_00500bb0((pos14_7f4c00*) (msg + 0x18), 2, 0, 0);
		*(int*) (msg + 0x1e) = 0;
		if (*(unsigned short*) (msg + 0x1c) > 0x16) {
			*(int*) (msg + 0x18) = *(int*) (msg + 0x18) + 1;
			*(unsigned short*) (msg + 0x1c) = 0xb;
		} else if (*(unsigned short*) (msg + 0x1c) < 7) {
			*(unsigned short*) (msg + 0x1c) = 0xb;
		}
		e[0xbb] = 1;
		*(pos14_7f4c00*) (e + 0x52) = *(pos14_7f4c00*) (msg + 0x18);
		*(int*) (e + 0x84) = -1;
		fcn_004c5620(4, e);
		fcn_004c5980(msg);
		return;
	default:
		return;
	}
tail:
	if ((e[0x78] & 2) != 0) {
		if (b != 0 && (*(int*) (b + 0x1c8) & 0x40000) != 0) {
			if (a != 0) {
				goto tail_locked;
			}
			fcn_004c5420(*(int*) (b + 4), 0x1c8, 4, 0, 0x40000);
			goto tail_done;
		}
		if (a == 0) {
			goto tail_done;
		}
tail_locked:
		if ((*(int*) (a + 0x1c8) & 0x40000) != 0 && b == 0) {
			fcn_004c5420(*(int*) (a + 4), 0x1c8, 4, 0, 0x40000);
		}
	}
tail_done:
	fcn_00546190(e);
	return;
Lneg:
	*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
Lsend:
	fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
	*(int*) (e + 0x84) = fcn_004c5620(-1, e);
}
#pragma optimize("", on)
