#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include "entity.h"

typedef int(__cdecl* dispatch_fn)(unsigned char*);

int __cdecl gm_RandomMod(int range);
void __cdecl gm_AddObjekt(int p1, int p2, int p3);
int __cdecl gm_ObjectsAvailble(int season);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_KillSpieler(unsigned int index, int param);
void* __cdecl gm_NextEntityQueryMatch(void);
extern float g_color_scale;
extern int g_next_object_id;
extern unsigned char g_current_season;
extern const float g_const_0_0;

extern double g_const_2; /* 0x10025688 */

extern double g_const_0_001; /* 0x100256d0 */


extern double g_const_0_2; /* 0x10025810 */

extern float g_const_0_6; /* 0x10025f88 */

extern double g_const_8; /* 0x10025f90 */

extern double g_const_900; /* 0x10025f98 */

/* 32 records at a 244-byte stride.  ahm_InitRandomEntity addresses them by raw
 * address (0x1002a1d0, 0x1002a200 and the in-use byte at 0x1002a2c2, each
 * plus idx * 244); the bytes are the reference's. */

float g_alchemy_one = 1.0f;

float g_alchemy_half = 0.5f;






extern unsigned char g_alchemy_random_table[];
extern int g_alchemy_entity_table[];
extern dispatch_fn g_chain_handler_table[];

int* __cdecl ahm_LookupEntityInTable(int);

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

unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);

extern unsigned char g_connections[0x264264];


/* Clamps a floating-point alchemy value to valid bounds.
 * Prevents stat overflow/underflow during recipe processing.
 * g_const_0_0 (0x100256cc) and g_const_1_0f (0x100256a0) hold
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



/* Resets an alchemy entity to its initial state by zeroing
 * out its operational fields via memset. */


void __cdecl ahm_ResetEntityState(void* a)
{
	if (*(unsigned char*) ((char*) a + 2) == 1 ||
	    *(unsigned char*) ((char*) a + 2) == 2) {
		if (*(unsigned char*) ((char*) a + 0x164) != 0) {
			memset((char*) a + 0x1b4, 0, 0x10);
			*(int*) ((char*) a + 0x1c0) = -1;
			*(int*) ((char*) a + 0x1b4) |= 1;
		}
	}
}

/* Checks the flag state of an alchemy entity's linked record.  Returns
 * non-zero when the entity type table marks it as an alchemy building
 * (0x1e) and the record carries an allocated data pointer. */



int __cdecl ahm_CheckFlag(void* a)
{
	char* rec;

	if (*(int*) ((char*) a + 0x1cc) & 4) {
		rec = *(char**) ((char*) a + 0x16c);
		if (rec != 0) {
			if (*(unsigned char*) (g_entity_type_table +
			    *(unsigned char*) rec + *(unsigned char*) rec * 0x24c) == 0x1e)
				return *(int*) (rec + 0x65) != 0;
		}
	}
	return 0;
}


#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "entity.h"

typedef int(__cdecl* dispatch_fn)(unsigned char*);

int __cdecl gm_ResolveEntityById(void** dynamic, int zero1, int zero2, int id);
int __cdecl gm_RandomMod(int range);
float __cdecl gm_RandomQuadratic(void);
void __cdecl gm_AddObjekt(int p1, int p2, int p3);
int __cdecl gm_ObjectsAvailble(int season);
extern int g_next_object_id;
extern unsigned char g_current_season;

extern int g_citizen_count;
extern unsigned char g_slot_table[2];
extern unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);
extern void __cdecl gm_RemoveObjectByType(int*, int);
void* __cdecl m_AllocTracked(unsigned int size, const char* source);
/* Defined in alchemistry_logic2.c; same literal, same VA. */

/* Allocates a new alchemy entity: resolves the parent building record,
 * finds a free slot in the static entity table (0x100358a0, stride 0x21c),
 * initializes the slot from the command payload, fills the alchemy grid
 * (0x100a9820 / 0x1014d8e0) with random values, and allocates/refreshes the
 * building's alchemy data block (record->0x65). Returns the slot index or
 * 0xffff on failure.
 *
 * Matches the reference (1002 bytes).  The inline comments at each block say
 * which spelling is load-bearing. */

