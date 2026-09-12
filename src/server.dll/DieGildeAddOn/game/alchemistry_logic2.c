#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <string.h>
int __cdecl _ftol(void);

typedef int(__cdecl* dispatch_fn)(unsigned char*);

extern char* g_table;
int __cdecl gm_ResolveEntityById(void** dynamic, int zero1, int zero2, int id);
int __cdecl gm_RandomMod(int range);
float __cdecl gm_RandomFloat01(void);
void __cdecl gm_AddObjekt(int p1, int p2, int p3);
int __cdecl gm_ObjectsAvailble(int season);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_KillSpieler(unsigned int index, int param);
void* __cdecl gm_NextEntityQueryMatch(void);
extern float g_color_scale;
extern int g_next_object_id;
extern unsigned char g_current_season;
extern float g_const_0_0;
extern float g_const_1_0;
extern double g_dbl_const_6d0; /* 0x100256d0 */
extern int g_alchemy_entity_table[];
int* __cdecl ahm_LookupEntityInTable(int);
extern dispatch_fn g_chain_handler_table[];

// SIZE 0x8
typedef struct {
	int key;
	int val;
} PAIR;

// SIZE 0x14
typedef struct {
	char hdr[8];
	int key;
	char pad[4];
	int val;
} SRC;

// SIZE 0x3c
typedef struct {
	char hdr[0xc];
	PAIR entries[6];
} TGT;

// CFLAGS: /O2 /Gd

unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);

// FUNCTION: SERVER 0x1000c1e0
// ahm_ApplyColorComponent

int __cdecl ahm_ApplyColorComponent(char* color_cmd, char* target)
{
	float val;
	switch (*(int*) (color_cmd + 8)) {
	case 0:
		val = *(float*) (color_cmd + 0x10);
		*(unsigned char*) (target + 8) = (unsigned char) (int) (val * g_color_scale);
		return 1;
	case 1:
		val = *(float*) (color_cmd + 0x10);
		*(unsigned char*) (target + 9) = (unsigned char) (int) (val * g_color_scale);
		return 1;
	case 2:
		val = *(float*) (color_cmd + 0x10);
		*(unsigned char*) (target + 0xa) = (unsigned char) (int) (val * g_color_scale);
		return 1;
	case 3:
		val = *(float*) (color_cmd + 0x10);
		*(unsigned char*) (target + 0xb) = (unsigned char) (int) (val * g_color_scale);
		return 1;
	default:
		return 0;
	}
}

/* Allocates an entity slot in the alchemy system. Finds a
 * free slot in the entity table and initializes it with the
 * given parameters. */

// FUNCTION: SERVER 0x1000c280
// SIZE: 130

int __cdecl ahm_AllocateEntitySlot(int obj, int tgt, int src)
{
	int i;
	unsigned short* query;

	for (i = 0; i < 6; i++) {
		if (*(int*) (tgt + 0xc + i * 8) == 0) {
			query = gm_ff_Objekt(*(int*) (src + 0x5d), 2, 6, 0, 0xff);
			*(int*) (obj + 0x14) = g_next_object_id;
			*(int*) (tgt + 0xc + i * 8) = *(int*) (obj + 8);
			*(int*) (tgt + 0x10 + i * 8) = *(int*) (obj + 0x10);
			if (query != 0)
				gm_AddObjekt(*(int*) ((char*) query + 2), *(int*) (obj + 8), 2);
			gm_ObjectsAvailble(g_current_season);
			return 1;
		}
	}
	return 0;
}


/* Clears a slot if it matches a target value. Used during
 * alchemy cleanup to remove specific entity references. */

// FUNCTION: SERVER 0x1000C310
// ahm_SlotClearMatch

int __cdecl ahm_SlotClearMatch(char* data, char* target, char* src)
{
	int i;
	char* slot_ptr;
	int key;
	int ent;
	key = *(int*) (data + 8);
	i = 0;
	slot_ptr = target + 0xc;
	while (i < 6) {
		if (*(int*) slot_ptr == key) {
			goto found;
		}
		i++;
		slot_ptr += 8;
	}
	return 0;
found:
	ent = (int) gm_ff_Objekt(*(int*) (src + 0x5d), 2, 6, 0, 0xff);
	if (ent) {
		gm_RemoveObjectByType((void**) (ent + 0x14), *(unsigned int*) (data + 8));
	}
	*(int*) (target + i * 8 + 0xc) = 0;
	*(int*) (target + i * 8 + 0x10) = 0;
	return 1;
}

