#include <stdio.h>

typedef struct
{
	int idx;
	int x;
	int y;
	int pad0c;
	int w;
	int h;
	int max;
	int f1c;
	int pad20;
	unsigned char digits;
	char pad25[3];
	int flags;
	char pad2c[0x12c - 0x2c];
	int f12c;
	int used;
	int ent;
	int font;
	int def;
	int f140;
	int f144;
	char pad148[0x154 - 0x148];
	int f154;
	char pad158[0x160 - 0x158];
} fcn_00467240_Fld;
// SIZE 0x160

typedef struct
{
	int i[0x2f4 / 4];
} fcn_00467240_Ent;
// SIZE 0x2f4

#include "Develop/client_types.h"
extern UI_FIELD g_102d140[];
#include "Develop/Units/d2.v1/d2_gui.h"
extern char s_67d47c[];
extern char s_67d474[];
extern char s_67d46c[];

#include "Develop/Units/Error/error_message.h"
int __cdecl d2_FindResourceByName(char* name);
int __cdecl d2_AllocateElement(void);
int __cdecl d2_MeasureTextWidth(char* s, int font);

/* ADDRESS: GOLDTL 0x00467240 */
int __cdecl d2_OpenInputIcon(int x, int y, int w, int h, unsigned char flags)
{
	int i;
	int n;
	int v;
	int id;
	fcn_00467240_Fld* f;
	char buf[24];

	i = 1;
	if (((fcn_00467240_Fld*)g_102d140)[1].used != 0) {
		while (((fcn_00467240_Fld*)g_102d140)[i].used != 0) {
			i++;
		}
		if (i > 0x7f) {
			ReportClientMessage(s_67d47c);
			return -1;
		}
	}
	f = &((fcn_00467240_Fld*)g_102d140)[i];
	f->idx = i;
	f->x = x;
	f->y = y;
	f->w = w;
	f->h = h;
	f->max = 999;
	f->f1c = 0;
	f->f12c = 0;
	f->f140 = 1;
	f->f144 = 1;
	f->digits = 3;
	f->flags = flags;
	f->used = 1;
	f->font = d2_FindResourceByName(s_67d474);
	f->def = -1;
	f->f154 = 0;
	id = d2_AllocateElement();
	if (flags & 2) {
		v = f->max;
		for (n = 0; n < 10; n++) {
			if (v <= 0) {
				break;
			}
			v /= 10;
		}
		f->digits = n;
		sprintf(buf, s_67d46c, f->digits);
		sprintf(buf + 8, buf, f->f12c * f->f140);
		f->w = d2_MeasureTextWidth(buf + 8, f->font);
	}
	if (flags & 1) {
		f->max = 0x20;
	}
	if (flags & 0x30) {
		(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].value_078) = 1;
	}
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].kind) = 0x41;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].x) = f->x;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].y) = f->y;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].width) = f->w;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].height) = f->h;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].value_008) = 0;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].value_088) = f->idx;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].mode) = 2;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_top) = f->y;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_left) = f->x;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_right) = f->x + f->w;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].clip_bottom) = f->y + f->h;
	(*(int*)&((D2_CONTROL_TL*)d2_Controls)[id].data) = (int) f;
	f->ent = id;
	return id;
}
