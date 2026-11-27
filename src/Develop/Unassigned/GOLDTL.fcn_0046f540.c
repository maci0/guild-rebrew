#include <string.h>

#include "Develop/Units/d2.v1/d2_win.h"




// SIZE 0x3cc

typedef struct
{
	int id;
	char pad04[0x40 - 0x4];
	D2_WIN* parent;
	char pad44[0x2f4 - 0x44];
} fcn_0046f540_Ent;
// SIZE 0x2f4

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern void** g_772540;

void __cdecl d2_ReorderControlStack(int id);

/* ADDRESS: GOLDTL 0x0046f540 */
void __cdecl d2_BringWindowToFront(int win)
{
	D2_WIN* w;
	fcn_0046f540_Ent* tmp[0x181];
	int i;
	int first;
	int last;
	int n;

	first = -1;
	last = -1;
	w = &((D2_WIN*)g_1015f40)[win];
	for (i = 0x3ff; i >= 0; i--) {
		if (((fcn_0046f540_Ent**)g_772540)[i] != 0 && ((fcn_0046f540_Ent**)g_772540)[i]->id == w->slot) {
			last = i;
			break;
		}
		if (((fcn_0046f540_Ent**)g_772540)[i] != 0 && ((fcn_0046f540_Ent**)g_772540)[i]->parent == w && first == -1) {
			first = i;
		}
	}
	if (first == -1) {
		first = last;
	}
	n = (first - last) * 4 + 4;
	memcpy(tmp, &((fcn_0046f540_Ent**)g_772540)[last], n);
	memmove(&((fcn_0046f540_Ent**)g_772540)[last], &((fcn_0046f540_Ent**)g_772540)[first + 1], 0xff8 - first * 4);
	for (i = 0x3ff; i >= 0; i--) {
		if (((fcn_0046f540_Ent**)g_772540)[i] != 0) {
			break;
		}
	}
	memcpy(&((fcn_0046f540_Ent**)g_772540)[i + 1], tmp, n);
	for (i = 0; i < w->count; i++) {
		d2_ReorderControlStack(w->children[i]);
	}
}
