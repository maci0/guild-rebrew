#include <string.h>
#include "client_data.h"

extern int __cdecl fcn_0046f280(int a1);
extern int __cdecl fcn_00475f80(void* o);

/* ADDRESS: GOLDTL 0x00471e30 */
void __cdecl fcn_00471e30(int a0)
{
	Obj_1038140* base;
	int i;
	int* p;
	int* items;

	if (a0 > 0x30) {
		if (a0 < 1) {
			return;
		}
	}
	base = &g_1038140[a0];
	if (base->used == 0) {
		return;
	}
	items = (int*) g_1038144;
	for (i = base->count - 1; i >= 0; i--) {
		fcn_0046f280(items[a0 * 175 + i]);
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
