#pragma pack(push, 1)
typedef struct
{
	int a;
	int b;
	int c;
	short d;
} fcn_005516e0_Stamp;
// SIZE 0xe
#pragma pack(pop)

// SIZE 0x21c
typedef struct
{
	unsigned short id;
	char pad2[2];
	int h;
	char pad8;
	char male;
	char pada[0x21c - 0xa];
} fcn_005516e0_Ent;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern char g_7f4ca0[];

int __cdecl fcn_004c4450(int id);
void __cdecl fcn_00546190(char* t);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_00507130(int k, int* a, int* b);
void __cdecl fcn_004c4510(fcn_005516e0_Ent* e, int h);
int __cdecl gm_RandomMod(int n);
void __cdecl fcn_004c4670(int, int, int, char*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c6470(int, int);
char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_004c5620(int a1, char* e);
void __cdecl fcn_0051af00(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);
void __cdecl fcn_00546ef0(int, char*, int, int);

// FUNCTION: GOLDTL 0x005516e0
void __cdecl fcn_005516e0(char* t)
{
	char c;
	int a;
	int b;
	char buf[0x100];
	fcn_005516e0_Ent* e;
	char* p;
	int h;

	if (*(int*) (t + 0x70) == -2 || *(int*) (t + 0x70) == -1) {
		fcn_00546190(t);
		return;
	}
	if (t[0x78] & 4)
		return;
	if (*(int*) (t + 0x84) != -1 && fcn_004c4450(*(int*) (t + 0x84)) == 0)
		return;
	*(int*) (t + 0x84) = -1;
	switch (*(int*) (t + 0x70)) {
	case 1:
		e = &((fcn_005516e0_Ent*)g_7f4ca0)[*(unsigned short*) (t + 8)];
		fcn_00507130(gm_MapEntityStatRange(*(unsigned char*) (t + 0xb0)), &a, &b);
		fcn_004c4510(e, e->h);
		c = gm_RandomMod(0x10) + 0x10;
		fcn_004c4670(1, 1, a + 0x80, &c);
		c = gm_RandomMod(0x10) + 0x10;
		fcn_004c4670(1, 1, b + 0x80, &c);
		fcn_004c5360();
		fcn_004c6470(e->h, *(unsigned char*) (t + 0xb0));
		p = fcn_00508e40(*(int*) (t + 0xac));
		if (p == 0) {
			*(fcn_005516e0_Stamp*) (t + 0x52) = (*(fcn_005516e0_Stamp*)&g_7f4c00);
			fcn_004c5620(-1, t);
			return;
		}
		fcn_0051af00(buf, 0x1a9c, e->id, (e->male ? 0x18f : 0x130) + *(unsigned char*) (t + 0xb0));
		h = *(int*) (p + 4);
		fcn_00545d40(h, h, buf, 0, 0x5f4, 0);
		*(fcn_005516e0_Stamp*) (t + 0x52) = (*(fcn_005516e0_Stamp*)&g_7f4c00);
		fcn_004c5620(-1, t);
		return;
	case 0:
		e = &((fcn_005516e0_Ent*)g_7f4ca0)[*(unsigned short*) (t + 8)];
		p = fcn_00508e40(*(int*) (t + 0xac));
		if (p == 0) {
			*(fcn_005516e0_Stamp*) (t + 0x52) = (*(fcn_005516e0_Stamp*)&g_7f4c00);
			fcn_004c5620(-1, t);
			return;
		}
		fcn_0051af00(buf, 0x1a9b, e->id);
		t[0xb8]++;
		*(short*) (t + 0x56) += 0x18;
		fcn_004c5620((unsigned char) t[0xb8] >= 3, t);
		fcn_00546ef0(*(unsigned short*) p, buf, 0, -*(int*) (t + 0xb4));
		return;
	}
}
