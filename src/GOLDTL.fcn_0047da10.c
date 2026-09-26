#pragma pack(2)
typedef struct
{
	int t;
	unsigned short hour;
	unsigned int f6;
	unsigned int f10;
} fcn_0047da10_Stamp;
// SIZE 0xe
#pragma pack()

// SIZE 0x21c
typedef struct
{
	unsigned short id;
	unsigned char kind;
	char pad3;
	int h;
	char pad8[0x24 - 8];
	int gold;
	char pad28[0x1cc - 0x28];
	int flags;
	char pad1d0[0x21c - 0x1d0];
} fcn_0047da10_Ent;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern fcn_0047da10_Stamp g_100dc04;
extern int g_100dc00;
extern float g_100dc14;
extern int g_7747b4;
extern float g_67db50;
extern float g_67db54;
extern unsigned char g_7747b0;
extern char g_7f4ca0[];

int __cdecl fcn_00500d20(fcn_0047da10_Stamp* a, fcn_0047da10_Stamp* b);
int __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_00489920(fcn_0047da10_Ent* e);
void __cdecl fcn_0047d810(fcn_0047da10_Ent* e);
int __cdecl fcn_0047dca0(fcn_0047da10_Ent* e);
void __cdecl fcn_004c4510(fcn_0047da10_Ent* e, int h);
void __cdecl fcn_004c4670(int, int, int, int*);
void __cdecl fcn_004c5360(void);

// FUNCTION: GOLDTL 0x0047da10
// SIZE: 656
void __cdecl fcn_0047da10(void)
{
	float f;
	int n;
	fcn_0047da10_Stamp now;
	char buf[0x400];
	fcn_0047da10_Ent* e;
	int d;
	int k;
	int idx;

	now = (*(fcn_0047da10_Stamp*)&g_7f4c00);
	d = fcn_00500d20(&g_100dc04, &now);
	f = d * 12.8f;
	n = (int) f;
	g_67db50 = (float) g_7747b4;
	g_67db54 = g_7747b4 * 0.0625f + 0.5f;
	if (d <= 0 || (*(fcn_0047da10_Stamp*)&g_7f4c00).hour > 0x16 || (*(fcn_0047da10_Stamp*)&g_7f4c00).hour < 6)
		return;
	if (g_100dc04.t < now.t) {
		g_100dc04 = now;
		return;
	}
	if (d > 0x3c) {
		g_100dc04.hour++;
		n = 0x300;
	} else {
		g_100dc04 = now;
		g_100dc14 += f - n;
		if (g_100dc14 >= 1.0f) {
			g_100dc14 -= 1.0f;
			n++;
		}
	}
	fcn_0064d41a(buf, "Player count: %i, Starting with: %i Count: %i Deltatime: %i", n, g_100dc00, n, d);
	idx = g_100dc00;
	for (k = n; k != 0; k--) {
		if (((fcn_0047da10_Ent*)g_7f4ca0)[idx].id != 0xffff) {
			e = &((fcn_0047da10_Ent*)g_7f4ca0)[idx];
			fcn_00489920(e);
			if ((*(fcn_0047da10_Stamp*)&g_7f4c00).hour > 6 && (*(fcn_0047da10_Stamp*)&g_7f4c00).hour < 0x16 && (g_7747b0 & 0x80) == 0 && (e->kind == 5
			    || ((e->id ^ (*(fcn_0047da10_Stamp*)&g_7f4c00).hour) & 1) == 0))
				fcn_0047d810(e);
			if ((fcn_0047dca0(e) != 0 && e->gold != 0) || (e->flags & 0x3000)) {
				int v;

				v = -e->gold - (int) (e->gold * -0.89f);
				fcn_004c4510(e, e->h);
				fcn_004c4670(4, 1, 0x24, &v);
				fcn_004c5360();
			}
		}
		idx = (idx + 1) % 0x300;
	}
	g_100dc00 = idx;
	if (g_100dc00 == 0x300) {
		g_100dc00 = 0;
		g_100dc04.hour++;
		g_100dc04.f6 = 0;
		g_100dc04.f10 = 0;
		g_100dc14 = 0;
	}
	fcn_0064d41a(buf, "Next Player: %i", g_100dc00);
}
