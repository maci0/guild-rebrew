// FUNCTION: GOLDTL 0x4adcd0

#include <string.h>

// SIZE 0x21c
typedef struct {
	char pad0[2];
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x214];
} Ent4adc;

// SIZE 0x1d0
typedef struct {
	unsigned short id;
	unsigned char state;
	char pad3;
	int handle;
	char pad8[2];
	unsigned short owner;
	unsigned char bc;
	unsigned char bd;
	char pade[2];
	float f10;
	float f14;
	float f18;
	float f1c;
	float f20;
	char pad24[0x0c];
	char name[0x10];
	char title[0x10];
	unsigned short w50;
	char pad52[6];
	unsigned char b58;
	char pad59[3];
	int f5c[8];
	int f7c;
	unsigned char b80[5];
	char pad85[0x16c - 0x85];
	int f16c;
	int f170;
	char pad174[0x18c - 0x174];
	int f18c;
	char pad190[0x1cc - 0x190];
	int flags;
} Guild4adc;

extern char g_869480[0x300][0x300];
extern char g_90e0a0[0x300][0x300];
extern char g_8680b4[];
extern unsigned char g_773d75;
extern char g_7f4ca0[];
extern int g_7728cc;
extern int g_7728c4;
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_004e8700(int);
void __cdecl fcn_004e8730(int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl fcn_005037c0(int a, int b, int c);
char* __cdecl fcn_004ad130(int, int*);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
int __cdecl fcn_004ae040(void);
int __cdecl fcn_004ae060(void);
void __cdecl fcn_004adf80(void);
void __cdecl fcn_004adfe0(void);

void __cdecl fcn_004adcd0(int mode, int unused, unsigned short owner, Guild4adc* g)
{
	char buf[0x100];
	char* p;
	unsigned short k;
	int i;
	int j;

	if (mode == 0x15) {
		g->flags |= 0x1000;
		fcn_004e8700(g->handle);
	} else {
		g->flags |= 0x2000;
		fcn_004e8730(g->handle);
	}
	g->owner = owner;
	g->bc = 0;
	for (i = 0; i < 0x300; i++) {
		for (j = 0; j < 0x300; j++) {
			g_869480[i][j] = gm_RandomMod(0x40) - 0x20;
			g_90e0a0[i][j] = 0;
		}
	}
	g->w50 = 0x7fff;
	g->f7c = 0;
	g->b58 = 0;
	for (i = 0; i < 8; i++) {
		g->f5c[i] = -1;
	}
	g->f170 = 0;
	g->f16c = 0;
	g->f1c = 1000.0f;
	g->f14 = 1.0f;
	g->f20 = 12.0f;
	g->f10 = 330.0f;
	g->f18 = 1000.0f;
	for (i = 0; i < 5; i++) {
		g->b80[i] = (unsigned char) (gm_RandomMod(0x2a) + 210.0f);
	}
	g->bd = 9;
	fcn_005037c0(g->handle, *(unsigned short*) (g_8680b4 + g_773d75 * 0x2f4), 16000000);
	k = 0xffff;
	for (i = 0; i < 768 && k == 0xffff; i++) {
		if (((Ent4adc*)g_7f4ca0)[i].type == 6) {
			k = i;
		}
	}
	{
		int tmp;

		if (mode == 0x15) {
			p = fcn_004ad130(g_7728cc, &tmp);
		} else {
			p = fcn_004ad130(g_7728c4, &tmp);
		}
	}
	strcpy(g->name, p + 0xc);
	strcpy(g->title, p + 0x1c);
	if (mode == 0x15) {
		if ((*(int*)&g_7f4c00) > 0 && k != 0xffff) {
			fcn_0051af00(buf, 0x42b3, g->id);
			fcn_00545d40(((Ent4adc*)g_7f4ca0)[k].id, -1, buf, 0, 0x602, "_NACHRICHTEN_NEU_01");
		}
		g->f18c = fcn_004ae040();
		fcn_004adf80();
	} else {
		if ((*(int*)&g_7f4c00) > 0 && k != 0xffff) {
			fcn_0051af00(buf, 0x42b5, g->id);
			fcn_00545d40(((Ent4adc*)g_7f4ca0)[k].id, -1, buf, 0, 0x602, "_NACHRICHTEN_NEU_03");
		}
		g->f18c = fcn_004ae060();
		fcn_004adfe0();
	}
	g->state = 3;
}
