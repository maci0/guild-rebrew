#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/game_matrices.h"
#include "Develop/DieGildeAddOn/game/entity_record.h"
int __cdecl cm_ResolveSpecialEntityId(int a, int b);
#define SLOT_DWORD(off) (*(int*)&((ENTITY_RECORD*)(g_7f4ca0 + (off)))->entity_id)
#define SLOT_WORD(off) (*(unsigned short*)&((ENTITY_RECORD*)(g_7f4ca0 + (off)))->entity_index)

/* Updates one slot's relation matrix for the given update kind and mode.
 * Native body: 889 bytes at 0x004c8de0. */
/* ADDRESS: GOLDTL 0x004c8de0 */
int __cdecl fcn_004c8de0(int* a, unsigned char* changed)
{
	char* p;
	int* t;
	int i;
	int j;
	int r1;
	int idx5;
	unsigned int idx4;
	unsigned int idx5idx;
	unsigned int mode;
	int kind;
	int e;
	int v;
	int hi;
	int lo;
	int hiadd;
	int loadd;

	t = a;
	r1 = cm_ResolveSpecialEntityId((int) t, t[4]);
	t[4] = r1;
	idx5 = cm_ResolveSpecialEntityId((int) t, t[5]);
	t[5] = idx5;
	kind = t[7];

	if (kind == 4) {
		mode = (unsigned int) t[9] <= 0 ? 0 : (unsigned int) t[9] >= 4 ? 4 : t[9];
		if (mode <= 0) {
			hi = 0x64; lo = -0x4b; hiadd = -5; loadd = 0xb;
		} else if (mode == 4) {
			hi = 0x28; lo = -0x73; hiadd = -0x14; loadd = 3;
		} else if (mode == 3) {
			hi = 0x37; lo = -0x69; hiadd = -0x10; loadd = 5;
		} else if (mode == 2) {
			hi = 0x46; lo = -0x5f; hiadd = -0xc; loadd = 7;
		} else if (mode == 1) {
			hi = 0x55; lo = -0x55; hiadd = -8; loadd = 9;
		} else {
			hi = 0x64; lo = -0x4b; hiadd = -5; loadd = 0xb;
		}
		for (i = 0; i < 0x300; i++) {
			for (j = 0; j < 0x300; j++) {
				v = (signed char) g_869480[i][j];
				if (i != j && ((ENTITY_RECORD*)g_7f4ca0)[i].entity_index != 0xffff &&
				    ((ENTITY_RECORD*)g_7f4ca0)[j].entity_index != 0xffff) {
					if (v > hi) {
						v += hiadd;
					} else if (v < lo) {
						v += loadd;
					}
					if (v > -0x7f) {
					if (v >= 0x7f) {
						v = 0x7f;
					}
				} else {
					v = -0x7f;
				}
					g_869480[i][j] = (signed char) v;
				}
			}
		}
	} else {
		for (idx4 = 0; idx4 < 0x300; idx4++) {
			if (((ENTITY_RECORD*)g_7f4ca0)[idx4].entity_id == idx5) {
				break;
			}
		}
		if (idx4 >= 0x300 || ((ENTITY_RECORD*)g_7f4ca0)[idx4].entity_index == 0xffff) {
			return 1;
		}
		if (kind == 3) {
			e = ((ENTITY_RECORD*)g_7f4ca0)[idx4].unk_210;
			p = &g_90e0a0[0][idx4];
			for (i = 0; i < 0x300; i++) {
				if (((ENTITY_RECORD*)g_7f4ca0)[i].entity_id != e) {
					*p = (char) (int) ((float) *p * *(float*) (t + 8));
				}
				p += 0x300;
			}
		} else {
			idx5idx = idx4;
			for (idx4 = 0; idx4 < 0x300; idx4++) {
				if (((ENTITY_RECORD*)g_7f4ca0)[idx4].entity_id == r1) {
					break;
				}
			}
			if (idx4 >= 0x300 || ((ENTITY_RECORD*)g_7f4ca0)[idx4].entity_index == 0xffff) {
				return 1;
			}
			if (kind == 2) {
				v = (signed char) g_869480[idx4][idx5idx];
				g_90e0a0[idx4][idx5idx] = 0;
				v += t[6];
				if (v >= -0x7f) {
					if (v >= 0x7f) {
						v = 0x7f;
					}
				} else {
					v = -0x7f;
				}
				g_869480[idx4][idx5idx] = (signed char) v;
			} else if (kind == 1) {
				v = (signed char) g_869480[idx4][idx5idx] + t[6];
				v = v < -0x7f ? -0x7f : v >= 0x7f ? 0x7f : v;
				g_869480[idx4][idx5idx] = (signed char) v;
				if (t[6] >= 0) {
					v = v / 2;
				}
				v += (signed char) g_90e0a0[idx4][idx5idx];
				v = v < -0x7f ? -0x7f : v >= 0x7f ? 0x7f : v;
				g_90e0a0[idx4][idx5idx] = (signed char) v;
			} else if (kind == 0) {
				v = (signed char) g_869480[idx4][idx5idx] + t[6];
				v = v < -0x7f ? -0x7f : v >= 0x7f ? 0x7f : v;
				g_869480[idx4][idx5idx] = (signed char) v;
			}
		}
	}
	if (changed != 0) {
		*changed = 1;
	}
	return 0;
}
