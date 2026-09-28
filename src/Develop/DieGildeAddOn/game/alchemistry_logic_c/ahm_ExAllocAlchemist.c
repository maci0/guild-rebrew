// FUNCTION: GOLDTL 0x4ee290
// SIZE: 1088
// FUNCTION: SERVER 0x1000bdf0

#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"
#include "../entity.h"

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
extern char s_ahm_AllocAhmInfo[];

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
		LogMessageInternal((char*) 0x1002a10c, 0x449, (char*) 0x1002a19c, 1);
		return 0xffff;
	}

	building_type = (unsigned char) *(char*) dynamic;
	if (*((char*) (g_entity_type_table + building_type + building_type * 0x24c)) != 0x1e) {
		LogMessageInternal((char*) 0x1002a10c, 0x451, (char*) 0x1002a168, 1);
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
			LogMessageInternal((char*) 0x1002a10c, 0x45d, (char*) 0x1002a140, 1);
			ret_false:
			return 0xffff;
		}
	}

	if (*(char*) (g_slot_table + slot_index * 0x21c + 2) == 0xf) {
		g_citizen_count = g_citizen_count - 1;
	}

	memset((void*) (g_slot_table + slot_index * 0x21c), 0, 0x21c);
	/* The 0xffff store goes through `slot` and the +4 store through the
	 * symbol: c2 cannot prove the two disjoint, so the +4 store depends on
	 * this one and lifts its scheduling priority just below the `or eax,-1`,
	 * giving the reference's `or eax,-1; mov word ptr [esi],0xffff` at
	 * 0x1000bee6.  `volatile` makes the store a barrier that
	 * holds the `or` behind it.  The +0x5c fill is a loop, not memset: the
	 * destination stays its own register, `lea edx,[edx+..]; mov edi,edx`
	 * as at 0x1000bef4 (shapes 197). */
	slot = (char*) (g_slot_table + slot_index * 0x21c);
	minus_one = -1;
	*(unsigned short*) slot = 0xffff;
	*(int*) (g_slot_table + slot_index * 0x21c + 4) = minus_one;
	for (i = 0; i < 8; i++)
		((int*) (g_slot_table + slot_index * 0x21c + 0x5c))[i] = minus_one;

	/* Both counters are read into a local ahead of their stores and written
	 * back after, which emits the reference's ecx traffic instead of a
	 * load-inc-store pair.  The citizen count is read through its literal
	 * address: c2 must assume that read may alias `slot`, so the 0xffff
	 * store above stays live although the slot-index store now goes through
	 * `slot`.  Through `slot` that store has no may-alias edges to the later
	 * slot stores, so its priority drops below the `mov dl,1`, as at
	 * 0x1000bf09.  Through the symbol it outranks the `1` and issues first. */
	{
		int live = *(int*) 0x10035434 + 1;
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
		float fv = gm_RandomQuadratic() * *(float*) 0x100256c8;
		*(int*) (slot + 0x20) = 0x41400000;
		*(float*) (slot + 0x14) =
			(fv + *(float*) 0x100256c4) - *(float*) 0x100256c0;
	}

	{
		float f_tmp = *(float*) (slot + 0x1c);
		rand_value = (int) (*(float*) 0x100256bc * f_tmp);
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
		v += *fp * *(float*) 0x100256b8;
		*(float*) (slot + 0x18) = *(float*) (slot + 0x1c);
		v -= (double) *fp * *(float*) 0x100256b4;
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
		*(int*) ((char*) dynamic + 0x65) = (int) m_AllocTracked(0x3c, s_ahm_AllocAhmInfo);
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
		((float) alch_props * *(float*) 0x100256ac + *(float*) 0x100256a0) * *(float*) 0x100256b0;

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

