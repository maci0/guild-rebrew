// FUNCTION: SERVER 0x1000bdf0
#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <string.h>
int __cdecl _ftol(void);

typedef int(__cdecl* dispatch_fn)(unsigned char*);

int __cdecl gm_ResolveEntityById(void** dynamic, int zero1, int zero2, int id);
int __cdecl gm_RandomMod(int range);
float __cdecl gm_RandomQuadratic(void);
void __cdecl gm_AddOrAccumulateObject(int p1, int p2, int p3);
int __cdecl gm_RefreshMarketAvailability(int season);
extern float fColorScale;
extern int g_next_object_id;
extern unsigned char g_current_season;
extern double dScaleFactor;
extern dispatch_fn PTR_LAB_1002c5a0[];

extern int g_entity_type_table;
extern int g_citizen_count;
extern unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
extern void __cdecl gm_RemoveObjectByType(int*, int);
void* __cdecl m_AllocTracked(unsigned int size, const char* source);

// SIZE 0x8
typedef struct {
	int key;
	int val;
} PAIR;

// SIZE 0x14
// SIZE 0x3c
typedef struct {
	char hdr[0xc];
	PAIR entries[6];
} TGT;

/* Allocates a new alchemy entity: resolves the parent building record,
 * finds a free slot in the static entity table (0x100358a0, stride 0x21c),
 * initializes the slot from the command payload, fills the alchemy grid
 * (0x100a9820 / 0x1014d8e0) with random values, and allocates/refreshes the
 * building's alchemy data block (record->0x65). Returns the slot index or
 * 0xffff on failure. */

