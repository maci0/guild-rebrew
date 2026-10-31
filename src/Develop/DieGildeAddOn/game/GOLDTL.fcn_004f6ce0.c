


#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl io_FormatTextBuffer(void*, int, ...);

void __cdecl fcn_004f6ce0(void* a1, int a2, void* a3)
{
	int v;
	int n;

	v = gm_WalkEntityChain(*(unsigned short*) a1);
	n = (int) ((float) v * 0.03f);
	switch (a2) {
	case 1:
		io_FormatTextBuffer(a3, 0x1538, n);
		break;
	case 3:
		io_FormatTextBuffer(a3, 0x153e, 4, n);
		break;
	default:
		io_FormatTextBuffer(a3, a2 * 3 + 0x1535);
		break;
	}
}
