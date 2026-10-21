#include "client_types.h"

#include "Develop/DieGildeAddOn/game/entity.h"

#pragma pack(1)
/* message record handed to fcn_004c6be0 */
typedef struct {
	pos14_7f4c00 stamp;	/* +0x00 */
	int f0e;		/* +0x0e */
	int f12;		/* +0x12 */
	int f16;		/* +0x16 */
	char f1a;		/* +0x1a */
	char f1b;		/* +0x1b */
} Msg56;
// SIZE 0x1c
#pragma pack()

extern pos14_7f4c00 g_7f4c00;
extern unsigned char g_773d75;

extern unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
extern char* __cdecl fcn_00508e40(int id);
extern void __cdecl fcn_004c5c80(int a1);
extern void __cdecl fcn_004c5da0(int, int, int, char*, int, char*);
extern void __cdecl fcn_00529160(char*, char*, unsigned int, char*);
extern void __cdecl fcn_00500bb0(pos14_7f4c00*, int, int, int);
extern int __cdecl fcn_00529670(char*, char*);
extern int __cdecl fcn_00507e30(char*, int);
extern int __cdecl fcn_0050c4e0(unsigned char*);
extern void __cdecl fcn_00546190(char*);
extern unsigned short* __cdecl fcn_00502cd0(int, int, ...);
extern int __cdecl gm_WalkEntityChain(unsigned short raw_idx);
extern int __cdecl fcn_0050df70(char*, char*);
extern float __cdecl fcn_0050bb50(int, unsigned char);
extern void* __cdecl fcn_00502850(void);
extern int __cdecl gm_RandomMod(int);
extern int __cdecl fcn_0050c710(unsigned char*, int, int);
extern void __cdecl fcn_004c6be0(char*, char*);
extern char* __cdecl fcn_0050dc90(char*);
extern unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
extern int __cdecl fcn_005049a0(unsigned char*);
extern void __cdecl fcn_0051af00(char*, int, ...);
extern void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, char*, char*);

