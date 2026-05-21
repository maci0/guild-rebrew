#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <string.h>

#pragma intrinsic(memset, strcpy)

int __cdecl gv_CheckSlotActive(char*, int);
extern int g_entity_type_table;
extern int g_slot_count_cat0[]; /* 0x1002577c */
extern int g_slot_count_cat1[]; /* 0x1002578c */
extern int g_slot_count_cat2[]; /* 0x1002579c */
extern int g_slot_count_cat3[]; /* 0x100257ac */
int __cdecl cm_GetBuildingStatCount(unsigned char*);
char* __cdecl gv_FindSlotEntryFiltered(char*, unsigned char*, char*, int(__cdecl*)(char*, char*), int);
int __cdecl gm_RandomMod(int);
extern unsigned int __ftol(void);
extern int g_1002575c[];
extern int g_1002576c[];
extern char g_1002d444;
extern char g_1002d45c;
extern char g_1002d474;
int AllocGraveyardField(int);
void gv_Free3Fields(char*);
int __cdecl gm_ResolveEntityById(void** out_slot, void** out_person, void** out_building, int entity_id);
int __cdecl gv_GetSlotEntry(int, int, unsigned char);
int __cdecl gm_SubObjektNoKill(int, int, int);
void* __cdecl gm_AddOrAccumulateObject(int, int, int);
void __cdecl game_free(void*);
extern int g_entity_table_end;
extern char* g_slot_table;
int SpawnGraveyardEntities(unsigned char*, int);
extern char* g_action_table_base;
double __cdecl gm_RandomFloat01(void);
extern int g_next_object_id;
extern int g_citizen_count;
extern unsigned char g_current_season;
extern float DAT_10025680;
extern float DAT_100257c4;
extern float DAT_100257c8;

/* Checks if a production slot in a building is active.
 * Returns non-zero if the slot at the given index has
 * an assigned worker or active production. */

// STUB: SERVER 0x10011bf0
// gv_ExAllocGraveyardWorker

