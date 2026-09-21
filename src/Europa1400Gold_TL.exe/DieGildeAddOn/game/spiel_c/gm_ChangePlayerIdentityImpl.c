/* gm_ChangePlayerIdentityImpl - identity swap between two dynasty records.
 *
 * Two 0x21c-byte stack copies are built: rec_a from the destination record
 * patched with the source header, rec_b from the source record patched with
 * the destination header. rec_a is written to the chain slot of g_slot_table
 * (0x100358a0), rec_b to the destination slot. The object chains at slot+0x178
 * are re-parented, the 0x300 x 8 id table at 0x100358fc has the two ids
 * swapped, and the record left in the chain slot is released.
 *
 * The third parameter is unreferenced; the swap partner is parameter two.
 * Frame: sub esp,0x44c plus four callee-saved pushes; rec_a at [esp+0x24],
 * rec_b at [esp+0x240].
 *
 * Five dword slots live below rec_a. Tracking esp through the unbalanced
 * pushes they are: 0x10 counter, 0x14 to_slot (stored 16-bit wide), 0x18 the
 * first gm_GetOppositeStatIndex result, 0x1c chain, 0x20 stat_ent. chain and
 * the gm_WalkEntityChain result are separate values: chain indexes the slot
 * table and is the return value, while the walk result is only stored to
 * 0x10035a48. Merging them loses a slot and shrinks the frame to 0x448.
 *
 * chain is unsigned short, and the local gm_WalkEntityChain prototype narrows
 * its parameter to match. An int chain widens the argument with an extra xor
 * and needs a chain &= 0xffff mask before the slot indexing; the 16-bit local
 * spills as a dword and reloads through the target's own and ebp,0xffff. The
 * pushed value is unchanged either way, since a 0..0xffff unsigned short
 * promotes to the same int. The definition in spiel622.c takes int.
 *
 * The 0x18 slot only appears when the second gm_GetOppositeStatIndex call sits
 * directly in the comparison. Naming its result in a local coalesces the two
 * calls into one register and drops the mov edx,eax.
 *
 * The building scan indexes with i * 0xa9 over a plain i++ counter, not an
 * i += 0xa9 byte offset: the multiply is what gives the counter the SIB base
 * role in mov al,[edi+ecx] / lea esi,[edi+ecx].
 *
 * The rec_a header patch order is +4, +0, +2, +0xd, +0x170. That order decides
 * which loads msvc6 hoists above the rep movsd (byte [ebp+2] and word [ebp],
 * not the dword [ebp+4]).
 *
 * gm_AddObjekt takes the owner id out of rec_a+4 (target loads
 * [esp+0x30] with two arguments already pushed), not the to_id parameter.
 */

// FUNCTION: GOLDTL 0x422150
// SIZE: 784

#include <stdlib.h>
#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern unsigned short* g_entity_table_end; /* 0x1003546c */

