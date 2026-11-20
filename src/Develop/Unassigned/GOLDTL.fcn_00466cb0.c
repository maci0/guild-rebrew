#include <stdio.h>

#include "client_types.h"
typedef UI_FIELD fcn_00466cb0_Fld;
// SIZE 0x160

typedef struct
{
	char pad00[0x50];
	short w;
	short h;
} fcn_00466cb0_Def;
// SIZE 0x54

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00466cb0_Ent;
// SIZE 0x2f4

extern UI_FIELD g_102d140[];
extern char* g_772500;
#include "Develop/Units/d2.v1/d2_gui.h"
extern int d2_ScreenHeight;
extern int g_1040494;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char s_67d47c[];
extern char s_67d474[];
extern char s_67d46c[];

#include "Develop/Units/Error/error_message.h"
int __cdecl fcn_00465950(char* name);
void __cdecl d2_AddRefcount(int def);
int __cdecl d2_AllocateElement(void);

/* ADDRESS: GOLDTL 0x00466cb0 */
int __cdecl fcn_00466cb0(int x, int y, int def, unsigned char flags)
{
	int i;
	int n;
	int v;
	int id;
	fcn_00466cb0_Fld* f;

	i = 1;
	if (g_102d140[1].used != 0) {
		while (g_102d140[i].used != 0) {
			i++;
		}
		if (i > 0x7f) {
			ReportClientMessage(s_67d47c);
			return -1;
		}
	}
	f = &g_102d140[i];
	f->x = x;
	f->y = y;
	f->def = def;
	f->idx = i;
	f->w = ((fcn_00466cb0_Def*)g_772500)[def].w;
	f->h = ((fcn_00466cb0_Def*)g_772500)[def].h;
	f->f1c = 0;
	f->f12c = 0;
	f->max = 999;
	f->digits = 3;
	f->flags = flags | 0x100;
	f->used = 1;
	f->font = fcn_00465950(s_67d474);
	d2_AddRefcount(def);
	if (flags & 2) {
		char buf[24];

		v = f->max;
		for (n = 0; n < 10; n++) {
			if (v <= 0) {
				break;
			}
			v /= 10;
		}
		f->digits = n;
		sprintf(buf, s_67d46c, f->digits);
		sprintf(buf + 8, buf, f->f140 * f->f12c);
	}
	if (flags & 0x80) {
		f->max = f->max > 0x19 ? f->max : 0x19;
	}
	id = d2_AllocateElement();
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].kind) = 0x41;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].x) = f->x;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].y) = f->y;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].width) = f->w;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].height) = f->h;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].value_008) = def;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].value_088) = i;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].mode) = 2;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].clip_top) = 0;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].clip_bottom) = d2_ScreenHeight;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].clip_left) = 0;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].clip_right) = g_1040494;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].data) = (int) f;
	(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[id].font) = d2_DefaultFont;
	f->ent = id;
	return id;
}
