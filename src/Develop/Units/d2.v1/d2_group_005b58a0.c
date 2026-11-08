typedef struct
{
	char pad0[0x18];
	int x18;
	char pad1c[0x40];
	int x5c;
	char pad60[0xc];
	int x6c;
	char pad70[0x2f4 - 0x70];
} Ctl;

typedef struct
{
	int x;
	int y;
	int x8;
	int icon;
	int x10;
	int label;
	int value;
	int x1c;
	int x20;
	int x24;
	int a[6];
	int b[6];
	int x58;
} Gauge;

extern int g_772514;
extern int g_772534;
extern char* g_1015ea0;
extern char* g_14abc28;

int __cdecl fcn_0046f740(int, int, int, int);
#include "Develop/Units/d2.v1/d2_gui.h"
typedef struct
{
	char pad0[0x18];
	int x18;
	char pad1c[0x30];
	int x4c;
	char pad50[0x1c];
	int x6c;
	char pad70[0x280];
	char* x2f0;
} fcn_005b59c0_Ctl;

typedef struct
{
	int x;
	int y;
	unsigned char* obj;
	int icon;
	int bar;
	int label;
	int value;
	int x1c;
	unsigned char state;
	char pad21[0x58 - 0x21];
	int win;
} fcn_005b59c0_Gauge;

extern unsigned char* lpGebaeudePROT;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char g_68c1c8[];
extern char g_679060[];

void __cdecl d2_SetForm(int, int);
int __cdecl fcn_0046f740(int x, int y, int a3, int win);
void __cdecl fcn_00517c00(int, int, int, char*);
void __cdecl fcn_0046f940(int, char*);
int __cdecl fcn_004677e0(int x, int y, int a3, int a4, int a5, int a6, int a7, int win);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
void __cdecl fcn_00534160(int x0, int y, int len, int t);
int __cdecl fcn_0050f950(int a1, int a2);

/* ADDRESS: GOLDTL 0x005b58a0 */
void __cdecl d2_CreateGauge(int x, int y, Gauge* s)
{
	int i;

	s->icon = fcn_0046f740(x, y, 0x5db, g_772514);
	((Ctl*)g_1015ea0)[s->icon].x5c = 1;
	s->label = d2_ShowTxt(x - 0x36, y - 0x11, g_14abc28, g_772514);
	((Ctl*)g_1015ea0)[s->label].x18 = 0xa0;
	((Ctl*)g_1015ea0)[s->label].x6c = 1;
	s->value = d2_ShowTxt(x - 0x36, y + 0x44, "", g_772514);
	((Ctl*)g_1015ea0)[s->value].x18 = 0xa0;
	((Ctl*)g_1015ea0)[s->value].x6c = 1;
	s->x1c = -1;
	s->x10 = -1;
	s->x8 = 0;
	s->x24 = 0;
	s->x58 = g_772534;
	s->y = y;
	s->x = x;
	for (i = 0; i < 6; i++) {
		s->a[i] = -1;
		s->b[i] = -1;
	}
}

/* ADDRESS: GOLDTL 0x005b59c0 */
void __cdecl d2_UpdateGauge(unsigned char* e, fcn_005b59c0_Gauge* g, int full)
{
	char buf[0x80];
	unsigned char* rec;

	rec = lpGebaeudePROT + **(unsigned char**) (e + 0x16c) * 0x24d;
	d2_SetForm(g->win, 3);
	g->x1c = fcn_0046f740(g->x + 2, g->y, *(int*) (e + 0x18c), g_772514);
	fcn_00517c00(*(unsigned short*) e, 1, 1, buf);
	fcn_0046f940(g->label, buf);
	((fcn_005b59c0_Ctl*)g_1015ea0)[g->label].x6c = 1;
	((fcn_005b59c0_Ctl*)g_1015ea0)[g->label].x18 = 0xa0;
	g->bar = fcn_004677e0(g->x - 8, g->y + 0x32, 0x40, 0, 0x64, 0x75, 0x42, g_772514);
	((fcn_005b59c0_Ctl*)g_1015ea0)[g->bar].x4c = 1;
	g->state = 1;
	((fcn_005b59c0_Ctl*)g_1015ea0)[g->icon].x2f0 = (char*) e;
	if (*(int*) (e + 0x174) != 0 && e[0x164] == 0) {
		if (g->obj[0x165] == rec[0x230])
			io_FormatTextBuffer(buf, g_68c1c8, *(int*) (e + 0x174), 0x1a39);
		else if (g->obj[0x165] == rec[0x22f])
			io_FormatTextBuffer(buf, g_68c1c8, *(int*) (e + 0x174), 0x1a3a);
		fcn_0046f940(g->value, buf);
		((fcn_005b59c0_Ctl*)g_1015ea0)[g->value].x6c = 1;
		((fcn_005b59c0_Ctl*)g_1015ea0)[g->value].x18 = 0xa0;
	} else if (e[0x164] == 0) {
		if (g->obj[0x165] == rec[0x230])
			io_FormatTextBuffer(buf, g_679060, 0x1a3b);
		else if (g->obj[0x165] == rec[0x22f])
			io_FormatTextBuffer(buf, g_679060, 0x1a3c);
		fcn_0046f940(g->value, buf);
		((fcn_005b59c0_Ctl*)g_1015ea0)[g->value].x6c = 1;
		((fcn_005b59c0_Ctl*)g_1015ea0)[g->value].x18 = 0xa0;
	}
	if (full != 0) {
		fcn_00534160(g->x, g->y + 0x64, e[0x83], 0x4df);
		fcn_00534160(g->x, g->y + 0x74, e[0x82], 0x4df);
	}
	if (g->bar != -1)
		d2_SetElementValue(g->bar, 0, 0x64, (int) ((float) ((fcn_0050f950(g_774970, *(unsigned short*) g->obj) + 128.0) * 100.0) / 255.0));
}
