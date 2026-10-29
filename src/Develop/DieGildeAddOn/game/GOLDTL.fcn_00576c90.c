#include "Develop/DieGildeAddOn/game/spiel.h"
#include "client_types.h"

extern char g_7f4ca0[];
extern pos14_7f4c00 g_7f4c00;
extern char* g_14b5304;

int __cdecl fcn_004c4450(int);
char* __cdecl fcn_004c4480(int);
int __cdecl fcn_004c5620(int, char*);
char* __cdecl fcn_00508e40(int);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
void __cdecl fcn_0051af00(char*, char*, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
int __cdecl fcn_005779e0(char*, char*, int);
int __cdecl fcn_00577890(char*, char*, int);
int __cdecl fcn_00500d20(char*, char*);
int __cdecl fcn_004c5da0(int, int, int, char*, int, char*);
void __cdecl fcn_004c57e0(int, int);
void __cdecl fcn_004c5c80(int);
int __cdecl fcn_00577af0(int, char*);
char* __cdecl fcn_00577d00(char*, char*, int);
int __cdecl fcn_00577e70(char*, char*, char*);
char* __cdecl fcn_005463a0(int, int, int, int, int);
int __cdecl fcn_004a5e60(unsigned short*, int, int, int, float, float, int*);
void __cdecl fcn_00546190(char*);

/* ADDRESS: GOLDTL 0x00576c90 */
void __cdecl fcn_00576c90(char* e)
{
	char text[0x100];
	char* h;
	char* p;
	char* q;
	char* r;
	int n;
	int c;

	if (*(int*) (e + 0x70) == -1 || *(int*) (e + 0x70) == -2) {
		goto state_minus;
	}
	if (*(unsigned char*) (e + 0x78) & 4) {
		return;
	}
	if (*(int*) (e + 0x84) != -1 && fcn_004c4450(*(int*) (e + 0x84)) == 0) {
		return;
	}
	*(int*) (e + 0x84) = -1;
	h = g_7f4ca0 + *(unsigned short*) (e + 8) * 0x21c;
	switch (*(int*) (e + 0x70)) {
	case 0:
		if (fcn_004c4450(*(int*) (e + 0xcc)) != 1) {
			goto minus_one;
		}
		p = fcn_004c4480(*(int*) (e + 0xcc));
		if (p == 0) {
			goto minus_one;
		}
		*(int*) (e + 0xb8) = *(int*) (p + 4);
		if (*(int*) (e + 0xbc) == 3) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			*(int*) (e + 0x84) = fcn_004c5620(6, e);
			return;
		}
		r = gm_StartFilteredEntitySearch(*(int*) (e + 0xac), 1, 1);
		if (r != 0) {
			*(int*) (e + 0xcc) = fcn_004c5da0(*(int*) (p + 4), *(int*) (r + 1), -1, 0, 1, (char*) 0x6a7e18);
			*(int*) (e + 0x84) = fcn_004c5620(1, e);
			return;
		}
		*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
	minus_one:
		*(int*) (e + 0x84) = fcn_004c5620(-1, e);
		return;
	case 1:
		*(int*) (e + 0xcc) = -1;
		p = fcn_00508e40(*(int*) (e + 0xb8));
		if (p == 0) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			goto minus_one;
		}
		if (*(char**) (*(char**) (p + 0x184) + 0x128) != 0) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 4, 0);
			return;
		}
		if (gm_StartFilteredEntitySearch(*(int*) (e + 0xac), 1, 1) != 0) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 1, 0, 0);
			*(int*) (e + 0x84) = fcn_004c5620(3, e);
			return;
		}
		*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
		goto minus_one;
	case 3:
		p = fcn_00508e40(*(int*) (e + 0xb8));
		if (p == 0) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			goto minus_one;
		}
		q = fcn_00508e40(*(int*) (e + 0xb4));
		r = gm_StartFilteredEntitySearch(*(int*) (e + 0xb0), 1, 1);
		if (h != 0 && q != 0 && r != 0) {
			switch (*(int*) (e + 0xbc)) {
			case 1:
				if (fcn_005779e0(h, q, *(int*) (e + 0xc0)) != 0) {
					fcn_0051af00(text, (char*) 0x4004, *(unsigned short*) q);
					fcn_00545d40(*(int*) (h + 4), -1, text, 1, 0x5fa, (char*) 0x6a7e78);
					fcn_0051af00(text, (char*) 0x4006, *(int*) (e + 0xc0) + 0x4007);
					fcn_00545d40(*(int*) (q + 4), -1, text, 1, 0x5fb, (char*) 0x6a7e60);
				} else {
					fcn_0051af00(text, (char*) 0x4005, *(unsigned short*) q);
					fcn_00545d40(*(int*) (h + 4), -1, text, 1, 0x5fa, (char*) 0x6a7e48);
					fcn_0051af00(text, (char*) 0x400a);
					fcn_00545d40(*(int*) (q + 4), -1, text, 1, 0x5fb, (char*) 0x6a7e60);
				}
				break;
			case 2:
				if (fcn_00577890(h, q, *(int*) (e + 0xc0)) != 0) {
					fcn_0051af00(text, (char*) 0x4019, (char*) 0x400c, *(unsigned short*) q, *(unsigned short*) q);
					fcn_00545d40(*(int*) (h + 4), -1, text, 1, 0x5fa, 0);
				} else {
					fcn_0051af00(text, (char*) 0x401a, (char*) 0x400c, *(unsigned short*) q, *(unsigned short*) q);
					fcn_00545d40(*(int*) (h + 4), -1, text, 1, 0x5fa, 0);
				}
				break;
			case 3:
				*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
				*(int*) (e + 0xc4) = -1;
				*(int*) (e + 0xc8) = 0;
				*(int*) (e + 0x84) = fcn_004c5620(6, e);
				*(int*) (e + 0x84) = fcn_004c5620(4, e);
				return;
			case 4:
				fcn_00577af0(*(int*) (r + 1), q);
				break;
			}
		}
		*(int*) (e + 0x84) = fcn_004c5620(4, e);
		return;
	case 4:
		p = fcn_00508e40(*(int*) (e + 0xb8));
		*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
		if (p == 0) {
			goto minus_one;
		}
		*(int*) (e + 0xcc) = fcn_004c5da0(*(int*) (e + 0xb8), *(int*) (e + 0xb0), -1, 0, 0, (char*) 0x6a7e18);
		*(int*) (e + 0x84) = fcn_004c5620(5, e);
		return;
	case 5:
		p = fcn_00508e40(*(int*) (e + 0xb8));
		if (p == 0) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			goto minus_one;
		}
		if (*(char**) (*(char**) (p + 0x184) + 0x128) != 0) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 4, 0);
			return;
		}
		n = fcn_00500d20(e + 0x44, (char*) &g_7f4c00);
		switch (*(int*) (e + 0xbc)) {
		case 2:
			c = 0x21c;
			break;
		case 4:
			c = 0xb40;
			break;
		default:
			c = 0x5a0;
			break;
		}
		n = c - n;
		if (n <= 5) {
			n = 5;
		}
		*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), n / 60, n % 60, 0);
		fcn_004c57e0(*(int*) (e + 0xb8), 1);
		*(int*) (e + 0x84) = fcn_004c5620(-1, e);
		return;
	case 6:
		n = fcn_00500d20(e + 0x44, (char*) &g_7f4c00);
		if (n > 0x5a0) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			*(int*) (e + 0x84) = fcn_004c5620(4, e);
			return;
		}
		q = fcn_00508e40(*(int*) (e + 0xb8));
		if (q == 0) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			goto minus_one;
		}
		r = fcn_00577d00(h, q, *(int*) (e + 0xc4));
		if (r != 0) {
			*(int*) (e + 0xac) = *(int*) (r + 0xb4);
			*(int*) (e + 0xc4) = *(int*) (r + 4);
			*(int*) (e + 0xc8) = 1;
			fcn_004c5c80(*(int*) (q + 4));
			fcn_004c5da0(*(int*) (q + 4), *(int*) (e + 0xac), -1, 0, 1, (char*) 0x6a7e3c);
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 5, 0);
			*(int*) (e + 0x84) = fcn_004c5620(7, e);
			return;
		}
		fcn_004a5e60((unsigned short*) h, 0, (int) 0xa7f4c7a0, 1, 0.0f, 100.0f, (int*) (e + 0xac));
		*(int*) (e + 0xc4) = -1;
		*(int*) (e + 0xc8) = 0;
		fcn_004c5c80(*(int*) (q + 4));
		fcn_004c5da0(*(int*) (q + 4), *(int*) (e + 0xac), -1, 0, 1, (char*) 0x6a7e3c);
		*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 0xf, 0);
		*(int*) (e + 0x84) = fcn_004c5620(6, e);
		return;
	case 7:
		n = fcn_00500d20(e + 0x44, (char*) &g_7f4c00);
		q = fcn_00508e40(*(int*) (e + 0xb8));
		if (q == 0) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			*(int*) (e + 0x84) = fcn_004c5620(-1, e);
			return;
		}
		if (n > 0x5a0) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			*(int*) (e + 0x84) = fcn_004c5620(4, e);
			return;
		}
		r = fcn_005463a0(2, 0, 0x18, 1, *(int*) (e + 0xc4));
		if (fcn_00577e70(q, e, r) != 0) {
			*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
			*(int*) (e + 0x84) = fcn_004c5620(6, e);
			return;
		}
		fcn_00500bb0((pos14_7f4c00*) (e + 0x52), 0, 6, 0);
		*(pos14_7f4c00*) (e + 0x52) = g_7f4c00;
		*(int*) (e + 0x84) = fcn_004c5620(7, e);
		return;
	}
	return;
state_minus:
	if (*(unsigned char*) (e + 0x78) & 2) {
		if (fcn_00508e40(*(int*) (e + 0xb8)) != 0) {
			fcn_004c57e0(*(int*) (e + 0xb8), 1);
		}
		if (*(int*) (e + 0x70) == -1) {
			fcn_00545d40(*(int*) (g_7f4ca0 + *(unsigned short*) (e + 8) * 0x21c + 4), -1, g_14b5304, 1, 0x5fa, (char*) 0x6a7e24);
		}
	}
	fcn_00546190(e);
}
