


#include "Develop/DieGildeAddOn/game/head_set.h"




// SIZE 0x44

extern HEAD_SET g_6918e8[];


void __cdecl gm_ResolveHeadSetIcons(HEAD_SET*);

HEAD_SET* __cdecl gm_FindOrAllocHeadSet(int which, int key)
{
	HEAD_SET* base;
	int i;

	i = 0;
	if (which == 0) {
		base = g_6918e8;
	} else if (which == 1) {
		base = g_693228;
	} else {
		return 0;
	}
	for (; i < 0x5f; i++) {
		if (base[i].key == 0) {
			break;
		}
		if (base[i].key == key) {
			gm_ResolveHeadSetIcons(&base[i]);
			return &base[i];
		}
	}
	return &base[i];
}
