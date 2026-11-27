#include <string.h>

typedef struct
{
	int i[0x3cc / 4];
} D2_FORM_WIN;
// SIZE 0x3cc

typedef struct
{
	int i[0x2f4 / 4];
} D2_FORM_ENT;
// SIZE 0x2f4

typedef struct
{
	int pad000;
	int wins[0x60];
	int count;
	char pad188[0x198 - 0x188];
	int ready;
	char pad19c[0x1a4 - 0x19c];
	int surf[2];
	int back[2];
	char pad1b4[0x2bc - 0x1b4];
} D2_FORM_PAGE;
// SIZE 0x2bc

typedef struct
{
	int f00;
	int w;
	int h;
	char pad0c[0x28 - 0xc];
	int fmt;
	char pad2c[0x5c - 0x2c];
} D2_FORM_TEX_DESC;
// SIZE 0x5c

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
#include "Develop/Units/d2.v1/d2_gui.h"
extern D2_FORM_RECORD g_1038140[];
extern int g_14ce86c;

int __cdecl d2_LoadForm(int a, int b, int c);
int __cdecl d2_CreateSurface(D2_FORM_TEX_DESC* d, int flags);

/* ADDRESS: GOLDTL 0x00471170 */
int __cdecl d2_CreateRenderableForm(int x, int y, int formName)
{
	int id;
	int i;
	int j;
	D2_FORM_PAGE* p;
	D2_FORM_WIN* w;
	D2_FORM_TEX_DESC d;

	id = d2_LoadForm(x, y, formName);
	if (id != 0) {
		p = &((D2_FORM_PAGE*)g_1038140)[id];
		for (i = 0; i < p->count; i++) {
			w = &((D2_FORM_WIN*)g_1015f40)[p->wins[i]];
			(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[w->i[0x27c / 4]].value_048) = 1;
			for (j = 0; j < w->i[0x2c / 4]; j++) {
				(*(int*)&((D2_CONTROL_TL*)g_1015ea0)[((int*) w->i[0x28 / 4])[j]].value_048) = 1;
			}
		}
		p->ready = 1;
		for (i = 0; i < 2; i++) {
			memset(&d, 0, sizeof(d));
			d.w = 0x100;
			d.h = 0x100;
			d.fmt = g_14ce86c;
			p->surf[i] = d2_CreateSurface(&d, 0x10);
			memset(&d, 0, sizeof(d));
			d.w = 0x100;
			d.h = 0x100;
			d.fmt = g_14ce86c;
			p->back[i] = d2_CreateSurface(&d, 0x10);
		}
		return id;
	}
	return 0;
}
