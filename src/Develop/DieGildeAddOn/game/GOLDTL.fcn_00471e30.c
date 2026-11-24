#include <string.h>
#include "client_data.h"

extern int __cdecl fcn_0046f280(int a1);
extern int __cdecl fcn_00475f80(void* o);

/* ADDRESS: GOLDTL 0x00471e30 */
void __cdecl fcn_00471e30(int dialogIndex)
{
	D2_FORM_RECORD* base;
	int i;
	int* p;
	int* items;

	if (dialogIndex > 0x30) {
		if (dialogIndex < 1) {
			return;
		}
	}
	base = &g_1038140[dialogIndex];
	if (g_1038140[dialogIndex].used == 0) {
		return;
	}
	items = (int*) g_1038144;
	for (i = base->count - 1; i >= 0; i--) {
		fcn_0046f280(items[dialogIndex * 175 + i]);
	}
	p = (int*) base->h;
	for (i = 0; i < 2; i++) {
		if (p[-2] != 0) {
			fcn_00475f80((void*) p[-2]);
		}
		if (p[0] != 0) {
			fcn_00475f80((void*) p[0]);
		}
		p++;
	}
	memset(base, 0, 700);
}