unsigned int __cdecl ahm_ExAllocAlchemist(int cmd_payload)
{
	void* dynamic;
	int building_type;
	char* slot;
	int slot_index;
	int rand_value;
	int* query_result;
	int found_record;
	short item_type;
	int building_id;
	int alch_data_ptr;
	int alch_props;
	int one;
	int minus_one;
	int i;
	unsigned short kind;

	building_id = *(int*) (cmd_payload + 8);
	gm_ResolveEntityById(&dynamic, 0, 0, building_id);
	if (dynamic == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\alchemistry_logic.c", 0x449, "ahm_ExAllocAlchemist: cant find target geb...", 1);
		return 0xffff;
	}

	building_type = (unsigned char) *(char*) dynamic;
	if (*((char*) (g_entity_type_table + building_type + building_type * 0x24c)) != 0x1e) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\alchemistry_logic.c", 0x451, "ahm_ExAllocAlchemist: wrong type of target geb...", 1);
		goto ret_false;
	}

	for (slot_index = 0; slot_index < 0x300; slot_index++) {
		if (*(unsigned short*) (g_slot_table + slot_index * 0x21c) == 0xffff)
			break;
	}
	if (slot_index == 0x300) {
		for (slot_index = 0; slot_index < 0x300; slot_index++) {
			if (*(char*) (g_slot_table + slot_index * 0x21c + 2) == 0xf)
				break;
		}
		if (slot_index == 0x300) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\alchemistry_logic.c", 0x45d, "ahm_ExAllocAlchemist: array overflow...", 1);
			ret_false:
			return 0xffff;
		}
	}

	if (*(char*) (g_slot_table + slot_index * 0x21c + 2) == 0xf) {
		g_citizen_count = g_citizen_count - 1;
	}

	memset((void*) (g_slot_table + slot_index * 0x21c), 0, 0x21c);
	/* The 0xffff and +4 stores go through the symbol.  Through `slot`, c2
	 * drops the 0xffff store as overwritten by the slot-index store below
	 * (the named g_citizen_count read between them cannot alias it).  The
	 * +4 store cannot be proved disjoint from it, which lifts its priority
	 * just below the `or eax,-1`: `or eax,-1; mov word ptr [esi],0xffff` at
	 * 0x1000bee6.  The +0x5c fill is a loop, not memset: the destination
	 * stays its own register, `lea edx,[edx+..]; mov edi,edx` as at
	 * 0x1000bef4 (shapes 197). */
	slot = (char*) (g_slot_table + slot_index * 0x21c);
	minus_one = -1;
	*(unsigned short*) (g_slot_table + slot_index * 0x21c) = 0xffff;
	*(int*) (g_slot_table + slot_index * 0x21c + 4) = minus_one;
	for (i = 0; i < 8; i++)
		((int*) (g_slot_table + slot_index * 0x21c + 0x5c))[i] = minus_one;

	/* Both counters are read into a local ahead of their stores and written
	 * back after, which emits the reference's ecx traffic instead of a
	 * load-inc-store pair.  The slot-index store goes through `slot`: there
	 * it has no may-alias edges to the later slot stores, so its priority
	 * drops below the `mov dl,1`, as at 0x1000bf09.  Through the symbol it
	 * outranks the `1` and issues first. */
	{
		int live = g_citizen_count + 1;
		int seq;
		one = 1;
		*(unsigned short*) slot = (unsigned short) slot_index;
		g_citizen_count = live;
		*(int*) (slot + 0x170) = (int) dynamic;
		*(int*) (slot + 0x16c) = (int) dynamic;
		seq = g_next_object_id;
		*(char*) (slot + 2) = 0;
		*(int*) (slot + 4) = seq;
		g_next_object_id = seq + 1;
	}

	*(int*) (slot + 0x1f0) = 0;
	*(int*) (slot + 0x210) = -1;
	*(char*) (slot + 0x215) = 0;
	*(char*) (slot + 0x216) = 0;
	*(char*) (slot + 0x217) = 0;
	*(char*) (slot + 0x218) = (char) one;
	*(int*) (slot + 0x1e4) = 0x3f800000;
	/* The +8 store goes before the cmd_payload read: that read may alias the
	 * slot stores, so it stays after them (`movzx cx` at 0x1000bf6e).  The
	 * store of 0 between `kind` and its use is dead and c2 deletes it, but it
	 * is a may-alias store, so `kind` is not forwarded into the use and stays
	 * a colouring candidate.  It is coloured before the constant 1 and takes
	 * ecx, which leaves the 1 `dl` (allocator Finding 72), and the pointer
	 * load then issues right after the object-id writeback, as at 0x1000bf38.
	 * Forwarded, the pointer load is a scratch pick: the 1 takes `cl` and
	 * every later scratch register rotates by one. */
	*(char*) (slot + 8) = 0x64;
	kind = *(unsigned char*) (cmd_payload + 0x10);
	*(unsigned short*) (slot + 0xa) = 0;
	*(unsigned short*) (slot + 0xa) = kind;
	*(char*) (slot + 0x164) = 0x52;
	*(char*) (slot + 0x166) = 0;
	*(char*) (slot + 0x165) = 0;
	*(char*) (slot + 0x1f4) = 0;
	*(int*) (slot + 0x190) = 4;
	*(int*) (slot + 0x194) = 0;
	*(char*) (slot + 0xd) = (char) one;
	*(int*) (slot + 0x18c) = -1;
	*(int*) (slot + 0x20c) = -1;
	*(unsigned short*) (slot + 0x50) = 0x7fff;

	/* A `for` gives the reference's bottom-tested loop at 0x1000bfb5. */
	for (i = 0; i < 5; i++)
		*(char*) (slot + 0x80 + i) = (char) (gm_RandomMod(0x40) + 0x54);
	*(char*) (slot + 9) = 0;

	*(int*) (slot + 0x1c) = 0x447a0000;
	{
		/* The multiply is in the initializer and the slot+0x20 store follows
		 * it, matching the reference's `fmul [0x100256c8]` at 0x1000bfdf
		 * ahead of `mov [esi+0x20],0x41400000` at 0x1000bfe5.  Leaving the
		 * multiply in the store expression below lets msvc6 schedule the
		 * constant store first. */
		float fv = gm_RandomQuadratic() * 7.0f;
		*(int*) (slot + 0x20) = 0x41400000;
		*(float*) (slot + 0x14) =
			(fv + 30.0f) - 2.0f;
	}

	{
		float f_tmp = *(float*) (slot + 0x1c);
		rand_value = (int) (0.2f * f_tmp);
	}
	rand_value = (unsigned short) gm_RandomMod(rand_value);

	/* Compound updates of one float local: `v +=` then `v -=` emit the
	 * reference's popping `faddp`/`fsubp` after a separate `fild`.  A
	 * single expression uses `fiadd`, or a non-popping `fadd` plus a trailing
	 * `fstp st(0)` when the conversion is a named local.  Reading slot+0x1c
	 * through the `fp` local loads the field first (`fld [esi+0x1c]; fmul
	 * [const]`); spelled inline, msvc6 loads the constant first.  The
	 * slot+0x18 copy sits between the two updates, where the reference
	 * stores it (0x1000c02b); there a float product in `v -=` gives
	 * `fsubr st,st(1)` plus a trailing `fstp st(0)`, and the `(double)`
	 * factor gives the reference's `fsubp`. */
	{
		float v = (float) rand_value;
		float* fp = (float*) (slot + 0x1c);
		v += *fp * 0.33f;
		*(float*) (slot + 0x18) = *(float*) (slot + 0x1c);
		v -= (double) (*fp * 0.1f);
		*(float*) (slot + 0x10) = v;
	}

	/* A counted loop over the 0x300 matrix rows, as the reference has it:
	 * msvc6 strength-reduces `rand_value * 0x300` into edi and keeps
	 * rand_value in its stack slot, giving the reference's lea chains and
	 * registers.  A hand-written 0x300-stride pointer counter swapped the edi
	 * and ebp roles. */
	for (rand_value = 0; rand_value < 0x300; rand_value++) {
		*(char*) (g_relationship_matrix_primary + rand_value * 0x300 + *(unsigned short*) slot) =
		    (char) (gm_RandomMod(0x40) - 0x20);
		*(char*) (g_relationship_matrix_secondary + rand_value * 0x300 + *(unsigned short*) slot) = 0;
		*(char*) (g_relationship_matrix_primary + *(unsigned short*) slot * 0x300 + rand_value) =
		    (char) (gm_RandomMod(0x40) - 0x20);
		*(char*) (g_relationship_matrix_secondary + *(unsigned short*) slot * 0x300 + rand_value) = 0;
	}

	if (*(int*) ((char*) dynamic + 0x65) == 0) {
		*(int*) ((char*) dynamic + 0x65) = (int) m_AllocTracked(0x3c, "ahm_AllocAhmInfo");
	}

	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	memset((void*) alch_data_ptr, 0, 0x3c);

	/* The slot-id store goes ahead of the alch_props byte read, matching the
	 * reference's `mov [ecx],edx` at 0x1000c0eb before `mov al,[edi+0xf]`.
	 * Reversing the two puts the whole alch-data block one slot out of phase.
	 * The reload of dynamic+0x65 between the store and the float is what the
	 * reference does; dropping it costs 233 bytes. */
	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(int*) alch_data_ptr = *(int*) (slot + 4);
	alch_props = (unsigned char) *(char*) (cmd_payload + 0xf);
	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(float*) (alch_data_ptr + 4) =
		((float) alch_props * 0.003968254197388887f + 1.0f) * 0.5f;

	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(char*) (alch_data_ptr + 8) = *(char*) (cmd_payload + 0xc);
	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(char*) (alch_data_ptr + 9) = *(char*) (cmd_payload + 0xd);
	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(char*) (alch_data_ptr + 0xa) = *(char*) (cmd_payload + 0xe);
	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(char*) (alch_data_ptr + 0xb) = *(char*) (cmd_payload + 0xf);
	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(int*) (alch_data_ptr + 0xc) = *(int*) (cmd_payload + 0x14);

	query_result = (int*) gm_ff_Objekt(
		*(int*) ((char*) dynamic + 0x5d),
		2,
		6,
		0,
		0xff
	);
	found_record = (int) query_result;

	if (found_record != 0) {
		while (*(int*) (found_record + 0x14) != 0) {
			item_type = *(short*) *(int*) (found_record + 0x14);
			gm_RemoveObjectByType((int*) (found_record + 0x14), (int) (unsigned short) item_type);
		}
	}

	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	*(int*) (alch_data_ptr + 0x10) = *(int*) (cmd_payload + 0x20);

	if (found_record != 0) {
		gm_AddObjekt(
			*(int*) (found_record + 2),
			*(int*) (cmd_payload + 0x14),
			2
		);
	}

	gm_ObjectsAvailble((int) (unsigned char) g_current_season);
	*(int*) (slot + 0x1cc) = *(int*) (slot + 0x1cc) | 4;

	return *(unsigned short*) slot;
}


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

