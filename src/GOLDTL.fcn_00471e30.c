#include <string.h>

extern int __cdecl fcn_0046f280(int a1);
extern int __cdecl fcn_00475f80(void* o);

/* ADDRESS: GOLDTL 0x00471e30 */
void __cdecl fcn_00471e30(int a0)
{
	char* base;
	int* items;
	int* p;
	int i;

	if (a0 > 0x30) {
		if (a0 < 1) {
			return;
		}
	}
	base = (char*) 0x1038140 + a0 * 700;
	if (*(int*) (0x10382d0 + a0 * 700) == 0) {
		return;
	}
	items = (int*) 0x1038144;
	for (i = *(int*) (0x10382c4 + a0 * 700) - 1; i >= 0; i--) {
		fcn_0046f280(items[a0 * 175 + i]);
	}
	p = (int*) (base + 0x1ac);
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
