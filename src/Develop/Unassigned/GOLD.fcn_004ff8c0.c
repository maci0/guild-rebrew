#define OBJECT_PROTOTYPE_DECLARE_ITEM_TABLE_CHAR_POINTER
#include "Develop/DieGildeAddOn/game/object_prototype.h"

extern float g_773d4c;

/* ADDRESS: GOLD 0x004ff8c0 */
int __cdecl fcn_004ff8c0(int a, int b)
{
	unsigned short w;
	OBJECT_PROTOTYPE* o;

	w = *(unsigned short*) ((char*) 0x7d6a70 + a * 0x2a90 + b * 0x80);
	o = &((OBJECT_PROTOTYPE*) g_item_def_table)[w];
	if ((*(char*) &o->kind) == 0x17 || (*(char*) &o->kind) == 0x25) {
		return 0;
	}
	if (a == 0) {
		return (int) (g_773d4c * *(float*) ((char*) 0x7d6a78 + b * 0x80) * 0.0025 + 0.5);
	}
	return (int) (*(int*) ((char*) 0x7d6a60 + a * 0x2a90) * *(float*) ((char*) 0x7d6a78 + a * 0x2a90 + b * 0x80) * 0.0005);
}