/* Clears a slot if it matches a target value. Used during
 * alchemy cleanup to remove specific entity references. */


int __cdecl ahm_ClampFloatValue(float* arg1, float* arg2)
{
	float sum;
	float clamp;

	sum = arg1[4] + arg2[1];
	if (sum > g_const_0_0 && sum < 1.0f) {
		arg2[1] = sum;
		return 1;
	}
	if (sum <= g_const_0_0) {
		clamp = g_const_0_0;
	} else {
		clamp = 1.0f;
	}
	arg2[1] = clamp;
	return 1;
}

/* Fires (activates) an alchemy entity and cleans up the
 * processing state. Finalizes the recipe output and resets
 * the alchemist for the next batch. */


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
		*(int*) (arg2 + 0x65) = (int) m_AllocTracked(0x3c, "ahm_AllocAhmInfo");
	memcpy((void*) *(int*) (arg2 + 0x65), buf, 0x3c);
	return 1;
}


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
		if (*(unsigned char*) ((unsigned int) g_alchemy_random_table + 0xf6 + idx * 244) == 0)
			goto found;
		counter--;
		idx = (idx + 1) & 0x1f;
	}
	return 0;
found:
	off = idx * 244;
	table_cursor = (float*) ((unsigned int) g_alchemy_random_table + 0x34 + off);
	n = 0xe;
	do {
		/* volatile pins the store right after the multiply; without it
		 * MSVC6 sinks it past the pointer bump to `fstp [eax-0xc]`. */
		*(volatile float*) table_cursor = table_cursor[-1] * g_const_0_001;
		table_cursor += 3;
		n--;
	} while (n != 0);
	*(unsigned char*) ((unsigned int) g_alchemy_random_table + 0xf6 + off) = 1;
	return (char*) ((unsigned int) g_alchemy_random_table + 4 + off);
}


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


