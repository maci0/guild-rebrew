#include "../entity.h"
/* InitNewDynastyEntity - initializes a dynasty entity: sets its link flags,
 * fills the static field buffers with random height values, initializes the
 * entity's geometry/speed fields and spawn stats (5 values), then links it
 * into the season-based entity table.
 *
 * Returns void: the only caller (0x100196a2) discards the return value and
 * the reference's EAX at exit is the discarded gm_RandomMod(2) result, so the
 * earlier `int` prototype made symbolic proving fail on junk EAX.
 *
 * The 0x5c..0x7c fill is written as an explicit 8x int loop rather than
 * memset(): the compiler unrolls it to the same `rep stosd`, but with the
 * setup instruction order the reference uses. */

// FUNCTION: GOLDTL 0x5d6030
// SIZE: 416

extern int __cdecl gm_RandomMod(int n);
extern int __cdecl amt_FindEntity26(int entity_id);
extern int __cdecl amt_FindEntity27(int entity_id);
extern int __cdecl gm_AddObjekt(int a, int b, int c);
extern unsigned char g_current_season;
/* 189 4-byte entries per object type; only the low word of each entry is read. */

void __cdecl InitNewDynastyEntity(int a, void* unused, unsigned short word_arg, void* entity)
{
	int i;
	int j;
	int cursor;
	int off;
	int flags;
	int k;

	(void) unused;

	if (a == 0x15) {
		flags = *(int*) ((char*) entity + 0x1cc);
		flags |= 0x1000;
		*(int*) ((char*) entity + 0x1cc) = flags;
		amt_FindEntity26(*(int*) ((char*) entity + 4));
	} else {
		flags = *(int*) ((char*) entity + 0x1cc);
		flags |= 0x2000;
		*(int*) ((char*) entity + 0x1cc) = flags;
		amt_FindEntity27(*(int*) ((char*) entity + 4));
	}
	*(unsigned short*) ((char*) entity + 0xa) = word_arg;
	*(char*) ((char*) entity + 0xc) = 0;
	for (cursor = (int) g_relationship_matrix_primary; cursor < (int) g_relationship_matrix_primary + 0x90000; cursor += 0x300) {
		i = 0;
		off = cursor - (int) g_relationship_matrix_primary;
		for (; i < 0x300; i++) {
			g_relationship_matrix_primary[off + i] = (unsigned char) (gm_RandomMod(0x40) - 0x20);
			g_relationship_matrix_secondary[off + i] = 0;
		}
	}
	*(unsigned short*) ((char*) entity + 0x50) = 0x7fff;
	*(int*) ((char*) entity + 0x7c) = 0;
	*(char*) ((char*) entity + 0x58) = 0;
	for (k = 0; k < 8; k++) {
		((int*) ((char*) entity + 0x5c))[k] = -1;
	}
	*(int*) ((char*) entity + 0x170) = 0;
	*(int*) ((char*) entity + 0x16c) = 0;
	*(float*) ((char*) entity + 0x1c) = 1000.0f;
	*(float*) ((char*) entity + 0x14) = 1.0f;
	*(float*) ((char*) entity + 0x20) = 12.0f;
	*(float*) ((char*) entity + 0x10) = 330.0f;
	*(float*) ((char*) entity + 0x18) = 1000.0f;
	for (j = 0; j < 5; j++) {
		*(char*) ((char*) entity + 0x80 + j) =
			(char) (long) ((float) (gm_RandomMod(0x2a) & 0xffff) + *(float*) 0x10025808);
	}
	*(char*) ((char*) entity + 0xd) = 9;
	gm_AddObjekt(*(int*) ((char*) entity + 4),
	             (unsigned short) g_entity_slot_table[(unsigned int) g_current_season * 189],
	             0xf42400);
	gm_RandomMod(2);
	*(char*) ((char*) entity + 2) = 3;
}
