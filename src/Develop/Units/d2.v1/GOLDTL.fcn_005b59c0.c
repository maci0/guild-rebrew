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
// SIZE 0x2f4

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

extern char* g_1015ea0;
extern unsigned char* lpGebaeudePROT;
extern int g_772514;
extern unsigned short g_774970;
extern char g_68c1c8[];
extern char g_679060[];

void __cdecl d2_SetForm(int, int);
int __cdecl fcn_0046f740(int x, int y, int a3, int win);
void __cdecl fcn_00517c00(int, int, int, char*);
void __cdecl fcn_0046f940(int, char*);
int __cdecl fcn_004677e0(int x, int y, int a3, int a4, int a5, int a6, int a7, int win);
void __cdecl fcn_0051af00(char*, char*, ...);
void __cdecl fcn_00534160(int x0, int y, int len, int t);
int __cdecl fcn_0050f950(int a1, int a2);
#include "Develop/Units/d2.v1/d2_gui.h"

/* ADDRESS: GOLDTL 0x005b59c0 */
void __cdecl fcn_005b59c0(unsigned char* e, fcn_005b59c0_Gauge* g, int full)
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
			fcn_0051af00(buf, g_68c1c8, *(int*) (e + 0x174), 0x1a39);
		else if (g->obj[0x165] == rec[0x22f])
			fcn_0051af00(buf, g_68c1c8, *(int*) (e + 0x174), 0x1a3a);
		fcn_0046f940(g->value, buf);
		((fcn_005b59c0_Ctl*)g_1015ea0)[g->value].x6c = 1;
		((fcn_005b59c0_Ctl*)g_1015ea0)[g->value].x18 = 0xa0;
	} else if (e[0x164] == 0) {
		if (g->obj[0x165] == rec[0x230])
			fcn_0051af00(buf, g_679060, 0x1a3b);
		else if (g->obj[0x165] == rec[0x22f])
			fcn_0051af00(buf, g_679060, 0x1a3c);
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