unsigned int __cdecl gv_ExAllocGraveyardWorker(int cmd_payload)
{
	unsigned short* new_entity_slot_ptr;
	unsigned short entity_slot_index;
	char rand_relationship_val;
	int entity_slot_byte_offset;
	int* matched_production_record;
	short* slot_scan_ptr;
	char* entity_type_scan_ptr;
	int* production_record_walker;
	int clear_loop_counter;
	int search_loop_idx;
	int slot_scan_idx_or_capacity;
	unsigned int* relationship_array_ptr;
	unsigned short* slot_clear_ptr;
	double random_float;
	int relationship_loop_idx;
	unsigned char* building_entity_ptr;
	int production_slot_entry_ptr;

	if (*(int*) (cmd_payload + 0x15) != 0x1b && *(int*) (cmd_payload + 0x15) != 0x1c) {
		return 0xfffffffa;
	}
	search_loop_idx = 0;
	gm_ResolveEntityById(&building_entity_ptr, 0, 0, *(unsigned int*) (cmd_payload + 8));
	if (building_entity_ptr == 0 || *(unsigned short*) (building_entity_ptr + 0x27) == 0xffff ||
		*(unsigned short*) (building_entity_ptr + 0x27) * 0x21c + (int) &g_slot_table == g_entity_table_end) {
		return 0xffffffff;
	}
	if (*(char*) (g_entity_type_table + (unsigned int) *building_entity_ptr * 0x24d) != '\x1d') {
		return 0xfffffffe;
	}
	slot_scan_idx_or_capacity = *(int*) (building_entity_ptr + 0x65);
	if (slot_scan_idx_or_capacity == 0) {
		return 0xfffffffd;
	}
	entity_slot_byte_offset = gv_CheckSlotActive((char*) slot_scan_idx_or_capacity, *(int*) (cmd_payload + 0xc));
	if (entity_slot_byte_offset == 0) {
		return 0xfffffffc;
	}
	production_slot_entry_ptr =
		gv_GetSlotEntry(slot_scan_idx_or_capacity, *(int*) (cmd_payload + 0xc), *(unsigned char*) (cmd_payload + 0x10));
	if (production_slot_entry_ptr == 0) {
		return 0xffff;
	}
	entity_slot_byte_offset = 0;
	slot_scan_idx_or_capacity = *(int*) (*(int*) (cmd_payload + 0xc) * 4 + 0x1002574c);
	if (0 < slot_scan_idx_or_capacity) {
		production_record_walker = *(int**) (production_slot_entry_ptr + 0x10);
		do {
			matched_production_record = production_record_walker;
			if (*matched_production_record == *(int*) (cmd_payload + 0x11)) {
				break;
			}
			entity_slot_byte_offset = entity_slot_byte_offset + 1;
			production_record_walker = matched_production_record + 0x11;
		} while (entity_slot_byte_offset < slot_scan_idx_or_capacity);
		if (matched_production_record != 0 && *matched_production_record == *(int*) (cmd_payload + 0x11)) {
			slot_scan_idx_or_capacity = 0;
			for (slot_scan_ptr = (short*) &g_slot_table; slot_scan_ptr < (short*) 0x1009aca0;
				slot_scan_ptr += 0x10e) {
				if (*slot_scan_ptr == -1) {
					break;
				}
				slot_scan_idx_or_capacity = slot_scan_idx_or_capacity + 1;
			}
			if (slot_scan_idx_or_capacity == 0x300) {
				slot_scan_idx_or_capacity = 0;
				for (entity_type_scan_ptr = (char*) 0x100358a2; entity_type_scan_ptr < (char*) 0x1009aca2;
					entity_type_scan_ptr += 0x21c) {
					if (*entity_type_scan_ptr == '\x0f') {
						break;
					}
					slot_scan_idx_or_capacity = slot_scan_idx_or_capacity + 1;
				}
				if (slot_scan_idx_or_capacity == 0x300) {
					LogMessageInternal(
						"D:\\Develop\\DieGildeAddOn\\game\\friedhof_logic.c",
						0x6ef,
						"gv_ExAllocGraveyardWorker: array overflow...",
						1
					);
					return 0xffff;
				}
			}
			entity_slot_byte_offset = slot_scan_idx_or_capacity * 0x21c;
			if (*(char*) (entity_slot_byte_offset + 0x100358a2) == '\x0f') {
				g_citizen_count = g_citizen_count - 1;
			}
			new_entity_slot_ptr = (unsigned short*) (entity_slot_byte_offset + (int) &g_slot_table);
			memset(new_entity_slot_ptr, 0, 0x21c);
			*new_entity_slot_ptr = 0xffff;
			*(int*) (entity_slot_byte_offset + 0x100358a4) = (int) 0xffffffff;
			memset((char*) (entity_slot_byte_offset + 0x100358fc), 0xff, 0x20);
			*(unsigned char**) (entity_slot_byte_offset + 0x10035a10) = building_entity_ptr;
			*(unsigned char**) (entity_slot_byte_offset + 0x10035a0c) = building_entity_ptr;
			g_citizen_count = g_citizen_count + 1;
			*(int*) (entity_slot_byte_offset + 0x100358a4) = g_next_object_id;
			g_next_object_id = g_next_object_id + 1;
			*new_entity_slot_ptr = (unsigned short) slot_scan_idx_or_capacity;
			*(char*) (entity_slot_byte_offset + 0x100358a2) = 0x14;
			*(int*) (entity_slot_byte_offset + 0x10035a90) = 0;
			*(int*) (entity_slot_byte_offset + 0x10035ab0) = (int) 0xffffffff;
			*(char*) (entity_slot_byte_offset + 0x10035ab5) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035ab6) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035ab7) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035ab8) = 1;
			*(int*) (entity_slot_byte_offset + 0x10035a84) = 0x3f800000;
			*(short*) (entity_slot_byte_offset + 0x100358a8) = 100;
			*(short*) (entity_slot_byte_offset + 0x100358aa) = 0x10;
			*(char*) (entity_slot_byte_offset + 0x10035a04) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035a06) = 0;
			*(char*) (entity_slot_byte_offset + 0x10035a05) = *(char*) (cmd_payload + 0x15);
			*(int*) (entity_slot_byte_offset + 0x10035a94) = 0;
			*(int*) (entity_slot_byte_offset + 0x10035a30) = 4;
			*(int*) (entity_slot_byte_offset + 0x10035a34) = 0;
			*(char*) (entity_slot_byte_offset + 0x100358ad) = 1;
			*(int*) (entity_slot_byte_offset + 0x10035a2c) = (int) 0xffffffff;
			*(int*) (entity_slot_byte_offset + 0x10035aac) = (int) 0xffffffff;
			*(short*) (entity_slot_byte_offset + 0x100358f0) = 0x7fff;
			slot_scan_idx_or_capacity = 0;
			do {
				*(char*) (slot_scan_idx_or_capacity + 0x80 + (int) new_entity_slot_ptr) =
					*((char*) matched_production_record + slot_scan_idx_or_capacity + 0x24) >> 1;
				slot_scan_idx_or_capacity = slot_scan_idx_or_capacity + 1;
			} while (slot_scan_idx_or_capacity < 5);
			*(char*) (entity_slot_byte_offset + 0x100358a9) = *((char*) matched_production_record + 0x38);
			strcpy((char*) (entity_slot_byte_offset + 0x100358d0), (char*) matched_production_record + 4);
			strcpy((char*) (entity_slot_byte_offset + 0x100358e0), (char*) matched_production_record + 0x14);
			*(int*) (entity_slot_byte_offset + 0x100358b0) = 0;
			random_float = gm_RandomFloat01();
			*(int*) (entity_slot_byte_offset + 0x100358b8) = 0;
			*(int*) (entity_slot_byte_offset + 0x100358bc) = 0x447a0000;
			*(int*) (entity_slot_byte_offset + 0x100358c0) = 0;
			*(int*) (entity_slot_byte_offset + 0x100358c4) = 0;
			*(int*) (entity_slot_byte_offset + 0x100358c8) = 0;
			*(int*) (entity_slot_byte_offset + 0x100358cc) = 0;
			relationship_loop_idx = 0;
			slot_scan_idx_or_capacity = 0;
			*(float*) (entity_slot_byte_offset + 0x100358b4) =
				DAT_10025680 / (float) (random_float * (double) DAT_100257c8 + (double) DAT_100257c4);
			do {
				entity_slot_index = *new_entity_slot_ptr;
				rand_relationship_val = (char) gm_RandomMod(0x40);
				*(char*) (entity_slot_index + slot_scan_idx_or_capacity + 0x1014d8e0) = 0;
				*(char*) (entity_slot_index + slot_scan_idx_or_capacity + 0x100a9820) = rand_relationship_val - 0x20;
				entity_slot_byte_offset = *new_entity_slot_ptr * 0x300 + relationship_loop_idx;
				rand_relationship_val = (char) gm_RandomMod(0x40);
				slot_scan_idx_or_capacity = slot_scan_idx_or_capacity + 0x300;
				relationship_loop_idx = relationship_loop_idx + 1;
				*(char*) (entity_slot_byte_offset + 0x100a9820) = rand_relationship_val - 0x20;
				*(char*) (entity_slot_byte_offset + 0x1014d8e0) = 0;
			} while (slot_scan_idx_or_capacity < 0x90000);
			if (*matched_production_record == *(int*) (production_slot_entry_ptr + 4)) {
				slot_scan_idx_or_capacity = *(int*) (*(int*) (cmd_payload + 0xc) * 4 + 0x1002574c);
				if (0 < slot_scan_idx_or_capacity) {
					search_loop_idx = 0;
					production_record_walker = *(int**) (production_slot_entry_ptr + 0x10);
					do {
						if (*production_record_walker != -1 &&
							*production_record_walker != *matched_production_record) {
							*(int*) (production_slot_entry_ptr + 4) = *production_record_walker;
							goto code_r0x10011fcd;
						}
						search_loop_idx = search_loop_idx + 1;
						production_record_walker = production_record_walker + 0x11;
					} while (search_loop_idx < slot_scan_idx_or_capacity);
				}
				*(int*) (production_slot_entry_ptr + 4) = (int) 0xffffffff;
				*(short*) (production_slot_entry_ptr + 8) = (short) 0xffff;
			}
		code_r0x10011fcd:
			production_record_walker = matched_production_record;
			for (search_loop_idx = 0x11; search_loop_idx != 0; search_loop_idx = search_loop_idx - 1) {
				*production_record_walker = 0;
				production_record_walker = production_record_walker + 1;
			}
			*matched_production_record = -1;
			return (unsigned int) *new_entity_slot_ptr;
		}
	}
	return 0xffff;
}
