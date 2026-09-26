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

#include "client_types.h"
extern Fld_102d140 g_102d140[];
extern char* g_1015ea0;
extern char s_67d47c[];
extern char s_67d474[];
extern char s_67d46c[];

void __cdecl fcn_0041d9e0(const char* msg);
int __cdecl fcn_00465950(char* name);
int __cdecl fcn_00469890(void);
int __cdecl fcn_0046b520(char* s, int font);

// FUNCTION: GOLDTL 0x467240
// SIZE: 575
int __cdecl fcn_00467240(int x, int y, int w, int h, unsigned char flags)
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
			fcn_0041d9e0(s_67d47c);
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
	f->font = fcn_00465950(s_67d474);
	f->def = -1;
	f->f154 = 0;
	id = fcn_00469890();
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
		f->w = fcn_0046b520(buf + 8, f->font);
	}
	if (flags & 1) {
		f->max = 0x20;
	}
	if (flags & 0x30) {
		((fcn_00467240_Ent*)g_1015ea0)[id].i[0x78 / 4] = 1;
	}
	((fcn_00467240_Ent*)g_1015ea0)[id].i[0x20 / 4] = 0x41;
	((fcn_00467240_Ent*)g_1015ea0)[id].i[0x10 / 4] = f->x;
	((fcn_00467240_Ent*)g_1015ea0)[id].i[0x14 / 4] = f->y;
	((fcn_00467240_Ent*)g_1015ea0)[id].i[0x18 / 4] = f->w;
	((fcn_00467240_Ent*)g_1015ea0)[id].i[0x1c / 4] = f->h;
	((fcn_00467240_Ent*)g_1015ea0)[id].i[0x8 / 4] = 0;
	((fcn_00467240_Ent*)g_1015ea0)[id].i[0x88 / 4] = f->idx;
	((fcn_00467240_Ent*)g_1015ea0)[id].i[0x24 / 4] = 2;
	((fcn_00467240_Ent*)g_1015ea0)[id].i[0x30 / 4] = f->y;
	((fcn_00467240_Ent*)g_1015ea0)[id].i[0x28 / 4] = f->x;
	((fcn_00467240_Ent*)g_1015ea0)[id].i[0x2c / 4] = f->x + f->w;
	((fcn_00467240_Ent*)g_1015ea0)[id].i[0x34 / 4] = f->y + f->h;
	((fcn_00467240_Ent*)g_1015ea0)[id].i[0xc / 4] = (int) f;
	f->ent = id;
	return id;
}
