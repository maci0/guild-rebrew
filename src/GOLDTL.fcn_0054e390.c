#include <string.h>

#include "client_types.h"

extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];
extern char g_7f4ca4[];
extern int g_774800;
extern unsigned short g_774970;
extern double g_6640e8;
extern double g_6629c8;
extern double g_662c38;
extern float g_662cf8;
extern float g_665e88;

char* __cdecl fcn_00503fe0(int, int, int);
char* __cdecl fcn_00508e40(int);
char* __cdecl fcn_00502cd0(int, int, ...);
char* __cdecl fcn_00502850(void);
char* __cdecl fcn_00504b30(char*);
char* __cdecl fcn_004e6a30(int);
int __cdecl fcn_0050c710(char*, int, int);
int __cdecl fcn_0042e410(int);
int __cdecl fcn_004d5450(char*);
int __cdecl fcn_004d5110(char*, char*, char*, char*);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_004c4480(int);
void __cdecl fcn_004c5c80(int);
int __cdecl fcn_004c5da0(int, int, int, char*, int, char*);
int __cdecl fcn_004c5620(char, char*);
int __cdecl fcn_004c5980(void*);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
void __cdecl fcn_00545e80(int, int, char*, int, int, int, int, char*, char*);
void __cdecl fcn_00529160(char*, char*, unsigned int, char*);
void __cdecl fcn_00546190(char*);

