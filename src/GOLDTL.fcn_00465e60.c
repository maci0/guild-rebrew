#include <string.h>
#pragma intrinsic(memset)

struct ent_465e60 {
	char pad0[0x190];
	int f190;
	int pad194;
	int f198;
};

struct slot_465e60 {
	int f0;
	int f4;
	struct ent_465e60* owner;
	int fc;
	int f10;
};

/* ADDRESS: GOLDTL 0x00465e60 */
void __cdecl fcn_00465e60(struct ent_465e60* e)
{
	int i;
	struct slot_465e60* s;

	if (!e->f190) {
		return;
	}
	if (!e->f198) {
		return;
	}
	for (i = 0; i < 0x5000; i += 0x14) {
		s = (struct slot_465e60*) (*(unsigned char**) 0x772588 + i);
		if (s->owner == e) {
			memset(s, 0, 0x14);
		}
	}
}
