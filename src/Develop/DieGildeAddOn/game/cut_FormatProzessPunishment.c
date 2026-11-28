


#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl io_FormatTextBuffer(void*, int, ...);

void __cdecl cut_FormatProzessPunishment(void* entity, int mode, void* output)
{
	int v;
	int n;

	v = gm_CalcPersonWealth(*(unsigned short*) entity);
	n = (int) ((float) v * 0.03f);
	switch (mode) {
	case 1:
		io_FormatTextBuffer(output, 0x1538, n);
		break;
	case 3:
		io_FormatTextBuffer(output, 0x153e, 4, n);
		break;
	default:
		io_FormatTextBuffer(output, mode * 3 + 0x1535);
		break;
	}
}