unsigned int __cdecl ahm_ExAllocAlchemist(int cmd_payload)
{
	void* dynamic;
	int building_type;
	char* slot;
	int slot_index;
	int rand_value;
	int rand_iter;
	int* query_result;
	int found_record;
	short item_type;
	int building_id;
	int alch_data_ptr;
	int alch_props;
	int i;

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
		if (*(unsigned short*) (0x100358a0 + slot_index * 0x21c) == 0xffff)
			break;
	}
	if (slot_index == 0x300) {
		for (slot_index = 0; slot_index < 0x300; slot_index++) {
			if (*(char*) (0x100358a2 + slot_index * 0x21c) == 0xf)
				break;
		}
		if (slot_index == 0x300) {
			LogMessageInternal((char*) 0x1002a10c, 0x45d, (char*) 0x1002a140, 1);
			ret_false:
			return 0xffff;
		}
	}

	if (*(char*) (0x100358a2 + slot_index * 0x21c) == 0xf) {
		g_citizen_count = g_citizen_count - 1;
	}

	memset((void*) (0x100358a0 + slot_index * 0x21c), 0, 0x21c);
	/* volatile: keeps both stores alive past the slot[0] = slot_index
	 * write below (the reference keeps them: slot[0]=0xffff, then
	 * slot[4]=-1 with the -1 in eax reused by the second memset). The
	 * reference order is slot[0]=0xffff before slot[4]=-1; both must be
	 * volatile or MSVC6 dead-store-eliminates slot[0]=0xffff. */
	*(volatile unsigned short*) (0x100358a0 + slot_index * 0x21c) = 0xffff;
	*(volatile int*) (0x100358a4 + slot_index * 0x21c) = -1;
	memset((void*) (0x100358fc + slot_index * 0x21c), -1, 0x20);

	slot = (char*) (0x100358a0 + slot_index * 0x21c);

	g_citizen_count = g_citizen_count + 1;
	*(unsigned short*) (0x100358a0 + slot_index * 0x21c) = (unsigned short) slot_index;
	*(char*) (slot + 2) = 0;
	*(int*) (slot + 4) = g_next_object_id;
	g_next_object_id = g_next_object_id + 1;
	*(int*) (slot + 0x170) = (int) dynamic;
	*(int*) (slot + 0x16c) = (int) dynamic;

	*(int*) (slot + 0x1f0) = 0;
	*(int*) (slot + 0x210) = -1;
	*(char*) (slot + 0x215) = 0;
	*(char*) (slot + 0x216) = 0;
	*(char*) (slot + 0x217) = 0;
	*(char*) (slot + 0x218) = 1;
	*(int*) (slot + 0x1e4) = 0x3f800000;
	*(char*) (slot + 8) = 0x64;
	*(unsigned short*) (slot + 0xa) = (unsigned short) (unsigned char) *(char*) (cmd_payload + 0x10);
	*(char*) (slot + 0x164) = 0x52;
	*(char*) (slot + 0x166) = 0;
	*(char*) (slot + 0x165) = 0;
	*(char*) (slot + 0x1f4) = 0;
	*(int*) (slot + 0x190) = 4;
	*(int*) (slot + 0x194) = 0;
	*(char*) (slot + 0xd) = 1;
	*(int*) (slot + 0x18c) = -1;
	*(int*) (slot + 0x20c) = -1;
	*(unsigned short*) (slot + 0x50) = 0x7fff;

	/* While-form of the 5-iteration fill: the top-tested loop shape
	 * (rather than a for or do-while) is what keeps the reference's
	 * register allocation downstream (the reference's fill is
	 * bottom-tested, but a do-while here cascades: 998 obj / 285 match). */
	i = 0;
	while (1) {
		if (!(i < 5)) break;
		*(char*) (slot + i + 0x80) = (char) (gm_RandomMod(0x40) + 0x54);
		i += 1;
	}
	*(char*) (slot + 9) = 0;

	*(int*) (slot + 0x1c) = 0x447a0000;
	{
		float fv = gm_RandomQuadratic();
		*(float*) (slot + 0x14) =
			(fv * *(float*) 0x100256c8 + *(float*) 0x100256c4) - *(float*) 0x100256c0;
		(void) fv;
	}
	*(int*) (slot + 0x20) = 0x41400000;

	{
		float f_tmp = *(float*) (slot + 0x1c);
		rand_value = (int) (*(float*) 0x100256bc * f_tmp);
	}
	rand_value = (unsigned short) gm_RandomMod(rand_value);

	{
		float v = (float) rand_value;
		*(float*) (slot + 0x18) = *(float*) (slot + 0x1c);
		*(float*) (slot + 0x10) = v + *(float*) (slot + 0x1c) * *(float*) 0x100256b8 -
			*(float*) (slot + 0x1c) * *(float*) 0x100256b4;
	}

	/* GRA fixed point: the base_off formulation strength-reduces this
	 * loop to advancing pointers + a down-counter (989 obj), which is
	 * what keeps the ebx=0 zero-register prologue (push ebx / cmp eax,ebx)
	 * intact. Inlining the grid addresses instead reproduces the
	 * reference loop shape (cmp edi,0x90000/jl bottom test, per-iter lea
	 * chains) but costs the prologue (push 0 / dynamic in ebx; 1000 obj,
	 * 364 match). The two are mutually exclusive under msvc6 /O2; 989/417
	 * is the best reachable state (see blocker note). */
	rand_iter = 0;
	i = 0;
	do {
		unsigned short btype;
		int rnd1;
		int rnd2;
		int base_off;

		btype = *(unsigned short*) (0x100358a0 + slot_index * 0x21c);
		base_off = btype + rand_iter;
		rnd1 = gm_RandomMod(0x40) - 0x20;
		*(char*) (base_off + 0x100a9820) = (char) rnd1;
		*(char*) (base_off + 0x1014d8e0) = 0;

		btype = *(unsigned short*) (0x100358a0 + slot_index * 0x21c);
		base_off = btype * 0x300 + i;
		rnd2 = gm_RandomMod(0x40) - 0x20;
		*(char*) (base_off + 0x100a9820) = (char) rnd2;
		*(char*) (base_off + 0x1014d8e0) = 0;
		i = i + 1;
		rand_iter = rand_iter + 0x300;
	} while (rand_iter < 0x90000);

	if (*(int*) ((char*) dynamic + 0x65) == 0) {
		*(int*) ((char*) dynamic + 0x65) = (int) m_AllocTracked(0x3c, (char*) 0x1002a0f8);
	}

	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	memset((void*) alch_data_ptr, 0, 0x3c);

	/* alch_props read hoisted ahead of the slot-id store below: MSVC6's
	 * allocation matches the reference only in this statement order. */
	alch_data_ptr = *(int*) ((char*) dynamic + 0x65);
	alch_props = (unsigned char) *(char*) (cmd_payload + 0xf);

	*(int*) alch_data_ptr = *(int*) (slot + 4);
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

	query_result = (int*) gm_StartEntityQuery(
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
		gm_AddOrAccumulateObject(
			*(int*) (found_record + 2),
			*(int*) (cmd_payload + 0x14),
			2
		);
	}

	gm_RefreshMarketAvailability((int) (unsigned char) g_current_season);
	*(int*) (slot + 0x1cc) = *(int*) (slot + 0x1cc) | 4;

	return *(unsigned short*) slot;
}