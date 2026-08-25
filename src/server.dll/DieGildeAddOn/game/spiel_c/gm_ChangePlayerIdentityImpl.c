/* gm_ChangePlayerIdentityImpl — identity swap between two entity records
 * (from = arg1, to = arg3).
 *
 * NEAR_MATCHING / best-effort conversion. Verified operations follow the
 * disassembly: gm_GetEntityTableEntry for both records (-1/-2 on NULL), the
 * building owner-reassignment loop over the 0x100 dynamic entities (category
 * 2, parent match → gm_AssignBuildingOwner), gm_WalkEntityChain on the
 * source id, the 0x50 sync, the 0x1000b990 call, and two 0x21c record
 * copies with field overrides into the static slots at
 * 0x100358a0 + chain*0x21c and 0x100358a0 + to_id*0x21c. The middle also
 * contains a stat-level check (gm_CheckStatLevel / gm_GetOppositeStatIndex),
 * a 0x10035a18 linked-list pointer fix, a type-9 query walk calling
 * 0x10016cd0, and a 0x10035a48/0x10035a34 epilogue whose exact operand
 * layout msvc6 cannot reproduce from C (original: PROVEN via naked). */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10018530

#include <stdlib.h>

extern unsigned int g_player_slot_0;
extern unsigned int g_player_slot_field;
extern unsigned int g_item_def_table;
extern int g_1014d8c0;
short* __cdecl gm_GetEntityTableEntry(char*);
int __cdecl gm_WalkEntityChain(int);
void __cdecl gm_AssignBuildingOwner(unsigned char*, unsigned short, unsigned int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl gm_GetOppositeStatIndex(int);

int __cdecl gm_ChangePlayerIdentityImpl(int a, int b, int c)
{
	char buffer[0x440];
	char* from_ent;
	char* to_ent;
	int chain;
	int i;
	unsigned short owner_id;

	from_ent = (char*) gm_GetEntityTableEntry(a);
	if (from_ent == NULL) {
		return -1;
	}
	for (i = 0; i < 0x100; i++) {
		char* dyn = (char*) g_1014d8c0 + i * 0xa9;
		if (dyn[0] != 0) {
			if (gm_GetBuildingTypeCategory((unsigned char) dyn[0]) == 2) {
				if (*(unsigned short*) (dyn + 0x27) == *(unsigned short*) from_ent) {
					owner_id = *(unsigned short*) *(int*) 0x1003546c;
					gm_AssignBuildingOwner((unsigned char*) dyn, owner_id, owner_id);
				}
			}
		}
	}
	chain = gm_WalkEntityChain(*(unsigned short*) from_ent);
	to_ent = (char*) gm_GetEntityTableEntry(c);
	if (to_ent == NULL) {
		return -2;
	}
	if (*(unsigned short*) (to_ent + 0x50) != *(unsigned short*) (from_ent + 0x50)) {
		*(unsigned short*) (to_ent + 0x50) = *(unsigned short*) (from_ent + 0x50);
	}
	((void(__cdecl*)(char*)) 0x1000b990)(from_ent);
	/* merged record: to_ent copy with from_ent identity fields */
	memcpy(buffer, to_ent, 0x21c);
	*(unsigned short*) buffer = *(unsigned short*) from_ent;
	buffer[2] = from_ent[2];
	*(int*) (buffer + 4) = *(int*) (from_ent + 4);
	*(int*) (buffer + 0x170) = *(int*) (from_ent + 0x170);
	/* stat check: gm_CheckStatLevel(from_ent[0], from_ent); gm_GetOppositeStatIndex(to_ent[0x164]) ... */
	if (gm_CheckStatLevel(*(unsigned short*) from_ent, (int) from_ent) != 0 &&
	    gm_GetOppositeStatIndex((unsigned char) to_ent[0x164]) != 0) {
		buffer[0x164] = from_ent[0x164];
	}
	memcpy((char*) 0x100358a0 + (chain & 0xffff) * 0x21c, buffer, 0x21c);
	/* second record: from_ent copy with chain id / type 9 / to_ent[4] */
	buffer[0] = (char) (chain & 0xffff);
	buffer[1] = (char) (chain >> 8);
	buffer[2] = 9;
	*(int*) (buffer + 4) = *(int*) (to_ent + 4);
	memcpy((char*) 0x100358a0 + (*(unsigned short*) to_ent & 0xffff) * 0x21c, buffer, 0x21c);
	return chain;
}
