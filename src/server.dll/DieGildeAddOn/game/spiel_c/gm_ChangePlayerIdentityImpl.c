#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <string.h>
typedef int(__cdecl* ALLOCFN)(int, int, int);

#pragma intrinsic(memcpy, memset)

// SIZE 0x2c
#pragma pack(push, 1)
// SIZE 0x43
typedef struct {
	short active;
	int id;
	char pad[0x3d];
} Record;
#pragma pack(pop)

extern char* g_entity_table; /* 0x101de450 */
extern unsigned char* g_entity_ptr;
extern char* g_item_def_table;
// STUB: SERVER 0x10018530
// gm_ChangePlayerIdentityImpl

int __cdecl gm_ChangePlayerIdentityImpl(int player_id, int new_identity)
{
	char* record_b;
	unsigned short index_b;
	unsigned short index_a;
	int chain_value;
	char* record_a;
	int stat_opposite;
	int inner_loop;
	int copy_count;
	int offset_a;
	int saved_id;
	int* ref_scan;
	int* outer_scan;
	char* pNode;
	int scan_count;
	char buf1[0x21c];
	char buf2[0x21c];

	record_a = (char*) gm_LookupEntityRecordById(player_id);
	if (record_a == 0) {
		return -1;
	}

	offset_a = 0;
	copy_count = 0x100;
	do {
		inner_loop = offset_a + (int) g_entity_ptr;
		if ((*(char*) (offset_a + (int) g_entity_ptr) != '\0') &&
			(stat_opposite = gm_GetBuildingTypeCategory((unsigned char) *(char*) (offset_a + (int) g_entity_ptr)),
			 stat_opposite == 2) &&
			(*(unsigned short*) (inner_loop + 0x27) == *(unsigned short*) record_a)) {
			gm_AssignBuildingOwner(
				(char*) inner_loop,
				**(unsigned short**) 0x1003546c,
				**(unsigned short**) 0x1003546c
			);
		}
		offset_a = offset_a + 0xa9;
		copy_count = copy_count - 1;
	} while (copy_count != 0);

	index_a = *(unsigned short*) record_a;
	chain_value = gm_WalkEntityChain(index_a);

	record_b = (char*) gm_LookupEntityRecordById(new_identity);
	if (record_b == 0) {
		return -2;
	}

	index_b = *(unsigned short*) record_b;
	if (*(unsigned short*) (record_a + 0x50) != *(unsigned short*) (record_b + 0x50)) {
		*(unsigned short*) (record_b + 0x50) = *(unsigned short*) (record_a + 0x50);
	}

	amt_ClearEntityLinks((short*) record_a);

	{
		unsigned char saved_byte2 = *(unsigned char*) (record_a + 2);
		unsigned short saved_word0 = *(unsigned short*) record_a;
		int* pDst;
		int* pSrc;

		memcpy(buf1, record_b, 0x21c);

		*(int*) (buf1 + 4) = *(int*) (record_a + 4);
		*(unsigned char*) (buf1 + 2) = saved_byte2;
		*(unsigned short*) buf1 = saved_word0;
	}

	*(unsigned char*) (buf1 + 0xd) = *(unsigned char*) (record_a + 0xd);
	*(int*) (buf1 + 0x170) = *(int*) (record_a + 0x170);

	copy_count = gm_MapEntityStatRange((unsigned char) *(unsigned char*) (record_b + 0x164));
	if (copy_count != 0) {
		offset_a = (int) gm_GetEntityTableEntry(record_a);
		if (offset_a != 0) {
			inner_loop = gm_CheckStatLevel(*(unsigned short*) record_a, copy_count);
			if (inner_loop != 0) {
				stat_opposite = gm_GetOppositeStatIndex((unsigned char) *(unsigned char*) (record_b + 0x164));
				inner_loop = gm_GetOppositeStatIndex(inner_loop);
				if (inner_loop < stat_opposite) {
					*(unsigned char*) (offset_a + copy_count + 0x74) = *(unsigned char*) (record_b + 0x164);
				}
				else {
					*(unsigned char*) (buf1 + 0x164) = *(unsigned char*) (record_a + 0x164);
				}
			}
		}
	}
	else {
		*(unsigned char*) (buf1 + 0x164) = *(unsigned char*) (record_a + 0x164);
	}

	saved_id = *(int*) (record_b + 4);
	memcpy(buf2, record_a, 0x21c);
	*(int*) (buf2 + 4) = saved_id;
	*(unsigned short*) buf2 = *(unsigned short*) record_b;
	*(unsigned char*) (buf2 + 2) = 9;

	offset_a = (int) index_a * 0x21c;
	memcpy((char*) (offset_a + 0x100358a0), buf1, 0x21c);

	copy_count = (int) index_b * 0x21c;
	memcpy((char*) (copy_count + 0x100358a0), buf2, 0x21c);

	for (inner_loop = *(int*) (offset_a + 0x10035a18); inner_loop != 0; inner_loop = *(int*) (inner_loop + 0x3f)) {
		*(int*) (inner_loop + 6) = *(int*) (offset_a + 0x100358a4);
	}

	for (inner_loop = *(int*) (copy_count + 0x10035a18); inner_loop != 0; inner_loop = *(int*) (inner_loop + 0x3f)) {
		*(int*) (inner_loop + 6) = *(int*) (copy_count + 0x100358a4);
	}

	outer_scan = (int*) 0x100358fc;
	scan_count = 0x300;
	do {
		copy_count = 8;
		ref_scan = outer_scan;
		do {
			if (*ref_scan == player_id) {
				*ref_scan = new_identity;
			}
			else if (*ref_scan == new_identity) {
				*ref_scan = player_id;
			}
			ref_scan = ref_scan + 1;
			copy_count = copy_count - 1;
		} while (copy_count != 0);
		outer_scan = (int*) ((char*) outer_scan + 0x21c);
		scan_count = scan_count - 1;
	} while (scan_count != 0);

	for (pNode = *(char**) (buf2 + 0x178); pNode != 0; pNode = *(char**) (pNode + 0x3f)) {
		index_b = *(unsigned short*) pNode;
		if (index_b != 0 && *(g_item_def_table + (int) index_b * 0x41) == '\t') {
			gm_AddOrAccumulateObject(*(int*) (buf1 + 4), (int) index_b, *(int*) (pNode + 0xe));
		}
	}

	*(int*) (offset_a + 0x10035a48) = chain_value;
	*(int*) (offset_a + 0x10035a34) = 4;
	*(int*) (offset_a + 0x10035a68) = 0;
	gm_DeallocEntity(*(unsigned short*) buf2, 0);

	return (int) index_a;
}

/* Creates a new entity from parent entities. Generates
 * inherited stats by blending parent attributes with random
 * variation. Core genetic system for citizen creation. */
