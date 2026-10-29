#include "client_types.h"

extern unsigned char g_14cf950;
extern char g_6b5c60[];
extern char* g_7e2aa0;
extern char* g_7ea360;
extern char g_7f4ca0[];
extern unsigned char g_7f4e51[];
extern pos14_7f4c00 g_7f4c00;
extern int g_774664;
extern char* g_7746c4;
extern unsigned char* g_7746c8;
extern char* g_7746cc;
extern int g_7747b0;
extern int g_774804;
extern unsigned short g_774970;

void __cdecl fcn_00406340(char*, char*, int);
void __cdecl CreateAnimationEvent(char*, char*);
int __cdecl fcn_00406670(char*, char*);
void __cdecl fcn_00407800(char*, int, char*);
void __cdecl m_FreeTracked(void*);
int __cdecl gm_RandomMod(int);
void __cdecl d3_DestroyObject(int);
void __cdecl fcn_004b3b30(void);
void __cdecl fcn_004c5530(void*);
int __cdecl fcn_004c5790(int, void*);
void __cdecl fcn_004c5980(void*);
int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
int __cdecl fcn_004c6470(int, int);
int __cdecl fcn_004c64b0(int, int, int, int, int, int, char*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_00535960(void);

/* ADDRESS: GOLDTL 0x00535ec0 */
void __cdecl fcn_00535ec0(void)
{
	unsigned short si;
	int i;
	int n;
	int e;
	char* p;
	char* m;
	char* l;
	unsigned char cx;

	switch (g_14cf950) {
	case 0x11:
		if (g_7746c8 == 0 && g_7746c4 == 0) {
			return;
		}
		e = 0;
		if (g_7746c8 != 0) {
			e = (int) g_7746c8;
		} else if (g_7746c4 != 0) {
			e = (int) g_7746c4;
		}
		n = fcn_004c64b0(0, *(int*) (e + 1), *(int*) (g_7746cc + 2), 0, 4, 0,
		    g_6b5c60);
		if (fcn_004c4450(n) == 0) {
			do {
				fcn_00535960();
			} while (fcn_004c4450(n) == 0);
		}
		p = fcn_004c4480(n);
		m = *(char**) (p + 0x184);
		if (m != 0) {
			m[0x8d] |= 0x10;
			fcn_00407800(m, 2, "ub_BIERKRUG");
			CreateAnimationEvent(*(char**) (p + 0x184), "sitzend/hinsetzen");
			fcn_00406340(*(char**) (p + 0x184), "sitzend/sitz_schreiben", 4);
		}
		return;
	case 0x16:
		i = g_774664;
		*(int*) (i * 0x2f4 + 0x7f4cc4) += gm_RandomMod(0x80) & 0xffff;
		return;
	case 0x17:
		fcn_004b3b30();
		return;
	case 0x19:
		fcn_004c6470(*(int*) (g_774970 * 0x2f4 + 0x7f4ca4), 1);
		return;
	case 0x1e:
		p = (char*) (g_774970 * 0x2f4 + 0x7f4e06);
		*p = *p != 0 ? 0 : 0x0f;
		if (g_7ea360 == 0) {
			return;
		}
		fcn_00406120(*(char**) (g_7ea360 + 0x184));
		m = *(char**) (g_7ea360 + 0x184);
		if (*(unsigned char*) (m + 0x8c) & 0x10) {
			fcn_00406670(m, "sitzend/aufstehen");
			return;
		}
		CreateAnimationEvent(m, "sitzend/hinsetzen");
		fcn_00406340(*(char**) (g_7ea360 + 0x184), "sitzend/sitz_schreiben", 6);
		return;
	case 0x1f: {
		int buf[0x1f];

		if ((g_7747b0 & 4) == 0) {
			return;
		}
		for (i = 0; i < 0x1f; i++) {
			buf[i] = 0;
		}
		buf[0] = -1;
		fcn_004c5790(0x11, buf);
		return;
	}
	case 0x20: {
		char buf[0x114];
		int* l2;

		for (i = 0; i < 0x45; i++) {
			((int*) buf)[i] = 0;
		}
		si = g_774970;
		*(unsigned char*) (buf + 8) = 4;
		*(unsigned char*) (buf + 0x26) = 0x22;
		*(int*) (buf + 0x14) = -1;
		l2 = (int*) (buf + 0x34);
		*l2 = *(int*) (si * 0x2f4 + 0x7f4ca4);
		*(int*) (buf + 0x0c) = *l2;
		n = 1;
		p = (char*) 0x7f4ca0;
		while (n < 2) {
			cx = *(unsigned short*) p;
			if (cx != 0xffff && *(unsigned char*) (p + 0x166) != 0 && si != cx) {
				l2[n] = *(int*) (p + 4);
				n++;
			}
			p += 0x21c;
			if (p >= (char*) 0x85a0a0) {
				break;
			}
		}
		*(pos14_7f4c00*) (buf + 0x18) = g_7f4c00;
		*(unsigned char*) (buf + 0x7c) = 0;
		fcn_00500bb0((pos14_7f4c00*) (buf + 0x18), 0, 0x1e, 0);
		fcn_004c5980(buf + 0x0c);
		return;
	}
	case 0x22:
		if (g_7ea360 == 0) {
			return;
		}
		m_FreeTracked(*(void**) (g_7ea360 + 0x184));
		*(int*) (g_7ea360 + 0x184) = 0;
		return;
	case 0x23:
		p = (char*) (g_774970 * 0x2f4 + 0x7f4ca2);
		if (*(int*) (g_774970 * 0x2f4 + 0x7f4cfc) != -1) {
			return;
		}
		n = g_774970 + 1;
		if (n >= 0xff) {
			return;
		}
		{
			char* q;

			q = (char*) (n * 0x2f4 + 0x7f4ca2);
			while (1) {
				if (*(unsigned char*) (q + 7) == 1 && *(unsigned char*) q != 0x0a
				    && *(int*) (q + 0x5a) == -1) {
					break;
				}
				q += 0x21c;
				n++;
				if (q >= (char*) 0x816686) {
					return;
				}
			}
			*q = 8;
			*(int*) (q + 0x5a) = *(int*) (g_774970 * 0x2f4 + 0x7f4ca4);
			*(unsigned short*) (q + 0x4e) = *(unsigned short*) (g_774970 * 0x2f4 + 0x7f4cf0);
			*(int*) (g_774970 * 0x2f4 + 0x7f4cfc) = *(int*) (q + 2);
			*(unsigned char*) (g_774970 * 0x2f4 + 0x7f4ca8) = 0;
		}
		return;
	case 0x24:
		g_7f4e51[g_774970 * 0x21c] = 2;
		return;
	case 0x25: {
		char buf[0xf8];

		if (g_7ea360 == 0) {
			return;
		}
		for (i = 0; i < 0x3e; i++) {
			((int*) buf)[i] = 0;
		}
		*(unsigned char*) (buf + 4) = 0x72;
		*(int*) (buf + 0x0c) = -1;
		*(unsigned char*) (buf + 0x36) = 2;
		*(int*) (buf + 8) = *(int*) (g_774970 * 0x2f4 + 0x7f4ca4);
		*(pos14_7f4c00*) (buf + 0x28) = g_7f4c00;
		*(int*) (buf + 0x58) = *(int*) (g_7ea360 + 4);
		fcn_004c5530(buf);
		return;
	}
	case 0x26:
		if (g_7e2aa0 == 0) {
			return;
		}
		d3_DestroyObject(*(int*) (g_7e2aa0 + 0x61));
		return;
	case 0x2e: {
		char buf[0x114];
		char* q;
		int* l2;

		if (g_774804 != 0) {
			return;
		}
		for (i = 0; i < 0x45; i++) {
			((int*) buf)[i] = 0;
		}
		si = g_774970;
		*(unsigned char*) (buf + 8) = 6;
		*(unsigned char*) (buf + 0x26) = 0x20;
		*(int*) (buf + 0x14) = -1;
		*(unsigned char*) (buf + 0x30) = 2;
		l2 = (int*) (buf + 0x34);
		*l2 = *(int*) (si * 0x2f4 + 0x7f4ca4);
		*(int*) (buf + 0x0c) = *l2;
		q = (char*) 0x7f4ec5;
		n = 1;
		cx = *(unsigned char*) (si * 0x2f4 + 0x7f4ca9);
		do {
			if (*(unsigned char*) q != cx) {
				break;
			}
			q += 0x21c;
			n++;
		} while (q < (char*) 0x85a0a9);
		*(int*) (buf + 0x38) = *(int*) (n * 0x2f4 + 0x7f4ca4);
		*(pos14_7f4c00*) (buf + 0x18) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (buf + 0x18), 0, 0x1e, 0);
		fcn_004c5980(buf + 0x0c);
		return;
	}
	case 0x30: {
		char buf[0x70];

		if (g_7e2aa0 == 0) {
			return;
		}
		*(unsigned char*) (buf + 4) = 0x47;
		*(int*) (buf + 0x0c) = -1;
		*(unsigned char*) (buf + 0x36) = 2;
		*(pos14_7f4c00*) (buf + 0x28) = g_7f4c00;
		*(int*) (buf + 8) = *(int*) (g_774970 * 0x2f4 + 0x7f4ca4);
		*(int*) (buf + 0x5c) = *(int*) (g_774970 * 0x2f4 + 0x7f4ca4);
		*(int*) (buf + 0x58) = *(int*) (*(unsigned short*) (g_7e2aa0 + 0x27) * 0x2f4
		    + 0x7f4ca4);
		*(unsigned short*) (buf + 0x60) = 0x1d6d;
		*(unsigned short*) (buf + 0x62) = 0x1d76;
		fcn_004c5530(buf);
		return;
	}
	default:
		return;
	}
}
unsigned char _dpad_7e6068[17144];
unsigned char _dpad_7ea360[38816];
