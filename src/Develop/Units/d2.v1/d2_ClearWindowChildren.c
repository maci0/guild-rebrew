#include "Develop/Units/d2.v1/d2_win.h"
// SIZE 0x3cc

typedef struct Slot {
	char pad0[0x20];
	int type;
	char pad24[0x2f4 - 0x24];
} Slot;
// SIZE 0x2f4

#include "Develop/client_types.h"
extern Win_1015f40 d2_Windows[0x60];
extern char* d2_Controls;

void __cdecl d2_DestroyElement(int slot);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x0046f2c0 */
/* ADDRESS: GOLDDE 0x00462850 */
int __cdecl d2_ClearWindowChildren(int win, int keep)
{
	int i;

	if (win > 0x60) {
		return 0;
	}
	if (!((D2_WIN*)d2_Windows)[win].active) {
		return 0;
	}
	for (i = ((D2_WIN*)d2_Windows)[win].count - 1; i >= 0; i--) {
		if (((D2_WIN*)d2_Windows)[win].children[i] == ((int*)((D2_WIN*)d2_Windows)[win].pad3a8)[4 + 0]) {
			((int*)((D2_WIN*)d2_Windows)[win].pad3a8)[4 + 0] = -1;
		} else if (((D2_WIN*)d2_Windows)[win].children[i] == ((int*)((D2_WIN*)d2_Windows)[win].pad3a8)[4 + 1]) {
			((int*)((D2_WIN*)d2_Windows)[win].pad3a8)[4 + 1] = -1;
		} else if (((D2_WIN*)d2_Windows)[win].children[i] == ((int*)((D2_WIN*)d2_Windows)[win].pad3a8)[4 + 2]) {
			((int*)((D2_WIN*)d2_Windows)[win].pad3a8)[4 + 2] = -1;
		}
		if (((D2_CONTROL_TL*) d2_Controls)[((D2_WIN*)d2_Windows)[win].children[i]].kind != 0x40 || keep) {
			d2_DestroyElement(((D2_WIN*)d2_Windows)[win].children[i]);
		}
	}
	if ((*(char**) &((D2_WIN*)d2_Windows)[win].pad3c[0])) {
		(*(char**) &((D2_WIN*)d2_Windows)[win].pad3c[0])[0] = 0;
	}
	*(int*) &((D2_WIN*)d2_Windows)[win].pad3c[0x220] = -1;
	*(int*) &((D2_WIN*)d2_Windows)[win].pad3c[0x21c] = 0;
	*(int*) &((D2_WIN*)d2_Windows)[win].pad3c[0x218] = 0;
	return 1;
}