int* __cdecl ahm_QueryEntityBuildingType(int arg1)
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


/* RELOC 752/752.  The switch-byte/index register pair (dl/ecx in the target,
 * cl/edx before this fix) is decided by which case-0x16 statement reads
 * cmd_payload first: assigning `cursor` from the `*cmd_payload == 0x16`
 * test before reading `cmd_payload[0x14]` into `count` pins the byte in dl.
 * The reverse order scores 742/752, and hoisting `total_size = 0x15` above
 * both scores 508/752. */
int ahm_GetCommandPayloadSize(unsigned char* cmd_payload)

{
	int count;
	unsigned char* cursor;
	int total_size;
	int entry_size;

	// switch table (103 cases) at 0x1000c864
	switch ((unsigned char) *cmd_payload) {
	case 0x3:
	case 0x13:
	case 0x1a:
	case 0x25:
	case 0x2b:
	case 0x34:
	case 0x36:
	case 0x38:
	case 0x47:
	case 0x52:
	case 0x54:
	case 0x5b:
	case 0x5d:
		return 0x1c;
	case 0x4:
		return 0x11;
	case 0x8:
	case 0x1c:
	case 0x28:
	case 0x31:
	case 0x3b:
	case 0x42:
	case 0x43:
	case 0x4a:
	case 0x4d:
	case 0x57:
	case 0x58:
	case 0x69:
		return 0x14;
	case 0xa:
		return 0x50;
	case 0xb:
		return 0x2a;
	case 0xc:
		return 0x49;
	case 0xf:
	case 0x2c:
		return 0x21;
	case 0x11:
	case 0x3d:
		return 0x27;
	case 0x12:
	case 0x1e:
		return 0x1e;
	case 0x14:
		return 0x16;
	case 0x15:
		return 0x39;
	case 0x16:
	case 0x17:
		cursor = (*cmd_payload == 0x16) ? (cmd_payload + 0x15) : (cmd_payload + 0x15);
		count = cmd_payload[0x14];
		total_size = 0x15;
		while (count > 0) {
			entry_size = cursor[1] * *cursor + 4;
			total_size = total_size + entry_size;
			cursor = cursor + entry_size;
			count = count - 1;
		}
		return total_size;
	case 0x18:
		return cmd_payload[0x14] * 5 + 0x15;
	case 0x19:
	case 0x53:
		return 0x24;
	case 0x1b:
	case 0x64:
		return 0x28;
	case 0x1d:
		return 0x5f;
	case 0x20:
		return ((cmd_payload[0x10] != 0xe ? -1 : 0) & 0x7c) + 0x11;
	case 0x22:
		return 0x3d;
	case 0xd:
	case 0x21:
	case 0x23:
	case 0x24:
	case 0x26:
	case 0x27:
	case 0x29:
	case 0x2a:
	case 0x33:
	case 0x39:
	case 0x3a:
	case 0x5a:
	case 0x66:
	case 0x68:
		return 0x18;
	case 0x2d:
	case 0x45:
		return 0x1f;
	case 0x2e:
	case 0x3c:
		return 0x20;
	case 0x2f:
	case 0x30:
		return 0x3c;
	case 0x35:
		return 0x5d;
	case 0x37:
		return 0x45;
	case 0x32:
	case 0x3e:
	case 0x4f:
	case 0x5e:
	case 0x63:
		return 0x34;
	case 0x40:
	case 0x60:
		return 0x2f;
	case 0x41:
		return 0x4a;
	case 0x44:
		return 0x17;
	case 0x46:
		return 0x19;
	case 0x48:
		return 0x15;
	case 0x49:
		return 0x36;
	case 0x4b:
	case 0x67:
		return 0x90;
	case 0x4c:
		return 0x35;
	case 0x4e:
		return 0x40;
	case 0x50:
	case 0x51:
		return 0x44;
	case 0x55:
		return 0x61;
	case 0x56:
		return 0x38;
	case 0x5c:
		return 0x1a;
	case 0x61:
	case 0x62:
		return 0x29;
	case 0x5f:
		return 0x80;
	default:
		return 0x91;
	}
	return total_size;
}




#pragma pack(push, 1)
// SIZE 0x99
typedef struct ChainNode {
	unsigned char cmd;      /* +0x00 */
	char pad[0x94];
	struct ChainNode* next; /* +0x95 (unaligned) */
} ChainNode;
#pragma pack(pop)

int __cdecl ahm_ProcessEntityChain(char* cmd_payload)
{
	ChainNode* node;
	ChainNode* n;
	int ok;

	ok = 1;
	node = ((ChainNode*) cmd_payload)->next;
	while (ok != 0) {
		if (node->cmd == 6) {
			goto check_result;
		}
		if (g_chain_handler_table[node->cmd](node) != 0) {
			ok = 0;
		}
		node = node->next;
	}
	goto error;
check_result:
	if (ok == 0) {
		goto error;
	}
	/* success: mark head and chain terminator as processed */
	n = (ChainNode*) cmd_payload;
	n->cmd = 1;
	while (n->cmd != 6) {
		n = n->next;
	}
	n->cmd = 1;
	return 1;

error:
	/* failure: mark every node in the chain */
	n = (ChainNode*) cmd_payload;
	while (n->cmd != 6) {
		n->cmd = 2;
		n = n->next;
	}
	n->cmd = 2;
	return 1;
}



