#include "Develop/Units/d2.v1/gold_gui.h"
#include "Develop/Units/d2.v1/d2_gui.h"

extern GuiEnt* g_00f8f080; /* 0x00f8f080 */

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

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00475970 */
int __cdecl d2_GetControlValue(int slot)
{
	GuiEnt* s;
	char* d;

	s = &g_00f8f080[slot];
	if (s->kind == 0x41) {
		d = s->data;
		if (*(int*) (d + 0x28) & 0x10) {
			return *(int*) (d + 0x14c);
		}
		if (*(int*) (d + 0x28) & 1) {
			return (int) (d + 0x2c);
		}
		if (*(int*) (d + 0x28) & 2) {
			return *(int*) (d + 0x12c);
		}
	}
	if (s->dirty) {
		return s->f28;
	}
	if (s->kind == 0x45) {
		return (int) s->buf;
	}
	return -1;
}
#else
/* ADDRESS: GOLDTL 0x00471f80 */
int __cdecl d2_GetControlValue(int slot)
{
	Slot* s;
	char* d;

	s = (Slot*)&((D2_CONTROL_TL*)d2_Controls)[slot];
	if ((*(int*)&((D2_CONTROL_TL*)s)->kind) == 0x41) {
		d = (*(char**)&((D2_CONTROL_TL*)s)->data);
		if (*(int*) (d + 0x28) & 0x10) {
			return *(int*) (d + 0x14c);
		}
		if (*(int*) (d + 0x28) & 1) {
			return (int) (d + 0x2c);
		}
		if (*(int*) (d + 0x28) & 2) {
			return *(int*) (d + 0x12c);
		}
	}
	if ((*(int*)&((D2_CONTROL_TL*)s)->value_058)) {
		return (*(int*)&((D2_CONTROL_TL*)s)->value_038);
	}
	if ((*(int*)&((D2_CONTROL_TL*)s)->kind) == 0x45) {
		return (int) (*(char**)&((D2_CONTROL_TL*)s)->payload.fields.value_08c);
	}
	return -1;
}
#endif