/* ADDRESS: GOLDTL 0x0056aef0 */
void __cdecl fcn_0056aef0(char* a1)
{
	int* p;
	char* e;
	char* q;
	char* h;
	char* h2;
	char* r;
	char* ent;
	char* u;
	int n;
	int v;
	int t;
	int k;
	int i;
	double d;
	Msg56 m;
	char buf[0x400];

	v = 0;
	u = 0;
	switch (*(int*)(a1 + 0x70)) {
	case -2:
	case -1:
		h = (char*)gm_StartFilteredEntitySearch(*(int*)(a1 + 0xb0), 1, 1);
		if (h != 0) {
			q = (char*)gm_SetupEntityQuery((unsigned char*)h);
		}
		p = (int*)(a1 + 0x8c);
		n = 8;
		do {
			e = (char*)fcn_00508e40(*p);
			if (e != 0) {
				fcn_004c5c80(*p);
				if (h != 0) {
					fcn_004c5da0(*p, *(int*)(h + 1), *(int*)(q + 2), 0, 0, "GebSpionage");
				}
				fcn_00529160(0, 0, *(unsigned short*)e, 0);
			}
			p++;
			n--;
		} while (n != 0);
		fcn_00546190(a1);
		return;

	case 0:
		h = (char*)gm_StartFilteredEntitySearch(*(int*)(a1 + 0xac), 1, 1);
		if (h == 0) {
			*(int*)(a1 + 0x70) = -1;
			return;
		}
		p = (int*)(a1 + 0x8c);
		n = 8;
		do {
			e = (char*)fcn_00508e40(*p);
			if (e != 0) {
				fcn_004c5c80(*(int*)(e + 4));
				fcn_004c5da0(*(int*)(e + 4), *(int*)(h + 1), -1, 0, 1, "GebSpionage");
				fcn_00529160(h, 0, *(unsigned short*)e, a1);
			}
			p++;
			n--;
		} while (n != 0);
		*(pos14_7f4c00*)(a1 + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*)(a1 + 0x52), 0, 0xa, 0);
		*(int*)(a1 + 0x70) = 1;
		return;

	case 1:
		v = 1;
		h = (char*)gm_StartFilteredEntitySearch(*(int*)(a1 + 0xac), 1, 1);
		if (h == 0) {
			*(int*)(a1 + 0x70) = -1;
			return;
		}
		p = (int*)(a1 + 0x8c);
		n = 8;
		do {
			e = (char*)fcn_00508e40(*p);
			if (e != 0 && *(int*)(e + 0x184) != 0) {
				if (fcn_00529670(e, h) == 0) {
					e = *(char**)(e + 0x184);
					if (*(int*)(e + 0x128) != 0) {
						v = 0;
					}
				}
			}
			p++;
			n--;
		} while (n != 0);
		if (v == 0) {
			*(pos14_7f4c00*)(a1 + 0x52) = g_7f4c00;
			fcn_00500bb0((pos14_7f4c00*)(a1 + 0x52), 0, 5, 0);
			return;
		}
		t = 0;
		k = 0;
		p = (int*)(a1 + 0x8c);
		n = 8;
		do {
			e = (char*)fcn_00508e40(*p);
			if (e != 0) {
				t += fcn_00507e30(e, 2);
				k++;
			}
			p++;
			n--;
		} while (n != 0);
		if (k == 0) {
			fcn_00546190(a1);
			return;
		}
		t = t / k;
		d = ((double)t > 1.0) ? 1.0 : (double)t;
		h = (char*)gm_StartFilteredEntitySearch(*(int*)(a1 + 0xac), 1, 1);
		if (h == 0) {
			*(int*)(a1 + 0x70) = -1;
			return;
		}
		v = fcn_0050c4e0((unsigned char*)h);
		i = (int)d;
		d = (double)v * 120.0 * (252.0 / (double)i) / (double)k;
		if (d > 2880.0) {
			d = 2880.0;
		}
		i = (int)d;
		*(pos14_7f4c00*)(a1 + 0x44) = g_7f4c00;
		*(pos14_7f4c00*)(a1 + 0x52) = g_7f4c00;
		fcn_00500bb0((pos14_7f4c00*)(a1 + 0x52), 0, i, 0);
		*(int*)(a1 + 0x70) = 2;
		return;

	case 2:
		h = (char*)gm_StartFilteredEntitySearch(*(int*)(a1 + 0xb0), 1, 1);
		if (h == 0) {
			*(int*)(a1 + 0x70) = -1;
			return;
		}
		i = *(unsigned short*)(h + 0x27);
		ent = (char*)fcn_00508e40(*(int*)((char*)g_slot_table + i * 0x21c + 4));
		q = (char*)gm_SetupEntityQuery((unsigned char*)h);
		t = 0;
		k = 0;
		p = (int*)(a1 + 0x8c);
		n = 8;
		do {
			e = (char*)fcn_00508e40(*p);
			if (e != 0) {
				t += fcn_00507e30(e, 2);
				u = e;
				fcn_004c5c80(*p);
				fcn_004c5da0(*p, *(int*)(h + 1), *(int*)(q + 2), 0, 0, "GebSpionage");
				fcn_00529160(h, 0, *(unsigned short*)e, 0);
				k++;
			}
			p++;
			n--;
		} while (n != 0);
		if (k == 0) {
			fcn_00546190(a1);
			return;
		}
		t = t / k;
		if (t > 42) {
			t = 42;
		}
		h2 = (char*)gm_StartFilteredEntitySearch(*(int*)(a1 + 0xac), 1, 1);
		if (h2 == 0) {
			*(int*)(a1 + 0x70) = -1;
			return;
		}
		i = *(unsigned short*)(h2 + 0x27);
		r = (char*)g_slot_table + i * 0x21c;
		q = (char*)fcn_00502cd0(*(int*)(h2 + 0x5d), 2, 6, 0, 0x2a);
		i = gm_WalkEntityChain(*(unsigned short*)r);
		if (i >= 100000) {
			i = 100000;
		}
		m.f12 = (int)((double)i * 0.1);
		v = 0;
		if (q != 0) {
			e = (char*)fcn_00502cd0(*(int*)(q + 0x14), 1, 5);
			while (e != 0) {
				v = (int)(fcn_0050bb50(*(unsigned short*)e, g_773d75) * (float)fcn_0050df70(q, e) + (float)v);
				e = (char*)fcn_00502850();
			}
		}
		i = (int)((double)k * (double)t * 0.25 / (double)fcn_0050c4e0((unsigned char*)h2));
		k = i + (gm_RandomMod(4) & 0xffff) - 2;
		if (k > 100) {
			k = 100;
		} else if (k < 2) {
			k = 2;
		}
		m.stamp = g_7f4c00;
		m.f0e = *(int*)(h2 + 1);
		m.f16 = v;
		m.f1a = (char)fcn_0050c710((unsigned char*)h2, 7, 1);
		m.f1b = (char)k;
		fcn_004c6be0(h, (char*)&m);
		e = (char*)fcn_0050dc90(h);
		if (*(char*)(ent + 2) == 6 || *(char*)(ent + 2) == 7) {
			if (u != 0) {
				if (e == 0 || (e[0x1b4] & 1) == 0) {
					fcn_0051af00(buf, 0x19f8, *(unsigned short*)u, *(unsigned short*)r, h2);
					i = fcn_005049a0((unsigned char*)h);
					he_MessageBoxQuickjump(*(int*)(ent + 4), *(int*)(ent + 4), buf, 1, 0x5f0,
						*(int*)(a1 + 0xb0), *(int*)((char*)i + 2), 0, "_NACHRICHTEN_HS_78");
				}
			}
		}
		fcn_00546190(a1);
		return;

	default:
		break;
	}
	fcn_00546190(a1);
}
