


// SIZE 0x18
typedef struct {
	unsigned char c0;
	char pad1[3];
	int id;
	char pad8[0x10];
} rec18;

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"











int __cdecl fcn_004e8b40(int, rec18*);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl amt_AdjustOfficeHoldersFavor(ENTITY_RECORD*, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl fcn_00545d40(int, int, char*, unsigned char, int, char*);

void __cdecl he_ApplyZigeunerFavorPenalty(ENTITY_RECORD* a, ENTITY_RECORD* b)
{
	rec18 r;
	char text1[0x400];
	char text2[0x400];
	int i;
	int d;
	int p;
	int id;

	if (fcn_004e8b40(b->unk_165[1], &r) != 0 && (p = r.id) != 0) {
		amt_AdjustOfficeHoldersFavor(b, p, -20 - gm_RandomMod(0x10));
	} else if (b->entity_state != 6 && b->entity_state != 7 && b->entity_state != 5) {
		amt_AdjustOfficeHoldersFavor(b, gm_RandomMod(3) + 1, gm_RandomMod(0x10) + 0x14);
	} else {
		d = -20 - gm_RandomMod(0x10);
		for (i = 0; i < 768; i++) {
			if (i != b->entity_index && (((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 6 || ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 7 || ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_type == 5)) {
				fcn_004c54c0(b->entity_id, ((ENTITY_RECORD_VIEW*)g_7f4ca0)[i].entity_id, d, 1);
			}
		}
	}
	if (b == a) {
		id = 0x41dd;
	} else {
		id = 0x41dc;
	}
	io_FormatTextBuffer(text1, 0x41df);
	io_FormatTextBuffer(text2, id, text1);
	fcn_00545d40(b->entity_id, -1, text2, 1, 0x5fb, 0);
}
