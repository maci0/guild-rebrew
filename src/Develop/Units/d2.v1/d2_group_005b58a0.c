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
#include "Develop/DieGildeAddOn/game/building_prototype.h"
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

extern int d2_CurrentWindowId;
extern int g_772534;
extern char* d2_Controls;
extern char* txt_NoEntityName;

int __cdecl d2_AddElementToWindow(int, int, int, int);
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
extern char str_fmt_s[];

void __cdecl d2_SetForm(int, int);
int __cdecl d2_AddElementToWindow(int x, int y, int a3, int win);
void __cdecl gm_FormatEntityTitleAndName(int, int, int, char*);
void __cdecl d2_SetLabelText(int, char*);
int __cdecl d2_AddWindowValueGauge(int x, int y, int a3, int a4, int a5, int a6, int a7, int win);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
void __cdecl d2_DrawSegmentedBar(int x0, int y, int len, int t);
int __cdecl gm_GetEntityRelation(int a1, int a2);

/* ADDRESS: GOLDTL 0x005b58a0 */
/* ADDRESS: GOLDDE 0x005980a0 */
void __cdecl d2_CreateGauge(int x, int y, Gauge* s)
{
	int i;

	s->icon = d2_AddElementToWindow(x, y, 0x5db, d2_CurrentWindowId);
	((D2_CONTROL_TL*) d2_Controls)[s->icon].value_05c = 1;
	s->label = d2_ShowTxt(x - 0x36, y - 0x11, txt_NoEntityName, d2_CurrentWindowId);
	((D2_CONTROL_TL*) d2_Controls)[s->label].width = 0xa0;
	((D2_CONTROL_TL*) d2_Controls)[s->label].value_06c = 1;
	s->value = d2_ShowTxt(x - 0x36, y + 0x44, "", d2_CurrentWindowId);
	((D2_CONTROL_TL*) d2_Controls)[s->value].width = 0xa0;
	((D2_CONTROL_TL*) d2_Controls)[s->value].value_06c = 1;
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
/* ADDRESS: GOLDDE 0x005981c0 */
void __cdecl d2_UpdateGauge(unsigned char* e, fcn_005b59c0_Gauge* g, int full)
{
	char buf[0x80];
	BUILDING_PROTOTYPE *rec;

	rec = &((BUILDING_PROTOTYPE *)lpGebaeudePROT)[**(unsigned char**) (e + 0x16c)];
	d2_SetForm(g->win, 3);
	g->x1c = d2_AddElementToWindow(g->x + 2, g->y, *(int*) (e + 0x18c), d2_CurrentWindowId);
	gm_FormatEntityTitleAndName(*(unsigned short*) e, 1, 1, buf);
	d2_SetLabelText(g->label, buf);
	((D2_CONTROL_TL*) d2_Controls)[g->label].value_06c = 1;
	((D2_CONTROL_TL*) d2_Controls)[g->label].width = 0xa0;
	g->bar = d2_AddWindowValueGauge(g->x - 8, g->y + 0x32, 0x40, 0, 0x64, 0x75, 0x42, d2_CurrentWindowId);
	((D2_CONTROL_TL*) d2_Controls)[g->bar].disabled = 1;
	g->state = 1;
	((D2_CONTROL_TL*) d2_Controls)[g->icon].associated_object = (char*) e;
	if (*(int*) (e + 0x174) != 0 && e[0x164] == 0) {
		if (g->obj[0x165] == rec->role_230)
			io_FormatTextBuffer(buf, g_68c1c8, *(int*) (e + 0x174), 0x1a39);
		else if (g->obj[0x165] == rec->role_22f)
			io_FormatTextBuffer(buf, g_68c1c8, *(int*) (e + 0x174), 0x1a3a);
		d2_SetLabelText(g->value, buf);
		((D2_CONTROL_TL*) d2_Controls)[g->value].value_06c = 1;
		((D2_CONTROL_TL*) d2_Controls)[g->value].width = 0xa0;
	} else if (e[0x164] == 0) {
		if (g->obj[0x165] == rec->role_230)
			io_FormatTextBuffer(buf, "%s", 0x1a3b);
		else if (g->obj[0x165] == rec->role_22f)
			io_FormatTextBuffer(buf, "%s", 0x1a3c);
		d2_SetLabelText(g->value, buf);
		((D2_CONTROL_TL*) d2_Controls)[g->value].value_06c = 1;
		((D2_CONTROL_TL*) d2_Controls)[g->value].width = 0xa0;
	}
	if (full != 0) {
		d2_DrawSegmentedBar(g->x, g->y + 0x64, e[0x83], 0x4df);
		d2_DrawSegmentedBar(g->x, g->y + 0x74, e[0x82], 0x4df);
	}
	if (g->bar != -1)
		d2_SetElementValue(g->bar, 0, 0x64, (int) ((float) ((gm_GetEntityRelation(gm_LocalPlayerSlot, *(unsigned short*) g->obj) + 128.0) * 100.0) / 255.0));
}
