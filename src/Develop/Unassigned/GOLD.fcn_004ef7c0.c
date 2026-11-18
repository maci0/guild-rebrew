#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl gv_CheckSlotActive(void*, int);
int __cdecl fcn_004f13d0(unsigned char*);

/* ADDRESS: GOLD 0x004ef7c0 */
void* __cdecl fcn_004ef7c0(void* a0, void* a1, void* a2, int (__cdecl* predicate)(void*, void*), int kind)
{
	unsigned char* entry;
	unsigned char* type;
	char* group;
	char* end;
	char* p;

	entry = (unsigned char*) a1;
	group = *(char**) (entry + 0x65);
	type = g_7e3f30 + *entry * 0x24d;
	if (kind != 0xff && !gv_CheckSlotActive(group, kind))
		return 0;
	if (kind == 0) {
		end = *(char**) (group + 8) + ((int*) 0x5ee084)[type[0x247]] * 20;
	} else if (kind == 1) {
		end = *(char**) (group + 0xc) + ((int*) 0x5ee094)[type[0x247]] * 20;
	} else if (kind == 2) {
		end = *(char**) (group + 0x10) + ((int*) 0x5ee0a4)[type[0x247]] * 20;
	} else if (kind == 3) {
		end = *(char**) (group + 0x14) + ((int*) 0x5ee0b4)[type[0x247]] * 20;
	} else if (kind == 0xff) {
		end = *(char**) (group + 0x1c) + fcn_004f13d0(entry) * 20;
	} else {
		return 0;
	}
	if (a2 != 0) {
		p = (char*) a2 + 0x14;
	} else if (kind == 0) {
		p = *(char**) (group + 8);
	} else if (kind == 1) {
		p = *(char**) (group + 0xc);
	} else if (kind == 2) {
		p = *(char**) (group + 0x10);
	} else if (kind == 3) {
		p = *(char**) (group + 0x14);
	} else {
		p = *(char**) (group + 0x1c);
	}
	if (p >= end)
		return 0;
	if (predicate == 0)
		return p;
	do {
		if (predicate(a0, p) != 0)
			return p;
		p += 0x14;
	} while (p < end);
	return 0;
}