int __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_WalkEntityChain(unsigned short);
void __cdecl gm_AssignBuildingOwner(char*, int, int);
int __cdecl gm_GetBuildingTypeCategory(int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl gm_GetOppositeStatIndex(int);
int __cdecl gm_MapEntityStatRange(int);
char* __cdecl gm_GetEntityTableEntry(char*);
void __cdecl gm_AddObjekt(int, int, int);
void __cdecl gm_KillSpieler(int, int);
void __cdecl amt_ClearEntityLinks(char*);

int __cdecl gm_ChangePlayerIdentityImpl(int from_id, int to_id, int unused)
{
	int counter;
	int owner;
	unsigned short to_slot;
	unsigned short chain;
	int link;
	char rec_a[0x21c];
	char rec_b[0x21c];
	char* from_ent;
	char* to_ent;
	char* ent;
	char* stat_ent;
	char* obj;
	char* dst;
	int i;
	int level;
	int range;
	unsigned short obj_type;

	(void) unused;

	from_ent = (char*) gm_LookupEntityRecordById(from_id);
	if (from_ent == NULL) {
		return -1;
	}

	i = 0;
	counter = 0x100;
	do {
		ent = (char*) g_entity_ptr + i * 0xa9;
		if (*ent != 0) {
			if (gm_GetBuildingTypeCategory(*ent & 0xff) == 2) {
				if (*(unsigned short*) (ent + 0x27) == *(unsigned short*) from_ent) {
					owner = *g_entity_table_end;
					gm_AssignBuildingOwner(ent, owner, owner);
				}
			}
		}
		i++;
		counter--;
	} while (counter != 0);

	chain = *(unsigned short*) from_ent;
	link = gm_WalkEntityChain(chain);
	to_ent = (char*) gm_LookupEntityRecordById(to_id);
	if (to_ent == NULL) {
		return -2;
	}
	to_slot = *(unsigned short*) to_ent;
	if (*(unsigned short*) (from_ent + 0x50) != *(unsigned short*) (to_ent + 0x50)) {
		*(unsigned short*) (to_ent + 0x50) = *(unsigned short*) (from_ent + 0x50);
	}
	amt_ClearEntityLinks(from_ent);

	memcpy(rec_a, to_ent, 0x21c);
	*(int*) (rec_a + 4) = *(int*) (from_ent + 4);
	*(unsigned short*) rec_a = *(unsigned short*) from_ent;
	rec_a[2] = from_ent[2];
	rec_a[0xd] = from_ent[0xd];
	*(int*) (rec_a + 0x170) = *(int*) (from_ent + 0x170);

	range = gm_MapEntityStatRange(to_ent[0x164] & 0xff);
	if (range != 0) {
		stat_ent = gm_GetEntityTableEntry(from_ent);
		if (stat_ent != NULL) {
			level = gm_CheckStatLevel(*(unsigned short*) from_ent, range);
			if (level != 0) {
				if (gm_GetOppositeStatIndex(level) <
					gm_GetOppositeStatIndex(to_ent[0x164] & 0xff)) {
					stat_ent[range + 0x74] = to_ent[0x164];
				} else {
					rec_a[0x164] = from_ent[0x164];
				}
			}
		}
	} else {
		rec_a[0x164] = from_ent[0x164];
	}

	memcpy(rec_b, from_ent, 0x21c);
	*(int*) (rec_b + 4) = *(int*) (to_ent + 4);
	*(unsigned short*) rec_b = *(unsigned short*) to_ent;
	rec_b[2] = 9;

	memcpy((char*) 0x100358a0 + chain * 0x21c, rec_a, 0x21c);
	memcpy((char*) 0x100358a0 + to_slot * 0x21c, rec_b, 0x21c);

	obj = *(char**) ((char*) 0x10035a18 + chain * 0x21c);
	while (obj != NULL) {
		*(int*) (obj + 6) = *(int*) ((char*) 0x100358a4 + chain * 0x21c);
		obj = *(char**) (obj + 0x3f);
	}
	obj = *(char**) ((char*) 0x10035a18 + to_slot * 0x21c);
	while (obj != NULL) {
		*(int*) (obj + 6) = *(int*) ((char*) 0x100358a4 + to_slot * 0x21c);
		obj = *(char**) (obj + 0x3f);
	}

	dst = (char*) 0x100358fc;
	counter = 0x300;
	do {
		ent = dst;
		level = 8;
		do {
			if (*(int*) ent == from_id) {
				*(int*) ent = to_id;
			} else if (*(int*) ent == to_id) {
				*(int*) ent = from_id;
			}
			ent += 4;
			level--;
		} while (level != 0);
		dst += 0x21c;
		counter--;
	} while (counter != 0);

	obj = *(char**) (rec_b + 0x178);
	while (obj != NULL) {
		obj_type = *(unsigned short*) obj;
		if (obj_type != 0) {
			if (g_item_def_table[(obj_type << 6) + obj_type] == 9) {
				gm_AddObjekt(*(int*) (rec_a + 4), obj_type,
					*(int*) (obj + 0xe));
			}
		}
		obj = *(char**) (obj + 0x3f);
	}

	*(int*) ((char*) 0x10035a48 + chain * 0x21c) = link;
	*(int*) ((char*) 0x10035a34 + chain * 0x21c) = 4;
	*(int*) ((char*) 0x10035a68 + chain * 0x21c) = 0;
	gm_KillSpieler(*(unsigned short*) rec_b, 0);

	return chain;
}