/* Searches for a value and sets it in the target. Used for
 * alchemy recipe ingredient matching and assignment. */

// FUNCTION: SERVER 0x1000C380
// ahm_SearchAndSet

int __cdecl ahm_SearchAndSet(SRC* src, TGT* tgt)
{
	int i;
	for (i = 0; i < 6; i++) {
		if (tgt->entries[i].key == src->key) {
			tgt->entries[i].val = src->val;
			return 1;
		}
	}
	return 0;
}

/* Clamps a floating-point alchemy value to valid bounds.
 * Prevents stat overflow/underflow during recipe processing.
 * g_const_0_0 (0x100256cc) and g_const_1_0 (0x100256a0) hold
 * 0.0f and 1.0f, so this is a clamp into [0.0, 1.0].
 *
 * The in-range test is one short-circuit `&&`, not a nested if, and the two
 * clamp arms select a value into a local that a single trailing store writes.
 * That shape alone gives the target's bytes; no volatile, flag local or
 * merge blocker is needed.
 *
 * Why the nested-if spellings could not get there. The target keeps three
 * blocks: the in-range one stores then sets eax, while both clamp blocks set
 * eax before the store. A nested if makes all three tails identical, so the
 * cross-jump pass merges the clamp arms into a 74-byte body. Splitting the
 * value selection from the store is what makes the clamp tails differ from
 * the in-range tail, which blocks the merge for free and simultaneously
 * fixes the eax scheduling.
 *
 * Dead ends from earlier passes, all on nested-if variants: routing the
 * constants through a float local, per-arm float temps, a `static const int`
 * return blocker (83 bytes and the right block order, but the return then
 * loads from memory instead of an immediate), volatile on the constant, the
 * destination or the local, goto chains for block layout, and a
 * /G3../G6 /Ox /Gy /Gf /Op /Za flag sweep. None beat 64/83. */


// FUNCTION: SERVER 0x1000c3c0
// SIZE: 83

int __cdecl ahm_ClampFloatValue(float* arg1, float* arg2)
{
	float sum;
	float clamp;

	sum = arg1[4] + arg2[1];
	if (sum > g_const_0_0 && sum < g_const_1_0) {
		arg2[1] = sum;
		return 1;
	}
	if (sum <= g_const_0_0) {
		clamp = g_const_0_0;
	} else {
		clamp = g_const_1_0;
	}
	arg2[1] = clamp;
	return 1;
}

/* Fires (activates) an alchemy entity and cleans up the
 * processing state. Finalizes the recipe output and resets
 * the alchemist for the next batch. */

// FUNCTION: SERVER 0x1000c420
// ahm_FireEntityAndCleanup

int __cdecl ahm_FireEntityAndCleanup(int cmd, int* entity_id_ptr, int parent_record)
{
	unsigned short* entity;
	void* query_result;
	unsigned int* slot_iter;
	int count;

	(void) cmd;
	entity = (unsigned short*) gm_LookupEntityRecordById(*entity_id_ptr);
	if (entity != (unsigned short*) 0) {
		query_result = gm_ff_Objekt(*(int*) (parent_record + 0x5d), 2, 6, 0, 0xff);
		*(int*) (entity + 0xb8) = 0;
		*(int*) (entity + 0xb6) = 0;
		slot_iter = (unsigned int*) (entity_id_ptr + 3);
		count = 6;
		do {
			if (*slot_iter != 0) {
				if (query_result != (void*) 0) {
					gm_RemoveObjectByType((void**) ((int) query_result + 0x14), *slot_iter);
				}
				*slot_iter = 0;
				slot_iter[1] = 0;
			}
			slot_iter = slot_iter + 2;
			count = count - 1;
		} while (count != 0);
		for (count = 0xf; count != 0; count--) {
			*entity_id_ptr = 0;
			entity_id_ptr = entity_id_ptr + 1;
		}
		gm_KillSpieler(*entity, 1);
		return 1;
	}
	return 0;
}

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx);
void* __cdecl m_AllocTracked(unsigned int allocSize, const char* groupTag);

