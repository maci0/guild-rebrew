#include <string.h>

#pragma warning(disable: 4234)

/* ADDRESS: GOLDTL 0x0060e654 */

void __thiscall fcn_0060e654(void* self, char* src, unsigned short a2, unsigned short a3)
{
	int* tbl120;
	int* tbl118;
	char* base;
	int count;
	int slot;

	tbl120 = *(int**)((char*)self + 0x120);
	tbl118 = *(int**)((char*)self + 0x118);
	base = *(char**)((char*)self + 0x114);
	count = *(int*)((char*)self + 0xc);
	slot = tbl120[a3];
	tbl118[slot] = a2;
	memcpy(base + slot * count, src + a2 * count, count);
	tbl120[a3] = tbl120[a3] - 1;
}
