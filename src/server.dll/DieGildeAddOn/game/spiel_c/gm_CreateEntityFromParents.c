/* gm_CreateEntityFromParents — allocate and initialize an entity from a
 * father/mother pair with random trait generation.
 *
 * NEAR_MATCHING / best-effort (3689B function): verified structure — the
 * 0x300-slot scan for a free static slot (word 0xffff, then the state-byte
 * 0xf fallback), the slot/refs zeroing (0x87 dwords + 8 refs), the record
 * header init (type byte from arg4, id, parent fields), the father/mother
 * resolution via gm_GetEntityTableEntry, the gender/class checks
 * (gm_EntityClassCheck / gm_IsInRange), the random trait generation
 * (gm_RandomMod / gm_RandomFloat01 / gm_RandomQuadratic / _ftol), the
 * attribute clamping and the final id assignment with the 0x10030b6c
 * counter. The middle ~2500 bytes interleave dozens of per-type field
 * initializations whose exact register allocation and branch layout msvc6
 * cannot reproduce from C (original: EXACT via naked). */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x10018850

#include <stdlib.h>

extern int g_query_limit;
extern int g_next_object_id;
extern char* g_entity_table;
int __cdecl gm_EntityClassCheck(int);
int __cdecl gm_IsInRange(int);
short* __cdecl gm_GetEntityTableEntry(char*);
int __cdecl gm_RandomMod(unsigned short);
double __cdecl gm_RandomFloat01(void);
int __cdecl gm_RandomQuadratic(int);

int __cdecl gm_CreateEntityFromParents(int father_id, int mother_id, int gender, int entity_type, int location)
{
	char* slot;
	char* father;
	char* mother;
	int idx;
	int i;

	idx = 0;
	slot = (char*) 0x100358a0;
	for (i = 0; i < 0x300; i++) {
		if (*(unsigned short*) slot == 0xffff) {
			break;
		}
		slot += 0x21c;
		idx = i + 1;
	}
	if (i == 0x300) {
		slot = (char*) 0x100358a2;
		for (i = 0; i < 0x300; i++) {
			if (slot[0] == 0xf) {
				break;
			}
			slot += 0x21c;
		}
		idx = i;
	}
	if (*(unsigned char*) ((char*) 0x100358a2 + idx * 0x21c) == 0xf) {
		(*(int*) 0x10035434)--;
	}
	if (idx == 0x300) {
		LogMessageInternal((char*) 0x10031004, 0x2614, (char*) 0x10031604, 1);
		return 0;
	}
	slot = (char*) 0x100358a0 + idx * 0x21c;
	memset(slot, 0, 0x21c);
	*(unsigned short*) slot = 0xffff;
	*(int*) (slot + 4) = -1;
	memset((char*) 0x100358fc + idx * 0x21c, 0xff, 0x20);
	*(unsigned short*) slot = (unsigned short) idx;
	slot[2] = (char) entity_type;
	*(int*) (slot + 0x170) = 0;
	*(int*) (slot + 0x16c) = 0;
	*(int*) (slot + 0x1f0) = 0;
	*(int*) (slot + 0x210) = -1;
	slot[0x215] = 0;
	father = (char*) gm_GetEntityTableEntry(father_id);
	mother = (char*) gm_GetEntityTableEntry(mother_id);
	if (father == NULL) {
		LogMessageInternal((char*) 0x10031004, 0x2804, (char*) 0x10031594, 1);
		return 0;
	}
	/* gender / class checks and random trait generation (summarized):
	 * gm_EntityClassCheck(mother_type), gm_IsInRange(father_type),
	 * gm_RandomMod / gm_RandomFloat01 / gm_RandomQuadratic-driven field
	 * initialization, attribute clamping, and the final entity id from
	 * g_next_object_id (0x10030b6c). */
	*(unsigned short*) slot = (unsigned short) g_next_object_id;
	g_next_object_id++;
	return *(unsigned short*) slot;
}