/* Allocates and initializes the alchemy info structure for
 * a building. Sets up recipe slots and ingredient storage. */

// DATA: SERVER 0x1002a0f8
char s_ahm_AllocAhmInfo_1002a0f8[] = "ahm_AllocAhmInfo";

// FUNCTION: SERVER 0x1000c4d0
// SIZE: 295

int __cdecl ahm_AllocAhmInfo(int cmd_payload, int arg2)
{
	char buf[0x3c];
	int i;

	if (!ls_ReadVfsDataChecked(buf, 4, 1, cmd_payload))
		return 0;
	if (!ls_ReadVfsDataChecked(buf + 4, 4, 1, cmd_payload))
		return 0;
	if (!ls_ReadVfsDataChecked(buf + 8, 1, 1, cmd_payload))
		return 0;
	if (!ls_ReadVfsDataChecked(buf + 9, 1, 1, cmd_payload))
		return 0;
	if (!ls_ReadVfsDataChecked(buf + 0xa, 1, 1, cmd_payload))
		return 0;
	if (!ls_ReadVfsDataChecked(buf + 0xb, 1, 1, cmd_payload))
		return 0;
	for (i = 0; i < 6; i++) {
		if (!ls_ReadVfsDataChecked(buf + 0xc + i * 8, 4, 1, cmd_payload))
			return 0;
		if (!ls_ReadVfsDataChecked(buf + 0x10 + i * 8, 4, 1, cmd_payload))
			return 0;
	}
	if (*(int*) (arg2 + 0x65) == 0)
		*(int*) (arg2 + 0x65) = (int) m_AllocTracked(0x3c, s_ahm_AllocAhmInfo_1002a0f8);
	memcpy((void*) *(int*) (arg2 + 0x65), buf, 0x3c);
	return 1;
}

// FUNCTION: SERVER 0x1000c600
// SIZE: 109

char* __cdecl ahm_InitRandomEntity(void)
{
	unsigned int idx;
	int counter;
	unsigned int off;
	float* table_cursor;
	int n;

	idx = gm_RandomMod(0x20) & 0xffff;
	counter = 0x20;
	while (counter != 0) {
		if (*(unsigned char*) (0x1002a2c2 + idx * 244) == 0)
			goto found;
		counter--;
		idx = (idx + 1) & 0x1f;
	}
	return 0;
found:
	off = idx * 244;
	table_cursor = (float*) (0x1002a200 + off);
	n = 0xe;
	do {
		/* volatile pins the store right after the multiply; without it
		 * MSVC6 sinks it past the pointer bump to `fstp [eax-0xc]`. */
		*(volatile float*) table_cursor = table_cursor[-1] * g_dbl_const_6d0;
		table_cursor += 3;
		n--;
	} while (n != 0);
	*(unsigned char*) (0x1002a2c2 + off) = 1;
	return (char*) (0x1002a1d0 + off);
}

// FUNCTION: SERVER 0x1000c670
// ahm_LookupEntityInTable

int* __cdecl ahm_LookupEntityInTable(int entity_id)
{
	int i;
	int* table_cursor;

	for (i = 0, table_cursor = g_alchemy_entity_table; (int) table_cursor < (int) (g_alchemy_entity_table + 0x17 * 10); table_cursor += 0x17, i++) {
		if (*table_cursor == entity_id) {
			return g_alchemy_entity_table + i * 0x17;
		}
	}
	return (int*) 0;
}

/* Queries what building type an alchemy entity belongs to.
 * Returns the building type category for alchemy purposes. */

// FUNCTION: SERVER 0x1000c6a0
// SIZE: 102

int __cdecl ahm_QueryEntityBuildingType(int arg1)
{
	unsigned short* query;
	int* entry;

	query = gm_ff_Objekt(*(int*) (arg1 + 0x178), 1, 5);
	while (query != 0) {
		entry = ahm_LookupEntityInTable(*(unsigned short*) query);
		if (entry != 0) {
			if ((*(int*) ((char*) entry + 0x58) == 1 ||
			     *(int*) ((char*) entry + 0x58) == 2) &&
			    *(int*) ((char*) query + 0x20) <= 0)
				entry = ahm_LookupEntityInTable(0);
			return entry;
		}
		query = gm_NextEntityQueryMatch();
	}
	return ahm_LookupEntityInTable(0);
}
