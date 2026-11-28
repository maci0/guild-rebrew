

typedef struct
{
	char pad0[0x18];
	int x18;
	int x1c;
	char pad20[0x4c];
	int x6c;
	char pad70[0x280];
	int x2f0;
} Ctl;
// SIZE 0x2f4

typedef struct
{
	int x;
	int y;
	unsigned short* obj;
	int icon;
	int x10;
	int label;
	int value;
	int x1c;
	unsigned char state;
} Gauge;

extern char* d2_Controls;
extern char* g_14abbb0;
extern char* txt_NoEntityName;

char* __cdecl he_StartHandlungSearch(int, int, int, int, int);
void __cdecl d2_SetLabelText(int, char*);
void __cdecl gm_FormatEntityTitleAndName(int, int, int, char*);
void __cdecl d2_ClearGauge(Gauge*);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_PopulateBookActionGauge(char* e, Gauge* g, int a3, int a4)
{
	char buf[0x100];
	char* p;
	char* src;
	char* dst;

	p = he_StartHandlungSearch(2, 0, a3, 3, *(int*) (e + 1));
	if (p != 0 && *(int*) (p + a4 * 4 + 0xb0) != 0) {
		src = g_14abbb0;
		dst = buf;
		while ((*dst++ = *src++) != 0) {
		}
		g->state = 2;
		d2_SetLabelText(g->label, buf);
		((D2_CONTROL_TL*) d2_Controls)[g->label].width = 0xa0;
		((D2_CONTROL_TL*) d2_Controls)[g->label].height = 0x28;
		g->state = 2;
		return;
	}
	if (g->obj != 0 && ((char*) g->obj)[8] != 0) {
		gm_FormatEntityTitleAndName(*g->obj, 1, 1, buf);
		d2_SetLabelText(g->label, buf);
		((D2_CONTROL_TL*) d2_Controls)[g->label].value_06c = 1;
		((D2_CONTROL_TL*) d2_Controls)[g->label].width = 0xa0;
		g->state = 1;
		return;
	}
	d2_ClearGauge(g);
	src = txt_NoEntityName;
	dst = buf;
	while ((*dst++ = *src++) != 0) {
	}
	g->state = 0;
	d2_SetLabelText(g->label, buf);
	((D2_CONTROL_TL*) d2_Controls)[g->label].width = 0xa0;
	((D2_CONTROL_TL*) d2_Controls)[g->label].height = 0x28;
	d2_SetLabelText(g->value, "");
	g->state = 0;
	*(int*) (&((D2_CONTROL_TL*) d2_Controls)[g->icon].associated_object) = 0;
}
