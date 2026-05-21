#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <string.h>
int __cdecl __ftol(void);

typedef int(__cdecl* dispatch_fn)(unsigned char*);

extern char* g_table;
int __cdecl gm_ResolveEntityById(void** dynamic, int zero1, int zero2, int id);
int __cdecl gm_RandomMod(int range);
float __cdecl gm_RandomFloat01(void);
void __cdecl gm_AddOrAccumulateObject(int p1, int p2, int p3);
int __cdecl gm_RefreshMarketAvailability(int season);
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_DeallocEntity(unsigned int index, int param);
void* __cdecl gm_NextEntityQueryMatch(void);
extern float fColorScale;
extern int g_next_object_id;
extern unsigned char g_current_season;
extern float g_float_const_cc;
extern float g_float_const_a0;
extern char s__ahm_AllocAhmInfo_1002a0f7[];
extern double dScaleFactor;
extern int g_alchemy_entity_table[];
int* __cdecl ahm_LookupEntityInTable(int);
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

/* Resets an alchemy entity to its initial state by zeroing
 * out its operational fields via memset. */

// STUB: SERVER 0x1000bdf0
// ahm_ExAllocAlchemist

unsigned short __cdecl ahm_ExAllocAlchemist(int cmd_payload)
{
	void* dynamic;
	char* building_record;
	int building_type;
	int slot_index;
	char* slot;
	int rand_value;
	int rand_iter;
	int* query_result;
	int found_record;
	short item_type;
	int building_id;
	int alch_data_ptr;
	int alch_props;
	int i;

	dynamic = 0;
	building_id = *(int*) (cmd_payload + 8);
	gm_ResolveEntityById(&dynamic, 0, 0, building_id);
	building_record = (char*) dynamic;
	if (building_record == 0) {
		LogMessageInternal((char*) 0x1002a10c, 0x449, (char*) 0x1002a19c, 1);
		return 0xffff;
	}

	building_type = (unsigned char) *building_record;
	if (*((char*) (g_entity_type_table + building_type + building_type * 0x24c)) != 0x1e) {
		LogMessageInternal((char*) 0x1002a10c, 0x451, (char*) 0x1002a168, 1);
		return 0xffff;
	}

	slot_index = 0;
	for (i = 0; i < 0x300; i = i + 1) {
		if (*(unsigned short*) (0x100358a0 + i * 0x21c) == 0xffff) {
			slot_index = i;
			goto found_slot;
		}
	}

	slot_index = 0;
	for (i = 0; i < 0x300; i = i + 1) {
		if (*(char*) (0x100358a2 + i * 0x21c) == 0xf) {
			slot_index = i;
			goto found_slot;
		}
	}

	LogMessageInternal((char*) 0x1002a10c, 0x45d, (char*) 0x1002a140, 1);
	return 0xffff;

found_slot:
	if (*(char*) (0x100358a2 + slot_index * 0x21c) == 0xf) {
		g_citizen_count = g_citizen_count - 1;
	}

	slot = (char*) (0x100358a0 + slot_index * 0x21c);
	memset(slot, 0, 0x21c);
	*(unsigned short*) slot = 0xffff;
	*(int*) (slot + 4) = -1;

	memset(slot + 0x5c, 0, 0x20);

	g_citizen_count = g_citizen_count + 1;
	*(unsigned short*) slot = (unsigned short) slot_index;
	*(int*) (slot + 0x170) = cmd_payload;
	*(int*) (slot + 0x16c) = cmd_payload;
	*(int*) (slot + 4) = g_next_object_id;
	*(char*) (slot + 2) = 0;
	g_next_object_id = g_next_object_id + 1;

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

	for (i = 0; i < 5; i = i + 1) {
		*(char*) (slot + i + 0x80) = (char) (gm_RandomMod(0x40) + 0x54);
	}
	*(char*) (slot + 9) = 0;

	*(int*) (slot + 0x1c) = 0x447a0000;
	{
		float fv = gm_RandomFloat01();
		*(float*) (slot + 0x14) = (fv * *(float*) 0x100256c8 + *(float*) 0x100256c4) * *(float*) 0x100256b0;
		(void) fv;
	}
	*(int*) (slot + 0x20) = 0x41400000;

	{
		float base = *(float*) (slot + 0x1c) * *(float*) 0x100256bc;
		rand_value = __ftol();
		(void) base;
	}
	rand_value = gm_RandomMod((unsigned short) rand_value);

	{
		float v = (float) rand_value;
		*(float*) (slot + 0x18) = *(float*) (slot + 0x1c);
		*(float*) (slot + 0x10) = v + *(float*) (slot + 0x1c) * *(float*) 0x100256b8 -
			*(float*) (slot + 0x1c) * *(float*) 0x100256b4;
	}

	rand_iter = 0;
	for (i = 0; i < 0x300; i = i + 1) {
		unsigned short btype;
		int rnd1;
		int rnd2;
		int base_off;

		btype = *(unsigned short*) slot;
		rnd1 = gm_RandomMod(0x40) - 0x20;
		base_off = btype + rand_iter;
		*(char*) (base_off + 0x100a9820) = (char) rnd1;
		*(char*) (base_off + 0x1014d8e0) = 0;

		btype = *(unsigned short*) slot;
		rnd2 = gm_RandomMod(0x40) - 0x20;
		base_off = btype * 0x300 + rand_value;
		*(char*) (base_off + 0x100a9820) = (char) rnd2;
		*(char*) (base_off + 0x1014d8e0) = 0;
		rand_value = rand_value + 1;
		rand_iter = rand_iter + 0x300;
	}

	if (*(int*) (cmd_payload + 0x65) == 0) {
		*(int*) (cmd_payload + 0x65) = (int) m_AllocTracked(0x3c, (char*) 0x1002a0f8);
	}

	alch_data_ptr = *(int*) (cmd_payload + 0x65);
	memset((void*) alch_data_ptr, -1, 0x3c);

	alch_data_ptr = *(int*) (cmd_payload + 0x65);
	*(int*) alch_data_ptr = *(int*) (slot + 4);

	alch_props = (unsigned char) *(char*) (cmd_payload + 0xf);
	alch_data_ptr = *(int*) (cmd_payload + 0x65);
	*(float*) (alch_data_ptr + 4) =
		((float) alch_props * *(float*) 0x100256ac + *(float*) 0x100256a0) * *(float*) 0x100256b0;

	alch_data_ptr = *(int*) (cmd_payload + 0x65);
	*(char*) (alch_data_ptr + 8) = *(char*) (cmd_payload + 0xc);
	alch_data_ptr = *(int*) (cmd_payload + 0x65);
	*(char*) (alch_data_ptr + 9) = *(char*) (cmd_payload + 0xd);
	alch_data_ptr = *(int*) (cmd_payload + 0x65);
	*(char*) (alch_data_ptr + 0xa) = *(char*) (cmd_payload + 0xe);
	alch_data_ptr = *(int*) (cmd_payload + 0x65);
	*(char*) (alch_data_ptr + 0xb) = *(char*) (cmd_payload + 0xf);
	alch_data_ptr = *(int*) (cmd_payload + 0x65);
	*(int*) (alch_data_ptr + 0xc) = *(int*) (cmd_payload + 0x14);

	query_result = (int*) gm_StartEntityQuery(
		(int) (unsigned short) *(short*) (slot + 0x5d),
		1,
		2,
		6
	);
	found_record = (int) query_result;

	if (found_record != 0) {
		while (*(int*) (found_record + 0x14) != 0) {
			item_type = *(short*) *(int*) (found_record + 0x14);
			gm_RemoveObjectByType((int*) (found_record + 0x14), (int) (unsigned short) item_type);
		}
	}

	alch_data_ptr = *(int*) (cmd_payload + 0x65);
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

	return (unsigned short) *(short*) slot;
}
