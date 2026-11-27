#include "gold_gui.h"
#include "Develop/Units/d2.v1/gold_window.h"

extern GuiEnt* g_00f8f080;
extern GOLD_GUI_WINDOW g_00f8f120[];
extern int g_fa6158[];

/* ADDRESS: GOLD 0x004760a0 */
void __cdecl d2_AssignElementFont(int id, int value)
{
	GuiEnt* s;

	s = &g_00f8f080[id];
	s->font = (short) value;
	switch (s->kind) {
	case 0x40:
		g_00f8f120[s->bild_offset].font = (short) value;
		break;
	case 0x41:
		g_fa6158[s->bild_offset * 0x58] = value;
		break;
	}
}
