#include <stdio.h>

#include "client_types.h"
typedef Fld_102d140 fcn_00466cb0_Fld;
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

extern Fld_102d140 g_102d140[];
extern char* g_772500;
extern char* g_1015ea0;
extern int g_1040490;
extern int g_1040494;
extern int g_67d398;
extern char s_67d47c[];
extern char s_67d474[];
extern char s_67d46c[];

#include "Develop/Units/Error/error_message.h"
int __cdecl fcn_00465950(char* name);
void __cdecl fcn_00469900(int def);
int __cdecl fcn_00469890(void);

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
			fcn_0041d9e0(s_67d47c);
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
	fcn_00469900(def);
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
	id = fcn_00469890();
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0x20 / 4] = 0x41;
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0x10 / 4] = f->x;
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0x14 / 4] = f->y;
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0x18 / 4] = f->w;
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0x1c / 4] = f->h;
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0x8 / 4] = def;
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0x88 / 4] = i;
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0x24 / 4] = 2;
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0x30 / 4] = 0;
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0x34 / 4] = g_1040490;
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0x28 / 4] = 0;
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0x2c / 4] = g_1040494;
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0xc / 4] = (int) f;
	((fcn_00466cb0_Ent*)g_1015ea0)[id].i[0x84 / 4] = g_67d398;
	f->ent = id;
	return id;
}