/* ADDRESS: GOLDTL 0x0054e390 */
void __cdecl fcn_0054e390(char* e)
{
	int n;
	float f = 1.0f;
	int i;
	char* q;
	char pkt[0x114];
	char text[0x800];

	n = 0;
	if (*(int*) (e + 0x70) == -2) {
		if (!(e[0x78] & 2)) {
			fcn_00546190(e);
			return;
		}
		n = 1;
		*(int*) (e + 0x70) = 1;
	}
	if (*(int*) (e + 0x84) != -1 && !fcn_004c4450(*(int*) (e + 0x84))) {
		return;
	}
	*(int*) (e + 0x84) = -1;
	switch (*(int*) (e + 0x70)) {
	case 0:
		{
			char* own;
			char* u;
			char* p;

			own = fcn_00503fe0(1, 1, *(int*) (e + 0xac));
			if (own == 0 || *(short*) (own + 0x27) == -1) {
				goto label_54e513;
			}
			p = e + 0x8c;
			i = 8;
			do {
				if (*(int*) p != -1) {
					u = fcn_00508e40(*(int*) p);
					if (u != 0) {
						fcn_00529160(own, 0, *(unsigned short*) u, e);
						fcn_004c5c80(*(int*) p);
						fcn_004c5da0(*(int*) p, *(int*) (own + 1), -1, 0, 0, (char*) 0x6a5ad8);
					} else {
						*(int*) p = -1;
					}
				}
				p += 4;
				i--;
			} while (i != 0);
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
			*(int*) (e + 0x84) = fcn_004c5620(2, e);
			return;
		}
	case 1:
		{
			char* own;
			char* slot;
			char* u;
			char* p;

			if (!(e[0x78] & 2)) {
				return;
			}
			own = fcn_00503fe0(1, 1, *(int*) (e + 0xb0));
			if (own == 0) {
				goto label_54e513;
			}
			slot = fcn_00502cd0(*(int*) (own + 0x5d), 1, 0, 0x146);
			p = e + 0x8c;
			i = 8;
			do {
				if (*(int*) p != -1) {
					u = fcn_00508e40(*(int*) p);
					if (u != 0 && *(char*) (u + 8) > 0) {
						fcn_004c5c80(*(int*) p);
						fcn_004c5da0(*(int*) p, *(int*) (own + 1), *(int*) (slot + 2), 0, 0,
						             (char*) 0x6a5ad8);
						fcn_00529160(own, 0, *(unsigned short*) u, e);
					} else {
						*(int*) p = -1;
					}
				}
				p += 4;
				i--;
			} while (i != 0);
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
			if (!n) {
				*(int*) (e + 0x84) = fcn_004c5620(-1, e);
				return;
			}
			break;
		}
	case 2:
		{
			char* u;
			char* p;
			int i;
			int s;

			s = 1;
			i = 0;
			p = e + 0x8c;
			do {
				if (*(int*) p != -1) {
					u = fcn_00508e40(*(int*) p);
					if (u != 0 && *(int*) (*(int*) (u + 0x184) + 0x128) != 0) {
						break;
					}
				}
				i++;
				p += 4;
				if (i >= 8) {
					goto label_54e6a1;
				}
			} while (1);
			s = 0;
label_54e6a1:
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 2, 0);
			if (!s) {
				*(int*) (e + 0x84) = fcn_004c5620(2, e);
				return;
			}
			*(int*) (e + 0x84) = fcn_004c5620(3, e);
			return;
		}
	case 3:
		{
			char* own;
			char* other;
			char* rec;
			char* p;
			int v;
			int m;
			int k;

			if (!(e[0x78] & 2)) {
				return;
			}
			own = fcn_00503fe0(1, 1, *(int*) (e + 0xac));
			v = fcn_0050c710(own, 5, 1);
			rec = fcn_00502cd0(*(int*) (fcn_00503fe0(1, 1, *(int*) (e + 0xb0)) + 0x5d), 1, 0, 0xca);
			while (rec != 0) {
				if (*(int*) (rec + 0x2a) == *(int*) (own + 1)) {
					f = (float) ((*(unsigned char*) (rec + 0x37) + g_662c38) * g_6640e8);
					break;
				}
				rec = fcn_00502850();
			}
			if (g_774800) {
				f = 5.0f;
			}
			if (f * g_662cf8 + (float) (fcn_0042e410(0x4b) & 0xffff)
			    <= (float) ((double) v * g_6640e8 + g_6629c8) * g_665e88) {
				other = fcn_00503fe0(1, 1, *(int*) (e + 0xb0));
				m = fcn_004d5450(other) + 0x1125;
				fcn_0051af00(text, 0x114b, m, *(unsigned short*) (own + 0x27), own, m);
				fcn_00545d40(*(int*) (g_7f4ca4 + *(unsigned short*) (e + 8) * 0x21c), -1, text, 0, 0x5f0, 0);
				k = *(unsigned char*) (g_7f4ca4 + *(unsigned short*) (own + 0x27) * 0x21c - 2);
				if (k == 6 || k == 7) {
					fcn_0051af00(text, 0x1c56, own);
					fcn_00545e80(*(int*) (g_7f4ca4 + *(unsigned short*) (own + 0x27) * 0x21c), -1, text, 0,
					             0x5f0, *(int*) (own + 1), -1, 0, 0);
				}
				*(int*) (e + 0x70) = -1;
				return;
			}
			memset(pkt, 0, sizeof(pkt));
			pkt[8] = 3;
			pkt[0x26] = 0xa2;
			*(int*) (pkt + 0x14) = *(int*) (own + 1);
			pkt[0x30] = 2;
			pkt[0x7c] = 2;
			*(int*) (pkt + 0x0c) = *(int*) (g_7f4ca4 + (unsigned short) g_774970 * 0x21c);
			p = g_7f4ca0 + *(unsigned short*) (e + 8) * 0x21c;
			*(int*) (pkt + 0x34) = *(int*) (p + 4);
			*(int*) (pkt + 0x38) = *(int*) (own + 4);
			i = 0;
			do {
				*(int*) (pkt + 0x80 + i * 4) = -1;
				*(int*) (pkt + 0xc0 + i * 4) = -1;
				i++;
			} while (i < 16);
			i = 0;
			for (p = (char*) 0x7f4e0c; p < (char*) 0x85a20c; p += 0x21c) {
				if (i >= 0x10 || i >= 6) {
					break;
				}
				if (*(char*) (p - 0x164) != 0 && *(char**) p == own) {
					*(int*) (pkt + 0x80 + i * 4) = *(int*) (p - 0x168);
					i++;
				}
			}
			*(int*) (pkt + 0x100) = -1;
			*(int*) (pkt + 0x104) = -1;
			*(int*) (pkt + 0x108) = -1;
			*(int*) (pkt + 0x10c) = *(int*) (fcn_00503fe0(1, 1, *(int*) (e + 0xb0)) + 1);
			m = 0;
			k = 0;
			p = e + 0x8c;
			do {
				if (m >= 6) {
					break;
				}
				if (*(int*) p != -1) {
					*(int*) (pkt + 0xc0 + m * 4) = *(int*) p;
					m++;
				}
				k++;
				p += 4;
			} while (k < 8);
			if (m != 0 && i != 0) {
				*(pos14_7f4c00*) (pkt + 0x18) = g_7f4c00;
				fcn_00500bb0((pos14_7f4c00*) (pkt + 0x18), 0, 0x1e, 0);
				*(int*) (e + 0xb4) = fcn_004c5980(pkt);
				*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
				fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 0, 1);
				*(int*) (e + 0x70) = 4;
				return;
			}
			other = fcn_00503fe0(1, 1, *(int*) (e + 0xb0));
			own = fcn_00503fe0(1, 1, *(int*) (e + 0xac));
			m = fcn_004d5110(own, other, g_7f4ca0 + *(unsigned short*) (e + 8) * 0x21c,
			                 g_7f4ca0 + *(unsigned short*) (own + 0x27) * 0x21c);
			k = *(unsigned char*) (g_7f4ca4 + *(unsigned short*) (own + 0x27) * 0x21c - 2);
			if (k == 6 || k == 7) {
				fcn_0051af00(text, 0x1c54, own, m);
				fcn_00545e80(*(int*) (g_7f4ca4 + *(unsigned short*) (own + 0x27) * 0x21c), -1, text, 0,
				             0x5f0, *(int*) (own + 1), -1, 0, 0);
			}
			k = *(unsigned char*) (g_7f4ca4 + *(unsigned short*) (e + 8) * 0x21c - 2);
			if (k == 6 || k == 7) {
				fcn_0051af00(text, 0x1c55, *(unsigned short*) (own + 0x27), own, m);
				fcn_00545d40(*(int*) (g_7f4ca4 + *(unsigned short*) (e + 8) * 0x21c), -1, text, 0, 0x5f0, 0);
			}
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 0, 1);
			*(int*) (e + 0x70) = 1;
			return;
		}
	case 4:
		{
			int id;

			id = *(int*) (e + 0xb4);
			if (fcn_004c4450(id)) {
				*(int*) (e + 0xb8) = *(int*) fcn_004c4480(*(int*) (e + 0xb4));
				*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
				fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 1, 0);
				*(int*) (e + 0x70) = 5;
			}
			return;
		}
	case 5:
		{
			int id;

			id = *(int*) (e + 0xb8);
			if (!fcn_004e6a30(id)) {
				*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
				fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 0, 1);
				*(int*) (e + 0x70) = 1;
				return;
			}
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 5, 0);
			return;
		}
	case -1:
		{
			char* own;
			char* slot;
			char* u;
			char* p;

			if (!(e[0x78] & 2)) {
				break;
			}
			own = fcn_00503fe0(1, 1, *(int*) (e + 0xb0));
			slot = fcn_00504b30(own);
			p = e + 0x8c;
			i = 8;
			do {
				if (*(int*) p != -1) {
					u = fcn_00508e40(*(int*) p);
					if (u != 0) {
						fcn_004c5c80(*(int*) p);
						fcn_004c5da0(*(int*) p, *(int*) (own + 1), *(int*) (slot + 2), 0, 0,
						             (char*) 0x6a5ad8);
						fcn_00529160(own, 0, *(unsigned short*) u, 0);
					}
				}
				p += 4;
				i--;
			} while (i != 0);
			break;
		}
	default:
		return;
	}
	fcn_00546190(e);
	return;
label_54e513:
	*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
	fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 1, 0);
	*(int*) (e + 0x84) = fcn_004c5620(-1, e);
}
