typedef struct Slot {
	int id;
	int used;
	int value;
	char* data;
	int x;
	int y;
	int w;
	int h;
	int type;
	char pad24[0x38 - 0x24];
	int text;
	char pad3c[0x48 - 0x3c];
	int hidden;
	char pad4c[0x58 - 0x4c];
	int dirty;
	char pad5c[0x88 - 0x5c];
	int result;
	char* buf;
	char pad90[0x2f4 - 0x90];
} Slot;
// SIZE 0x2f4
#include "Develop/Units/d2.v1/d2_window_view.h"












// SIZE 0x3cc
#include "client_types.h"
typedef D2_FORM_RECORD Obj;
// SIZE 0x2bc

#include "Develop/Units/d2.v1/d2_gui.h"

extern D2_FORM_RECORD g_1038140[];
#include "Develop/DieGildeAddOn/game/game_data.h"

/* ADDRESS: GOLDTL 0x00472100 */
char* __cdecl fcn_00472100(int j, int i)
{
	D2_WIN* w;
	D2_CONTROL_TL* s;

	w = &((D2_WIN*)g_1015f40)[g_1038140[g_772534].wins[i]];
	if (j > w->count) {
		return 0;
	}
	s = &((D2_CONTROL_TL*)g_1015ea0)[w->children[j]];
	if (s->kind == 0x41) {
		return *(char**)&s->data;
	}
	return 0;
}
