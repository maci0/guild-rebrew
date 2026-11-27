#include "gold_gui.h"

extern GuiObj g_00fb1020[];
void __cdecl d2_RestoreFormPageTextures(int index);
void __cdecl d2_CaptureFormPageTextures(int index, void* a, void* b);
void __cdecl d2_RenderFormToTextures(int index);

/* ADDRESS: GOLD 0x00474c90 */
int __cdecl d2_UpdateFormPageTextures(int index, void* a, void* b)
{
	char* record;
	record = (char*) &g_00fb1020[index];
	if (*(int*) (record + 0x190) == 0) {
		return 0;
	}
	if (*(int*) (record + 0x198) == 0) {
		return 0;
	}
	if (a != 0 && b != 0) {
		d2_RestoreFormPageTextures(index);
		d2_CaptureFormPageTextures(index, a, b);
		d2_RenderFormToTextures(index);
	}
	return 1;
}
