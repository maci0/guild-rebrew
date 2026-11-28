#include <string.h>
#include "Develop/Units/d2.v1/d2_gui.h"
#include "Develop/client_types.h"
#include "Develop/Units/d2.v1/gold_window.h"

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

/* Gold window table 0xf8f120; the Gold record is 0x3c4 bytes, not the shared
 * Win_1015f40 size, so rows are addressed with the native stride. */
extern Win_1015f40 d2_Windows[0x60];
extern D2_FORM_RECORD d2_Forms[];
extern int g_14ce86c;

int __cdecl d2_LoadForm(int, int, char*);
int __cdecl gfx_CreateSurface(void*, int);
int __cdecl d2_CreateSurface(D2_FORM_TEX_DESC* d, int flags);

#if defined(REBREW_GOLD)
/* Opens a screen page: creates it, flags its window and every child GUI entity
 * (+0x38), and builds the two 0x40-byte descriptors stored at +0x1a4/+0x1a8. */
/* ADDRESS: GOLD 0x00474b20 */
int __cdecl d2_CreateRenderableForm(int x, int y, char* formName)
{
	int buf[0x10];
	int r;
	char* rec;
	GOLD_GUI_WINDOW* w;
	int i;
	int j;

	r = d2_LoadForm(x, y, formName);
	if (r != 0) {
		rec = (char*) 0xfb1020 + r * 0x2ac;
		for (i = 0; i < *(int*) (rec + 0x184); i++) {
			w = &((GOLD_GUI_WINDOW*) d2_Windows)[((int*) (rec + 4))[i]];
			*(int*) ((char*) &g_00f8f080[w->id] + 0x38) = 1;
			for (j = 0; j < w->count; j++) {
				*(int*) ((char*) &g_00f8f080[w->list[j]] + 0x38) = 1;
			}
		}
		*(int*) (rec + 0x198) = 1;
		w = &((GOLD_GUI_WINDOW*) d2_Windows)[*(int*) (rec + 4)];
		memset(buf, 0, sizeof(buf));
		buf[1] = w->width;
		buf[2] = w->height;
		*(int*) (rec + 0x1a4) = gfx_CreateSurface(buf, 3);
		memset(buf, 0, sizeof(buf));
		buf[1] = w->width;
		buf[2] = w->height;
		*(int*) (rec + 0x1a8) = gfx_CreateSurface(buf, 3);
		return r;
	}
	return 0;
}
#else
/* ADDRESS: GOLDTL 0x00471170 */
/* ADDRESS: GOLDDE 0x00464670 */
int __cdecl d2_CreateRenderableForm(int x, int y, char* formName)
{
	int id;
	int i;
	int j;
	D2_FORM_PAGE* p;
	D2_FORM_WIN* w;
	D2_FORM_TEX_DESC d;

	id = d2_LoadForm(x, y, formName);
	if (id != 0) {
		p = &((D2_FORM_PAGE*)d2_Forms)[id];
		for (i = 0; i < p->count; i++) {
			w = &((D2_FORM_WIN*)d2_Windows)[p->wins[i]];
			(*(int*)&((D2_CONTROL_TL*)d2_Controls)[w->i[0x27c / 4]].value_048) = 1;
			for (j = 0; j < w->i[0x2c / 4]; j++) {
				(*(int*)&((D2_CONTROL_TL*)d2_Controls)[((int*) w->i[0x28 / 4])[j]].value_048) = 1;
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
#endif
