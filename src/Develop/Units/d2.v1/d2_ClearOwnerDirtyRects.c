#include <string.h>
#pragma intrinsic(memset)

struct D2_DIRTY_OWNER {
	char pad0[0x190];
	int f190;
	int pad194;
	int f198;
};

struct D2_DIRTY_SLOT {
	int f0;
	int f4;
	struct D2_DIRTY_OWNER* owner;
	int fc;
	int f10;
};

/* ADDRESS: GOLDTL 0x00465e60 */
/* ADDRESS: GOLDDE 0x00459a90 */
void __cdecl d2_ClearOwnerDirtyRects(struct D2_DIRTY_OWNER* e)
{
	int i;
	struct D2_DIRTY_SLOT* s;

	if (!e->f190) {
		return;
	}
	if (!e->f198) {
		return;
	}
	for (i = 0; i < 0x5000; i += 0x14) {
		s = (struct D2_DIRTY_SLOT*) (*(unsigned char**) 0x772588 + i);
		if (s->owner == e) {
			memset(s, 0, 0x14);
		}
	}
}
