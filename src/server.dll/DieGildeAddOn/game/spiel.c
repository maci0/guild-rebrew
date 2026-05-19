#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
int __cdecl __ftol(void);

typedef int(__cdecl* ALLOCFN)(int, int, int);

#pragma intrinsic(memcpy, memset)

typedef struct {
	char pad[0x24];
	int(__cdecl* func)(int, int);
	int field_28;
} DISPATCH_OBJ;

#pragma pack(push, 1)
typedef struct {
	short active;
	int id;
	char pad[0x3d];
} Record;
#pragma pack(pop)

extern char* g_entity_table; /* 0x101de450 */
;
void __cdecl gm_InitObjektHersteller(void);
void __cdecl gm_InitEntitySlots(void);
int __cdecl _getpid(void);
extern char* g_entity_ptr;
void __cdecl vfs_EntityCleanup(char*);
extern unsigned short* DAT_100a8c34;
extern int DAT_10035450;
extern Record* g_records;
void __cdecl free_block(int);
extern int g_data_ptr;
extern int g_data_ptr2;
extern int g_data_ptr3;
extern int g_data_ptr4;
extern char* g_game_initialized;
extern unsigned char* DAT_1014d8c0;
extern int DAT_100a8c30;
extern unsigned char DAT_10035439;
extern int DAT_1003543c;
extern char* DAT_101de450;
void* __cdecl FindNextFilteredEntity(void);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern WORD* DAT_10035468;
extern char DAT_10035454;
extern char DAT_1003545d;
extern int DAT_10035458;
extern short DAT_10030b94;
extern int DAT_10030b98;
extern short DAT_10030b9c;
extern char DAT_10030b9e;
extern char DAT_1003545c;
extern char DAT_1003545e;
extern int DAT_100a8c38;
extern int* DAT_101398a0;
extern int* DAT_1013989c;
extern char* g_array_base;
// DATA: SERVER 0x100358a0
extern char g_entity_array[];
void __cdecl free_node(char*);
int __cdecl gm_FreeObjectListRecursive(char**);
void __cdecl gm_NoopRet2(void);
char* __cdecl gm_AllocateObjectSlot(void);
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
short* __cdecl gm_ResolveParentEntity(short*);
extern int g_item_def_table;
extern int g_next_object_id;
extern int g_object_count;
extern int g_current_year;
extern char s_D__Develop_DieGildeAddOn_game_sp_10031004[];
extern char s_gm_AddObjekt____obj____ob_NULL_10031390[];
extern char s_gm_AddObjekt____Parent_not_found_10031358[];
extern unsigned char* g_EntityListStart;
extern unsigned char* g_EntitySearchPtr;
extern int g_SearchCount;
extern unsigned char g_SearchFlag;
extern void* g_SomeGlobal;
extern unsigned char g_FilterActive;
extern unsigned char g_FilterType;
extern int g_FilterId;
extern unsigned short g_FilterVal25;
extern unsigned short g_FilterVal27;
extern unsigned char g_FilterVal30;
extern char* g_array;
void __cdecl gv_Free3Fields(void* param);
extern int DAT_10035a0c;
extern unsigned char DAT_10030861;
char* __cdecl gm_SearchStruct(void);
int __cdecl gm_AllocBuildingContents(char* geb, int obj_id);
unsigned short* __cdecl gm_SetupEntityQuery(unsigned char*);
int __cdecl gm_CheckEntityType(unsigned char* geb);
int __cdecl AllocGraveyardField(char* geb);
void __cdecl SpawnGraveyardEntities(char* geb, int param);
void __cdecl gm_SetBuildingWorkerLimits(unsigned char* geb);
int __cdecl gm_GetBuildingTypeCategory(int);
void __cdecl gm_AllocBuildingDefaults(unsigned char* geb);
extern char* g_table_a9;
extern char* dword_100a8c30;
extern unsigned short* dword_100a8c34;
extern char* dword_101de450;
char* __cdecl gm_GetMsgField(int param);
extern int g_entity_type_table;
extern char g_current_season;
extern char g_10031004[];
extern char g_10031484[];
extern char g_100314b8[];
int __cdecl gm_EntityAccumulate(void*);
int __cdecl gm_RemoveLinkedNodeById(int*, int);
void __cdecl amt_ClearEntityLinks(short*);
void __cdecl gm_InitEntityIfValid(void* param_1);
void __cdecl gm_DeallocEntity(unsigned int idx, int param);
extern int DAT_10035434;
extern int DAT_1003542c;
extern int DAT_10035430;
extern char g_entity_base[];
extern char g_entity_end[];
int __cdecl gm_GetBuildingTypeCategory(int param_1);
int __cdecl gm_MapEntityStatRange(int);
short* __cdecl gm_GetEntityTableEntry(char*);
extern float DAT_100257bc;
int __cdecl gm_RandomMod(unsigned short range);
extern char entity_table[];
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_AssignBuildingOwner(unsigned char*, unsigned short, unsigned int);
int __cdecl gm_WalkEntityChain(int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl gm_GetOppositeStatIndex(int);
void* __cdecl gm_AddOrAccumulateObject(int, int, int);
extern int g_citizen_count;
extern char entity_slot_table[];
extern float DAT_10025fb8; /* 0x10025fb8 */
;
extern float DAT_10025fb4; /* 0x10025fb4 */
;
extern float DAT_10025fb0; /* 0x10025fb0 */
;
extern float DAT_10025fac; /* 0x10025fac */
;
extern float DAT_10025fa8; /* 0x10025fa8 */
;
extern double DAT_10025fa0; /* 0x10025fa0 */
;
extern float _DAT_100256cc; /* 0x100256cc */
;
extern float DAT_100257c8; /* 0x100257c8 */
;
extern double DAT_100257d0; /* 0x100257d0 */
;
double __cdecl gm_CalculateProductionValue(int, int);
extern char g_type_idx;
extern int g_key_table[];
extern char entity_array[];
int __cdecl gm_SumBuildingProductionValues(char*, int);
int __cdecl gm_EntityQuerySum(int);
int __cdecl compute_size(char*); /* 0x10019d00 */
;
int __cdecl gm_FindEntityByOwner(char*, char*); /* 0x10019cd0 */
;
int __cdecl ahm_LookupEntityInTable(int); /* 0x1000c670 */
;
extern float _DAT_10025fbc;
double __cdecl gm_RandomFloat01(void);
extern float _DAT_100256a0;
extern float _DAT_100256a8;

/* Allocates and initializes a game entity structure. Allocates
 * memory via m_AllocTracked and zeroes the initial fields. */

// FUNCTION: SERVER 0x10004B80
// gm_AllocAndInit

void* __cdecl gm_AllocAndInit(char a, char b, int c, int d, char* ctx)
{
	char* p;
	p = (char*) ((ALLOCFN) (*(int*) (ctx + 0x20)))(*(int*) (ctx + 0x28), 1, 0x1c);
	if (p) {
		p[0x10] = a;
		p[0x11] = b;
		*(int*) p = 0;
		*(int*) (p + 0x14) = c;
		*(int*) (p + 0x18) = d;
	}
	return p;
}

/* Dispatches a function call through a callback table. Central
 * dispatch mechanism for game system callbacks. */

// FUNCTION: SERVER 0x10005370
// gm_DispatchCall

int __cdecl gm_DispatchCall(int param, DISPATCH_OBJ* obj)
{
	return obj->func(obj->field_28, param);
}

/* Initializes the object production (Hersteller) system.
 * Loads product definitions, recipes, and production chain
 * data from game files. */

// FUNCTION: SERVER 0x100156c0
// gm_InitObjektHersteller

/* Game function - gm_InitObjektHersteller (initialize object manufacturers) */

void __cdecl gm_InitObjektHersteller(void)
{
	int* p;
	int i;
	char* record_base;
	int byte_offset;
	int record_index;
	int same_count;
	int run_length;
	int prev_type;
	char* record;
	int entity_type;

	/* Zero manufacturer table (25 ints) */
	p = (int*) 0x10139820;
	for (i = 0x19; i != 0; i--) {
		*p = 0;
		p++;
	}

	same_count = 0;
	run_length = 0;

	LogMessageInternal((char*) 0x10031004, 0x458, (char*) 0x1003102c, 1);

	*(int*) 0x10139840 = 0x2f;
	*(int*) 0x1013983c = 0x32;
	*(int*) 0x10139838 = 0x29;
	*(int*) 0x10139848 = 0x21;
	*(int*) 0x10139858 = 0x1e;
	*(int*) 0x1013985c = 0x1f;
	*(int*) 0x10139860 = 0x20;
	*(int*) 0x1013984c = 0x17;
	*(int*) 0x10139850 = 0x35;
	*(int*) 0x10139844 = 0x14;

	LogMessageInternal((char*) 0x10031004, 0x46d, (char*) 0x10030fb0, 1);

	record_base = *(char**) 0x100a8c30;

	/* Fill ObjektNr2MinimalHersteller with 0x58 (732 ints) */
	p = (int*) 0x101dd8e0;
	for (i = 0x2dc; i != 0; i--) {
		*p = 0x58;
		p++;
	}

	record_index = 0;
	byte_offset = 0;
	prev_type = 0x58;

	do {
		record = record_base + byte_offset;
		entity_type = *(unsigned char*) record;

		if (entity_type == prev_type) {
			goto same_type;
		}

		same_count = 0;
		run_length = 0;
		prev_type = entity_type;

		if (byte_offset < 0xca78) {
			int idx = record_index;
			char* scan = record;
			do {
				if (*(unsigned char*) scan != (unsigned char) entity_type) {
					break;
				}
				run_length++;
				idx++;
				scan += 0x24d;
			} while (idx < 0x58);
		}
		goto after_branch;

	same_type:
		same_count++;

	after_branch:
		LogMessageInternal((char*) 0x10031004, 0x490, (char*) 0x10030f54, 1);

		record_base = *(char**) 0x100a8c30;

		if (*(unsigned char*) (record + 0x22) != 0) {
			unsigned short* comp_ptr;
			int comp_count;

			comp_ptr = (unsigned short*) (record + 0x23);
			comp_count = 0;

			do {
				unsigned short entry;

				entry = *comp_ptr;

				if (entry != 0xffff) {
					int ent_idx;
					int mfr_start;
					char* mfr_record;
					int mfr_type;
					int consec;
					int new_val;

					ent_idx = entry & 0x7fff;
					mfr_start = *(unsigned char*) (g_entity_table + (ent_idx << 6) + ent_idx + 0x21);
					mfr_start = *(int*) (mfr_start * 4 + 0x10139820);

					mfr_record = record_base + mfr_start * 0x24d;
					mfr_type = *(unsigned char*) mfr_record;
					consec = 0;

					if (mfr_start < 0x58) {
						int j = mfr_start;
						char* scan = mfr_record;
						do {
							if (*(unsigned char*) scan != (unsigned char) mfr_type) {
								break;
							}
							consec++;
							j++;
							scan += 0x24d;
						} while (j < 0x58);
					}

					new_val = mfr_start + (consec * same_count) / run_length;
					if (new_val < *(int*) (ent_idx * 4 + 0x101dd8e0)) {
						*(int*) (ent_idx * 4 + 0x101dd8e0) = new_val;
					}
				}

				comp_count++;
				comp_ptr++;
			} while (comp_count < *(unsigned char*) (record + 0x22));
		}

		byte_offset += 0x24d;
		record_index++;
	} while (byte_offset < 0xca78);

	LogMessageInternal((char*) 0x10031004, 0x4ae, (char*) 0x10030eec, 1);

	{
		int* min_ptr;
		unsigned char* type_ptr;

		min_ptr = (int*) 0x101dd8e0;
		type_ptr = (unsigned char*) (g_entity_table + 0x21);

		do {
			if (*min_ptr == 0x58) {
				*min_ptr = *(int*) (*type_ptr * 4 + 0x10139820);
			}
			min_ptr++;
			type_ptr += 0x41;
		} while ((int) min_ptr < 0x101de450);
	}
}

/* Opens/initializes the game world. Loads map data, entity
 * tables, building type definitions, and sets up the
 * simulation state. Central game world init function. */

// FUNCTION: SERVER 0x10015950
// gm_Open

// DATA: SERVER 0x100a8c30
extern int g_entity_type_table;
// DATA: SERVER 0x1014d8c0
extern int g_1014d8c0;
// DATA: SERVER 0x101de450
extern int g_item_def_table;
// DATA: SERVER 0x100a8c34
extern int g_100a8c34;

// DATA: SERVER 0x100a8cf8
extern int g_100a8cf8;
// DATA: SERVER 0x1009b764
extern int g_1009b764;
// DATA: SERVER 0x1002dde0
extern int g_1002dde0;

int __cdecl gm_Open(int param_1)
{
	unsigned int* src_player_ptr;
	unsigned int* dst_player_ptr;
	unsigned int player_field;
	FILE* file_handle;
	int next_offset;
	unsigned short slot_entry;
	char item_category;
	int producible_count;
	unsigned short* slot_ptr;
	int slot_counter;
	unsigned char path_buf[512];
	int table_offset;

	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4d3, "gm_Open(): enter", 1);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4d6, "gm_Open(): Spieler initialisieren", 1);
	src_player_ptr = (unsigned int*) &g_100a8cf8;
	dst_player_ptr = (unsigned int*) &g_1009b764;
	do {
		dst_player_ptr[-1] = src_player_ptr[-0x14];
		player_field = *src_player_ptr;
		dst_player_ptr[0] = 1000;
		dst_player_ptr[1] = player_field;
		dst_player_ptr[2] = 1000;
		memcpy((void*) &dst_player_ptr[3], (void*) &g_1002dde0, 0x2a80);
		src_player_ptr = src_player_ptr + 0xbd;
		dst_player_ptr = dst_player_ptr + 0xaa4;
	} while ((unsigned int) src_player_ptr < 0x100a9bbc);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4e3, "gm_Open(): Gebaeude-Daten", 1);
	g_entity_type_table = (int) m_AllocTracked(0xca78, (const char*) 0x100311d8);
	if (g_entity_type_table == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4e8, "Memory could not be allocated!", 1);
		return -1;
	}
	g_1014d8c0 = (int) m_AllocTracked(0xa900, (const char*) 0x100311a0);
	memset((void*) g_1014d8c0, 0, 0xa900);
	if (g_1014d8c0 == 0) {
		return -2;
	}
	sprintf((char*) path_buf, (char*) 0x1003118c, param_1, (char*) 0x10031194);
	file_handle = fopen((char*) path_buf, (char*) 0x1002944c);
	if (file_handle == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4f5, (char*) 0x10031154, 1);
		return -3;
	}
	fread((void*) g_entity_type_table, 0x24d, 0x58, file_handle);
	fflush(file_handle);
	g_item_def_table = (int) m_AllocTracked(0xb9dc, (const char*) 0x10031140);
	if (g_item_def_table == 0) {
		return -4;
	}
	g_100a8c34 = (int) m_AllocTracked(0x14f218, (const char*) 0x1003112c);
	if (g_100a8c34 == 0) {
		return -5;
	}
	memset((void*) g_100a8c34, 0, 0x14f218);
	sprintf((char*) path_buf, (char*) 0x1003118c, param_1, (char*) 0x10031120);
	file_handle = fopen((char*) path_buf, (char*) 0x1002944c);
	if (file_handle == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
			0x52d,
			"Objekt-Daten konnten nicht geladen werden! (A_Obj.dat)",
			1
		);
		return -6;
	}
	fread((void*) g_item_def_table, 0x41, 0x2dc, file_handle);
	fflush(file_handle);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x536, "gm_Open(): gm_InitObjektHersteller", 1);
	gm_InitObjektHersteller();
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x53a, "gm_Open(): gm_KillAllSpieler", 1);
	gm_InitEntitySlots();
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
		0x53e,
		"gm_Open(): ---- Das dusselige Datendesign hinbiegen !! -----",
		1
	);
	table_offset = 0;
	do {
		producible_count = 0;
		slot_counter = 0x40;
		slot_ptr = (unsigned short*) (table_offset + 0x23 + g_entity_type_table);
		do {
			slot_entry = *slot_ptr;
			if (slot_entry != 0xffff) {
				item_category = *(char*) (g_item_def_table + (slot_entry & 0x7fff) * 0x41);
				if (((item_category == '\x02') || (item_category == '\x06')) && ((slot_entry & 0x7fff) != 0xfd) &&
					((slot_entry & 0x8000) != 0)) {
					producible_count = producible_count + 1;
				}
			}
			slot_ptr = slot_ptr + 1;
			slot_counter = slot_counter + -1;
		} while (slot_counter != 0);
		next_offset = table_offset + 0x24d;
		*(char*) (table_offset + 0x21 + g_entity_type_table) =
			*(char*) (table_offset + 0x21 + g_entity_type_table) + producible_count;
		table_offset = next_offset;
	} while (next_offset < 0xca78);
	_getpid();
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x588, "gm_Open(): exit", 1);
	return 0;
}

/* Resets all entities to initial state. Walks the entity
 * tables and clears all active entities without deallocation. */

// FUNCTION: SERVER 0x10015CB0
// gm_ResetAllEntities

void __cdecl gm_ResetAllEntities(void)
{
	int i;
	char* p;
	for (i = 0; i < 0x100; i++) {
		p = g_entity_ptr + i * 0xa9;
		if (*p != 0) {
			vfs_EntityCleanup(p);
		}
	}
	{
		int* dst;
		int n;
		dst = (int*) g_entity_ptr;
		for (n = 0; n < 0x2a40; n++) {
			*dst++ = 0;
		}
	}
}

/* Cleans up object entities. Frees inventory objects and
 * linked item chains from all active entities. */

// FUNCTION: SERVER 0x10015cf0
// gm_CleanupObjectEntities

int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
int __cdecl gm_RemoveObjectByType(void** objectListHead, unsigned int objectTypeId);
void __cdecl gm_NoopRet2(void);

void __cdecl gm_CleanupObjectEntities(void)
{
	void** objectListHead;
	int record_offset;
	int pRecord;
	unsigned int* clear_ptr;
	void* dynamic_ent;
	void* existing_ent;
	void* static_ent;

	record_offset = 0;
	do {
		if (*(short*) (record_offset + (int) DAT_100a8c34) != 0) {
			gm_ResolveEntityById(
				&dynamic_ent,
				&existing_ent,
				&static_ent,
				*(int*) (record_offset + 6 + (int) DAT_100a8c34)
			);
			if (dynamic_ent != (void*) 0) {
				objectListHead = (void**) ((int) dynamic_ent + 0x5d);
			}
			else if (existing_ent != (void*) 0) {
				objectListHead = (void**) ((int) existing_ent + 0x14);
			}
			else if (static_ent != (void*) 0) {
				objectListHead = (void**) ((int) static_ent + 0x178);
			}
			else {
				goto LAB_cleanup;
			}
			if (objectListHead != (void**) 0) {
				gm_RemoveObjectByType(
					objectListHead,
					(unsigned int) *(unsigned short*) (record_offset + (int) DAT_100a8c34)
				);
				goto LAB_10015d8e;
			}
		LAB_cleanup:
			pRecord = record_offset + (int) DAT_100a8c34;
			gm_NoopRet2();
			*(short*) (record_offset + (int) DAT_100a8c34) = 0;
			DAT_10035450 = DAT_10035450 + -1;
		}
	LAB_10015d8e:
		record_offset = record_offset + 0x43;
	} while (record_offset < 0x14f218);
	clear_ptr = (unsigned int*) DAT_100a8c34;
	for (record_offset = 0x53c86; record_offset != 0; record_offset = record_offset + -1) {
		*clear_ptr = 0;
		clear_ptr = clear_ptr + 1;
	}
}

/* Finds a record in the entity table by ID. Searches the
 * global entity records for a matching entity ID. Returns
 * pointer or NULL. */

// FUNCTION: SERVER 0x10015dc0
// gm_FindRecordById

Record* __cdecl gm_FindRecordById(int id)
{
	int i;
	Record* p;

	i = 0;
	p = g_records;
	while (i < 0x5008) {
		if (p->active != 0 && p->id == id) {
			return (Record*) ((char*) g_records + i * 0x43);
		}
		i++;
		p = (Record*) ((char*) p + 0x43);
	}
	return (Record*) 0;
}

/* Cleans up all entities. Complete teardown of all game
 * entities including buildings, citizens, and objects. */

// FUNCTION: SERVER 0x10015E00
// gm_CleanupAllEntities

void __cdecl gm_CleanupAllEntities(void)
{
	int ent;
	ent = (int) gm_StartFilteredEntitySearch(1, 6);
	if (ent) {
		do {
			((void(__cdecl*)(unsigned char*)) gm_CleanupBuildingEntity)((unsigned char*) ent);
			ent = (int) FindNextFilteredEntity();
		} while (ent);
	}
	if (g_data_ptr) {
		free_block(g_data_ptr);
		g_data_ptr = 0;
	}
	if (g_data_ptr2) {
		free_block(g_data_ptr2);
		g_data_ptr2 = 0;
	}
	if (g_data_ptr3) {
		free_block(g_data_ptr3);
		g_data_ptr3 = 0;
	}
	if (g_data_ptr4) {
		free_block(g_data_ptr4);
		g_data_ptr4 = 0;
	}
}

/* Resolves an entity by ID to up to three pointers:
 * primary entity, object entity, and dynamic entity.
 * Returns non-zero on success. Core entity resolution API. */

// FUNCTION: SERVER 0x10015e90
// gm_ResolveEntityById

int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id)
{
	short* entity_slot;
	char* dynamic_entity;
	int search_index;

	if (g_game_initialized != 0) {
		if (dynamic != (void**) 0) {
			*dynamic = (void*) 0;
		}
		if (existing != (void**) 0) {
			*existing = (void*) 0;
		}
		if (static_ptr != (void**) 0) {
			*static_ptr = (void*) 0;
			entity_slot = (short*) 0x100358a0;
			search_index = 0;
			do {
				if (*entity_slot != -1 && *(int*) (entity_slot + 2) == entity_id) {
					*static_ptr = entity_slot;
					return 3;
				}
				entity_slot = (short*) ((char*) entity_slot + 0x21c);
				search_index = search_index + 1;
			} while (search_index < 0x300);
		}
		if (dynamic != (void**) 0) {
			search_index = 0;
			dynamic_entity = DAT_1014d8c0;
			do {
				if (*dynamic_entity != '\0' && *(int*) (dynamic_entity + 1) == entity_id) {
					*dynamic = dynamic_entity;
					return 1;
				}
				search_index = search_index + 1;
				dynamic_entity = dynamic_entity + 0xa9;
			} while (search_index < 0x100);
		}
		if (existing != (void**) 0 && (search_index = 0, entity_slot = DAT_100a8c34, DAT_10035450 > 0)) {
			do {
				if (*entity_slot != 0) {
					if (*(int*) (entity_slot + 1) == entity_id) {
						*existing = entity_slot;
						return 2;
					}
					search_index = search_index + 1;
				}
				entity_slot = (short*) ((char*) entity_slot + 0x43);
			} while (search_index < DAT_10035450);
		}
	}
	return 0;
}

/* Refreshes market availability. Recalculates which goods
 * are available for trade based on current building production
 * and inventory states. */

// FUNCTION: SERVER 0x10015f70
// gm_RefreshMarketAvailability

void __cdecl gm_RefreshMarketAvailability(int param_1)
{
	int base;
	int resource_types[8];

	resource_types[0] = 0x92;
	resource_types[1] = 0x93;
	resource_types[2] = 0x94;
	resource_types[3] = 0x95;
	resource_types[4] = 0x96;
	resource_types[5] = 0x97;
	resource_types[6] = 0x2db;
	resource_types[7] = 0;

	DAT_1003543c = (int) gm_StartFilteredEntitySearch(1, 5, 10);
	if (DAT_1003543c == 0) {
		LogMessageInternal((char*) 0x10031004, 0x7cf, (char*) 0x1003122c, 1);
		return;
	}

	{
		int ecx;
		int eax;
		ecx = param_1;
		eax = ecx;
		eax = eax << 4;
		eax = eax + ecx;
		eax = eax + eax * 4;
		base = ecx + eax * 8;
		base = base << 4;
		base = base + 0x1009b770;
	}

	if (param_1 != DAT_10035439) {
		return;
	}

	/* Clear offset 4 of each of 0x55 slots (stride 0x80) */
	{
		int ptr;
		int cnt;
		ptr = base + 4;
		cnt = 0x55;
		do {
			*(int*) ptr = 0;
			ptr += 0x80;
			cnt--;
		} while (cnt != 0);
	}

	/* First major loop: iterate filtered entities */
	{
		int entity_ptr;
		entity_ptr = (int) gm_StartFilteredEntitySearch(1, 6);
		if (entity_ptr != 0) {
			do {
				int byteVal;
				int edi;
				int ecx2;
				byteVal = *(unsigned char*) entity_ptr;
				edi = DAT_100a8c30;
				edi += byteVal;
				ecx2 = byteVal + byteVal * 2;
				ecx2 = ecx2 << 4;
				ecx2 = ecx2 + byteVal;
				ecx2 = ecx2 + ecx2 * 2;
				if (*(char*) (edi + ecx2 * 4) != '\n') {
					int query_result;
					query_result = (int) gm_StartEntityQuery(*(int*) (entity_ptr + 0x5d), 1, 0, 0xff);
					param_1 = 0;
					if (query_result != 0) {
						int pSlot;
						pSlot = base;
						while (param_1 < 0x55) {
							if (*(short*) pSlot != 0) {
								int inner_query;
								inner_query = (int)
									gm_StartEntityQuery(*(int*) (query_result + 0x14), 1, 0, *(short*) pSlot & 0xffff);
								if (inner_query != 0) {
									int rowId;
									int edx2;
									int pOuter;
									int pInner;
									int outerCount;
									int pInnerCount;
									*(int*) (pSlot + 4) = 1;
									rowId = *(short*) pSlot & 0xffff;
									edx2 = *(int*) DAT_101de450;
									edx2 = edx2 + (rowId << 6);
									edx2 = edx2 + rowId;
									pOuter = base;
									outerCount = 0x55;
									do {
										pInner = edx2 + 0x2e;
										pInnerCount = 4;
										do {
											if (*(short*) pOuter == *(short*) pInner) {
												*(int*) (pOuter + 4) = 1;
											}
											pInner += 2;
											pInnerCount--;
										} while (pInnerCount != 0);
										pOuter += 0x80;
										outerCount--;
									} while (outerCount != 0);
								}
							}
							param_1++;
							pSlot += 0x80;
						}
					}
				}
				entity_ptr = (int) FindNextFilteredEntity();
			} while (entity_ptr != 0);
		}
	}

	/* Second major loop: 0x55 iterations over base array */
	{
		int query_result;
		int esi;
		query_result = 0x55;
		esi = base;
		do {
			int inner_query;
			int outer_query;
			int edi;
			inner_query = DAT_1003543c;
			{
				int ax;
				ax = *(short*) (esi + 0x3c) & 0xffff;
				outer_query = (int) gm_StartEntityQuery(*(int*) (inner_query + 0x5d), 1, 0, ax);
				if (outer_query != 0) {
					edi = (int) gm_StartEntityQuery(*(int*) (outer_query + 0x14), 1, 0, 0xff);
					if (*(int*) (esi + 4) != 0) {
						int edx;
						int cx;
						edx = *(int*) (edi + 0x14);
						cx = *(short*) esi & 0xffff;
						inner_query = (int) gm_StartEntityQuery(edx, 1, 0, cx);
						if (inner_query == 0) {
							gm_AllocObjekt(*(int*) (edi + 2), *(short*) esi & 0xffff, 1);
						}
					}
				}
			}
			esi += 0x80;
			query_result--;
		} while (query_result != 0);
	}

	/* Third loop: iterate over resource_types array */
	{
		int resource_id;
		int* pArr;
		resource_id = 0x92;
		pArr = &resource_types[0];
		do {
			int inner_query;
			int outer_query;
			int count_query;
			int uCount;
			uCount = 0;
			outer_query = (int) gm_StartEntityQuery(*(int*) (DAT_1003543c + 0x5d), 1, 0, resource_id);
			if (outer_query != 0) {
				inner_query = (int) gm_StartEntityQuery(*(int*) (outer_query + 0x14), 1, 0, 0xff);
				if (inner_query != 0) {
					count_query = (int) gm_StartEntityQuery(*(int*) (inner_query + 0x14), 1, 5);
					while (count_query != 0) {
						uCount++;
						count_query = (int) gm_NextEntityQueryMatch();
					}
					count_query = (int) gm_StartEntityQuery(*(int*) (outer_query + 0x14), 1, 4, 0x11);
					if (count_query != 0) {
						if ((*(unsigned char*) (count_query + 0x1c) & 0xff) != uCount) {
							*(unsigned char*) (count_query + 0x1c) = (unsigned char) uCount;
						}
					}
				}
			}
			pArr = pArr + 1;
			resource_id = *pArr;
		} while (resource_id != 0);
	}
}

/* Finds a slot by ID in the entity slot table. Returns
 * the slot pointer or NULL if not found. */

// FUNCTION: SERVER 0x10016240
// gm_FindSlotById

// DATA: SERVER 0x1009b770
extern char g_slot_array[];

char* __cdecl gm_FindSlotById(int param_1, int param_2)
{
	int base_offset;
	char* ptr;
	int i;

	base_offset = param_1 * 10896;
	ptr = g_slot_array + base_offset;
	i = 0;
	do {
		if (*(unsigned short*) ptr == param_2) {
			return g_slot_array + base_offset + (i << 7);
		}
		i = i + 1;
		ptr = ptr + 0x80;
	} while (i < 0x55);
	return (char*) 0;
}

/* Returns the next matching entity from an active query.
 * Advances the query iterator and returns the next entity
 * that matches the query criteria. */

// FUNCTION: SERVER 0x10016290
// gm_NextEntityQueryMatch

unsigned short __cdecl gm_GetEntityType(short* entity);

void* __cdecl gm_NextEntityQueryMatch(void)
{
	WORD* candidate_ptr;
	short entity_type_result;
	unsigned short* scan_ptr;
	unsigned short* current;
	unsigned short* matched_ent;
	short filter_type_cache;
	int stack_depth;
	int is_match;
	WORD entry_val;

	current = DAT_10035468;
	matched_ent = (unsigned short*) 0x0;
	is_match = 0;

	if (DAT_10035468 == (WORD*) 0x0) {
		return (void*) 0x0;
	}

	if ((DAT_10035454 != '\0') && (DAT_10035454 = '\0', DAT_1003545d != '\0') &&
		(*(int*) ((int) DAT_10035468 + 10) != 0)) {
		*(int*) (&DAT_101398a0 + DAT_100a8c38 * 4) = *(int*) (DAT_10035468 + 10);
		DAT_100a8c38 = DAT_100a8c38 + 1;
	}

	stack_depth = DAT_100a8c38;
	filter_type_cache = DAT_10030b9c;

	if (DAT_10035458 < DAT_10035450) {
		do {
			if (current == (WORD*) 0x0) {
				return matched_ent;
			}
			if (is_match) {
				return matched_ent;
			}
			entry_val = *current;
			candidate_ptr = current;
			scan_ptr = DAT_10035468;

			while (DAT_10035468 = candidate_ptr, entry_val == 0) {
				scan_ptr = (unsigned short*) ((int) DAT_10035468 + 0x43);
				entry_val = *scan_ptr;
				candidate_ptr = scan_ptr;
			}

			if (DAT_1003545e != '\0') {
				is_match = 1;
			}

			if (DAT_10030b94 == 0x7fff) {
				if (DAT_10030b98 != -1) {
					if (*(int*) ((int) DAT_10035468 + 1) != DAT_10030b98) {
						goto LAB_10016382;
					}
					is_match = 1;
				}
				if (filter_type_cache != -1) {
					candidate_ptr = DAT_10035468;
					DAT_10035468 = scan_ptr;
					entity_type_result = gm_GetEntityType(candidate_ptr);
					stack_depth = DAT_100a8c38;
					filter_type_cache = DAT_10030b9c;
					if (entity_type_result != DAT_10030b9c) {
						is_match = 0;
						goto LAB_100163bc;
					}
					is_match = 1;
				}
				if (DAT_10030b9e != -1) {
					is_match = *(char*) (g_game_initialized + (unsigned int) *DAT_10035468 * 0x41) == DAT_10030b9e;
				}
			}
			else {
				if (*DAT_10035468 == DAT_10030b94) {
					is_match = 1;
					goto check_filters;
				}
			LAB_10016382:
				is_match = 0;
			}
		LAB_100163bc:
		check_filters:
			if (DAT_1003545c == '\0') {
				if (is_match) {
					matched_ent = DAT_10035468;
				}
				current = *(unsigned short**) ((int) DAT_10035468 + 0x3f);
				DAT_10035468 = current;
				if (current == (WORD*) 0x0) {
					if ((DAT_1003545d != '\0') && (stack_depth != 0)) {
						current = *(unsigned short**) (&DAT_1013989c + stack_depth * 4);
						stack_depth = stack_depth - 1;
						DAT_10035468 = current;
						DAT_100a8c38 = stack_depth;
						if (*(int*) (current + 10) != 0) {
							*(int*) (&DAT_101398a0 + stack_depth * 4) = *(int*) (current + 10);
							goto LAB_1001643e;
						}
					}
				}
				else if ((*(int*) (current + 10) != 0) && (DAT_1003545d != '\0')) {
					*(int*) (&DAT_101398a0 + stack_depth * 4) = *(int*) (current + 10);
				LAB_1001643e:
					stack_depth = stack_depth + 1;
					DAT_100a8c38 = stack_depth;
				}
			}
			else {
				if (is_match) {
					matched_ent = DAT_10035468;
				}
				current = (unsigned short*) ((int) DAT_10035468 + 0x43);
				DAT_10035458 = DAT_10035458 + 1;
				DAT_10035468 = current;
			}
		} while (DAT_10035458 < DAT_10035450);
	}

	return matched_ent;
}

/* Starts a new entity query with type, filter, and range
 * parameters. Initializes the query state for iteration
 * via gm_NextEntityQueryMatch. Variadic args for filters. */

// FUNCTION: SERVER 0x10016460
// gm_StartEntityQuery

// DATA: SERVER 0x101de450
// DATA: SERVER 0x10030b94
// DATA: SERVER 0x10030b98
// DATA: SERVER 0x10030b9c

// DATA: SERVER 0x10030b9e
extern char DAT_10030b9e;

// DATA: SERVER 0x1003545e
extern char DAT_1003545e;

// DATA: SERVER 0x1003545c
extern char DAT_1003545c;

// DATA: SERVER 0x1003545d
extern char DAT_1003545d;

// DATA: SERVER 0x10035454
extern char DAT_10035454;

// DATA: SERVER 0x10035458
extern int DAT_10035458;

// DATA: SERVER 0x100a8c38
extern int DAT_100a8c38;

// DATA: SERVER 0x10035468
extern unsigned short* DAT_10035468;

unsigned short* __cdecl gm_StartEntityQuery(int param_1, int param_2, int param_3, ...)
{
	int* arg_ptr;
	int i;
	unsigned char flag1;
	unsigned char flag2;

	if (DAT_101de450 == 0) {
		return (unsigned short*) 0;
	}

	flag1 = 0;
	flag2 = 0;

	DAT_10030b94 = 0x7fff;
	DAT_10030b98 = -1;
	DAT_10030b9c = (short) 0xffff;
	DAT_10030b9e = (char) 0xff;
	DAT_1003545e = 0;
	DAT_1003545c = flag1;
	DAT_1003545d = flag2;
	DAT_10035454 = 1;
	DAT_10035458 = 0;
	DAT_100a8c38 = 0;

	if (param_2 > 0) {
		arg_ptr = &param_3;

		for (i = param_2; i > 0; i--) {
			unsigned char ftype;

			ftype = *(unsigned char*) arg_ptr;
			switch (ftype) {
			case 0:
				arg_ptr++;
				DAT_10030b94 = *(unsigned short*) arg_ptr;
				break;
			case 1:
				DAT_10030b98 = *(arg_ptr + 1);
				arg_ptr++;
				break;
			case 2:
				DAT_10030b9c = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 3:
				DAT_10030b9e = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 4:
				DAT_1003545e = 1;
				break;
			case 5:
				flag2 = 1;
				break;
			case 6:
				flag1 = 1;
				break;
			case 7:
				break;
			}
		}

		DAT_1003545c = flag1;
		DAT_1003545d = flag2;

		if (flag1 == 0) {
			goto check_container;
		}

		if (flag2 != 0) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\objekte", 0xb66, "query flags conflict", 1);
			return (unsigned short*) 0;
		}

		DAT_10035468 = DAT_100a8c34;
		return gm_NextEntityQueryMatch();
	}

check_container:
	if (param_1 != 0) {
		DAT_10035468 = DAT_100a8c34;
		return gm_NextEntityQueryMatch();
	}

	return (unsigned short*) 0;
}

/* Allocates an object slot in an entity's inventory.
 * Finds the next free slot and returns its index. */

// FUNCTION: SERVER 0x100165A0
// gm_AllocateObjectSlot

char* __cdecl gm_AllocateObjectSlot(void)
{
	char* p;
	char* result;
	int i;
	p = g_array_base;
	result = 0;
	i = 0;
	while (!result) {
		if (i >= 0x5008) {
			break;
		}
		if (*(short*) p != 0) {
			i++;
			p += 0x43;
		}
		else {
			result = p;
		}
	}
	return result;
}

/* Removes an object from an entity by type. Searches the
 * entity's inventory for an object matching the type and
 * removes it. */

// FUNCTION: SERVER 0x100165d0
// gm_RemoveObjectByType

int __cdecl gm_RemoveObjectByType(char** objectListHead, unsigned int objectTypeId)
{
	char* prevNode;
	char* currentNode;
	int nodeIndex;

	prevNode = 0;
	if (objectListHead == 0) {
		return -1;
	}
	currentNode = *objectListHead;
	if (currentNode == 0) {
		return -1;
	}
	nodeIndex = 0;
	while (*(unsigned short*) currentNode != objectTypeId) {
		prevNode = currentNode;
		currentNode = *(char**) (currentNode + 0x3f);
		nodeIndex++;
		if (currentNode == 0) {
			return -2;
		}
	}
	if (currentNode == 0) {
		return -2;
	}
	if (*(int*) (currentNode + 0x14) != 0) {
		gm_FreeObjectListRecursive((char**) (currentNode + 0x14));
	}
	free_node(currentNode);
	if (nodeIndex == 0) {
		*objectListHead = *(char**) (currentNode + 0x3f);
	}
	else {
		*(char**) (prevNode + 0x3f) = *(char**) (currentNode + 0x3f);
	}
	*(unsigned short*) currentNode = 0;
	DAT_10035450 = DAT_10035450 - 1;
	return 0;
}

/* No-op function that returns 2. Used as a placeholder
 * in function/callback tables. */

// FUNCTION: SERVER 0x10016670
// gm_NoopRet2
void __cdecl gm_NoopRet2(void)
{
}

/* Removes a linked node from an entity's chain by node ID.
 * Unlinks the node and frees its memory. */

// FUNCTION: SERVER 0x10016680
// gm_RemoveLinkedNodeById

int __cdecl gm_RemoveLinkedNodeById(int* param_1, int param_2)
{
	char* prev;
	char* curr;
	int count;

	prev = (char*) 0;
	curr = (char*) *param_1;
	if (curr == (char*) 0) {
		return -1;
	}
	count = 0;
	do {
		if (*(int*) (curr + 2) == param_2) {
			if (curr == (char*) 0) {
				return -2;
			}
			if (*(int*) (curr + 0x14) != 0) {
				gm_FreeObjectListRecursive((char**) (curr + 0x14));
			}
			gm_NoopRet2();
			if (count == 0) {
				*param_1 = *(int*) (curr + 0x3f);
			}
			else {
				*(int*) (prev + 0x3f) = *(int*) (curr + 0x3f);
			}
			*(short*) curr = 0;
			DAT_10035450 = DAT_10035450 - 1;
			return 0;
		}
		prev = curr;
		curr = *(char**) (curr + 0x3f);
		count = count + 1;
		if (curr == (char*) 0) {
			return -2;
		}
	} while (1);
	return -2;
}

/* Recursively frees an object list. Walks the linked list
 * of objects and deallocates each one. */

// FUNCTION: SERVER 0x10016710
// gm_FreeObjectListRecursive

int __cdecl gm_FreeObjectListRecursive(char** head_ptr)
{
	char* node;
	if (!head_ptr) {
		return 0;
	}
	node = *head_ptr;
	if (!node) {
		return -1;
	}
	do {
		*head_ptr = *(char**) (node + 0x3f);
		if (*(int*) (node + 0x14)) {
			gm_FreeObjectListRecursive((char**) (node + 0x14));
		}
		free_node(node);
		node = *head_ptr;
	} while (node);
	return 0;
}

/* Allocates a new object in an entity's inventory. Creates
 * the object entry, sets type/quantity, and links it into
 * the entity's object chain. */

// FUNCTION: SERVER 0x10016760
// gm_AllocObjekt

char* __cdecl gm_AllocObjekt(int param_1, int param_2, int param_3)
{
	int dynamic_parent;
	int existing_parent;
	int static_parent;
	char* item_def_ptr;
	char buf[0x400];
	char* esi;
	int resolve_result;
	int last_node;
	int* edi;
	char* ebx;

	esi = 0;
	existing_parent = 0;
	dynamic_parent = 0;
	static_parent = 0;
	if (g_item_def_table == 0) {
		return 0;
	}
	if (param_1 == -1) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
			0xcb2,
			"gm_AllocObjekt(): Versuch Objekt au\xdf"
			"erhalb einer Hirachie zu erzeugen",
			1
		);
		return 0;
	}
	resolve_result =
		gm_ResolveEntityById((void**) &dynamic_parent, (void**) &existing_parent, (void**) &static_parent, param_1);
	if (resolve_result == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcb8, "gm_AllocObjekt(): Parent not found", 1);
		return 0;
	}
	if (dynamic_parent != 0) {
		edi = (int*) ((char*) dynamic_parent + 0x5d);
	}
	else if (existing_parent != 0) {
		edi = (int*) ((char*) existing_parent + 0x14);
	}
	else if (static_parent != 0) {
		edi = (int*) ((char*) static_parent + 0x178);
	}
	else {
		return 0;
	}
	if (edi != 0) {
		resolve_result = *edi;
		if (resolve_result != 0) {
			do {
				last_node = resolve_result;
				resolve_result = *(int*) (last_node + 0x3f);
			} while (resolve_result != 0);
			esi = gm_AllocateObjectSlot();
			if (esi == 0) {
				LogMessageInternal(
					"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
					0xcd4,
					"gm_AllocObjekt(): Kein Platz mehr",
					1
				);
				return 0;
			}
			*(int*) (last_node + 0x3f) = (int) esi;
		}
		else {
			esi = gm_AllocateObjectSlot();
			if (esi == 0) {
				LogMessageInternal(
					"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
					0xcdd,
					"gm_AllocObjekt(): Kein Platz mehr",
					1
				);
				return 0;
			}
			*edi = (int) esi;
		}
	}
	item_def_ptr = (char*) (g_item_def_table + param_2 * 0x41);
	*(short*) esi = (short) param_2;
	sprintf(buf, "----->ObjID= %i ObjProt= %i", g_next_object_id, param_2 & 0xffff);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcee, buf, 8);
	*(int*) (esi + 2) = g_next_object_id;
	g_next_object_id = g_next_object_id + 1;
	if (dynamic_parent != 0) {
		*(int*) (esi + 0xa) = *(int*) ((char*) dynamic_parent + 1);
	}
	else if (existing_parent != 0) {
		*(int*) (esi + 0xa) = *(int*) ((char*) existing_parent + 0xa);
	}
	else if (static_parent != 0) {
		*(int*) (esi + 0xa) = *(int*) ((char*) static_parent + 4);
	}
	*(int*) (esi + 6) = param_1;
	*(int*) (esi + 0xe) = param_3;
	esi[0x12] = 0x64;
	esi[0x13] = 0;
	*(int*) (esi + 0x14) = 0;
	*(int*) (esi + 0x3f) = 0;
	g_object_count = g_object_count + 1;
	ebx = esi + 0x1c;
	memset(ebx, 0, 31);
	if (param_2 > 0x160) {
		switch (param_2) {
		case 0x174:
		case 0x176:
			*(int*) (esi + 0x20) = 6;
			break;
		case 0x24b:
		case 0x256:
		case 0x266:
			*(int*) (ebx) = 0;
			*(int*) (esi + 0x20) = 0;
			break;
		default:
			break;
		}
	}
	else if (param_2 == 0x160) {
		*(int*) (esi + 0x20) = 0xf;
	}
	else {
		switch (param_2) {
		case 0xb8:
			*ebx = 6;
			break;
		case 300:
			*(int*) (ebx) = -1;
			*(int*) (esi + 0x20) = -1;
			*(int*) (esi + 0x24) = -1;
			*(int*) (esi + 0x28) = g_current_year - 1;
			break;
		case 0x12d:
			*(int*) (ebx) = -1;
			*(int*) (esi + 0x20) = -1;
			*(int*) (esi + 0x24) = -1;
			*(int*) (esi + 0x28) = -1;
			break;
		case 0x134:
		case 0x135:
		case 0x136:
			if (dynamic_parent != 0) {
				int eax;
				eax = *(unsigned short*) ((char*) dynamic_parent + 0x27);
				eax = eax * 3;
				eax = eax * 5;
				eax = eax * 9;
				*(int*) (esi + 0xa) = *(int*) (eax * 4 + 0x100358a4);
			}
			else if (existing_parent != 0) {
				resolve_result = (int) gm_ResolveParentEntity((short*) existing_parent);
				*(int*) (esi + 0xa) = *(int*) (resolve_result + 4);
			}
			else if (static_parent != 0) {
				*(int*) (esi + 0xa) = *(int*) ((char*) static_parent + 4);
			}
			resolve_result = gm_ResolveEntityById(
				(void**) &dynamic_parent,
				(void**) &existing_parent,
				(void**) &static_parent,
				param_1
			);
			while (resolve_result != 0 && dynamic_parent == 0) {
				if (existing_parent != 0) {
					param_1 = *(int*) ((char*) existing_parent + 6);
				}
				else if (static_parent != 0) {
					LogMessageInternal(
						"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
						0xd3d,
						"gm_AllocObjekt(): Karren in Spieler erzeugt?!?",
						1
					);
				}
				resolve_result = gm_ResolveEntityById(
					(void**) &dynamic_parent,
					(void**) &existing_parent,
					(void**) &static_parent,
					param_1
				);
			}
			esi[0x28] = 0;
			esi[0x31] = 2;
			if (dynamic_parent != 0) {
				*(int*) (ebx) = *(int*) ((char*) dynamic_parent + 1);
			}
			else {
				*(int*) (ebx) = -1;
			}
			{
				char* child_obj;
				child_obj = gm_AllocObjekt(*(int*) (esi + 2), 0x1dd, 1);
				*(int*) (child_obj + 0xe) = (int) (*(unsigned short*) esi) - 0x133;
				child_obj[0x1c] = *(unsigned char*) esi - 0x33;
			}
			break;
		case 0x15e:
			*(int*) (esi + 0x20) = 0xf;
			break;
		default:
			break;
		}
	}
	{
		char item_class = *item_def_ptr;
		if (item_class == 0x17 || item_class == 0x20 || item_class == 0x25) {
			*(int*) (ebx) = 0;
		}
	}
	return esi;
}

/* Adds or accumulates an object. If an object of the same
 * type exists, increments its quantity; otherwise allocates
 * a new object slot. */

// FUNCTION: SERVER 0x10016cd0
// gm_AddOrAccumulateObject

void* __cdecl gm_AddOrAccumulateObject(int parent_id, int type_id, int amount)
{
	int lookupStatus;
	int* childListHead;
	void* allocatedObject;
	void* existingObject;
	void* dynamicParent;
	void* staticParent;
	char logBuffer[512];

	if (type_id == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_game_sp_10031004,
			0xdf4,
			s_gm_AddObjekt____obj____ob_NULL_10031390,
			1
		);
		return (void*) 0;
	}
	lookupStatus = gm_ResolveEntityById(&dynamicParent, &existingObject, &staticParent, parent_id);
	if (lookupStatus == 0) {
		sprintf(logBuffer, s_gm_AddObjekt____Parent_not_found_10031358, type_id, amount);
		LogMessageInternal(s_D__Develop_DieGildeAddOn_game_sp_10031004, 0xdfd, logBuffer, 8);
		return (void*) 0;
	}
	if (dynamicParent != (void*) 0) {
		childListHead = (int*) ((int) dynamicParent + 0x5d);
	}
	else if (existingObject != (void*) 0) {
		childListHead = (int*) ((int) existingObject + 0x14);
	}
	else if (staticParent != (void*) 0) {
		childListHead = (int*) ((int) staticParent + 0x178);
	}
	else {
		return (void*) 0;
	}
	existingObject = gm_StartEntityQuery(*childListHead, 1, 0, type_id);
	if (existingObject == (void*) 0) {
		allocatedObject = gm_AllocObjekt(parent_id, type_id, amount);
		return allocatedObject;
	}
	*(int*) ((int) existingObject + 0xe) = *(int*) ((int) existingObject + 0xe) + amount;
	return existingObject;
}

/* Subtracts quantity from an object. If quantity reaches zero,
 * the object is removed and deallocated (killed). Returns 0
 * if insufficient quantity. */

// FUNCTION: SERVER 0x10016de0
// gm_SubObjekt

int __cdecl gm_SubObjekt(void* param_1, unsigned int param_2, int param_3)
{
	unsigned int objectTypeId;
	int resolve_result;
	void** objectListHead;
	void* dynamic_ent;
	void* static_ent;

	resolve_result = gm_ResolveEntityById(&dynamic_ent, (void**) &param_1, &static_ent, (int) param_1);
	objectTypeId = param_2;
	if (resolve_result == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xe2d, "gm_SubObjekt(): Parent not found", 1);
	}
	else {
		if (dynamic_ent != (void*) 0) {
			objectListHead = (void**) ((int) dynamic_ent + 0x5d);
		}
		else if (param_1 != (void*) 0) {
			objectListHead = (void**) ((int) param_1 + 0x14);
		}
		else {
			if (static_ent == (void*) 0) {
				return 0;
			}
			objectListHead = (void**) ((int) static_ent + 0x178);
		}
		param_1 = gm_StartEntityQuery((int) *objectListHead, 1, 0, param_2);
		if (param_1 != (void*) 0 && *(int*) ((int) param_1 + 0xe) >= param_3) {
			*(int*) ((int) param_1 + 0xe) = *(int*) ((int) param_1 + 0xe) - param_3;
			if (*(int*) ((int) param_1 + 0xe) <= 0) {
				gm_RemoveObjectByType(objectListHead, objectTypeId);
			}
			return 1;
		}
	}
	return 0;
}

/* Subtracts quantity without killing the object when it
 * reaches zero. The object slot remains even at zero quantity.
 * Used for transferring where the slot should persist. */

// FUNCTION: SERVER 0x10016ea0
// gm_SubObjektNoKill

int __cdecl gm_SubObjektNoKill(int entity_id, int object_id, int subtract_amount)
{
	int person;
	int slot;
	int building;
	int* container_ptr;
	int result;

	if (gm_ResolveEntityById((void**) &slot, (void**) &person, (void**) &building, entity_id) == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\object", 0xe5c, "entity not found", 1);
		return 0;
	}

	if (slot != 0) {
		container_ptr = (int*) ((char*) slot + 0x5d);
	}
	else if (person != 0) {
		container_ptr = (int*) ((char*) person + 0x14);
	}
	else if (building != 0) {
		container_ptr = (int*) ((char*) building + 0x178);
	}
	else {
		return 0;
	}

	result = (int) gm_StartEntityQuery(*container_ptr, 1, 0, object_id);
	if (result == 0) {
		result = (int) gm_AllocObjekt(entity_id, object_id, 1);
		*(int*) ((char*) result + 0xe) = 0;
	}

	*(int*) ((char*) result + 0xe) -= subtract_amount;

	if (*(int*) ((char*) result + 0xe) == 0) {
		gm_RemoveObjectByType((void**) container_ptr, object_id);
	}

	return 1;
}

/* Finds the next entity matching filter criteria. Used
 * internally by entity query iteration. Advances past
 * non-matching entities. */

// FUNCTION: SERVER 0x10016f80
// FindNextFilteredEntity

void* __cdecl FindNextFilteredEntity(void)
{
	unsigned char* entity = g_EntityListStart;
	unsigned char matched = 0;
	unsigned char* end = entity + 0xa900;

	if (!g_SomeGlobal) {
		return 0;
	}
	if (g_SearchCount > 0x100) {
		return 0;
	}

	if (g_SearchFlag) {
		g_SearchFlag = 0;
		entity = g_EntitySearchPtr;
		if (entity >= end) {
			return 0;
		}
		if (*entity != 0) {
			goto MATCH;
		}
	}
	else {
		entity = g_EntitySearchPtr;
	}

LOOP:
	entity += 0xa9;
	g_EntitySearchPtr = entity;
	if (entity >= end) {
		return 0;
	}
	if (*entity == 0) {
		goto LOOP;
	}

MATCH:
	/* High register pressure starts here - push ebx, ebp, edi */
	{
		unsigned char f_active;
		unsigned char f_type;
		int f_id;
		unsigned short f_v25;
		unsigned short f_v27;
		unsigned char f_v30;

	RETRY:
		f_active = g_FilterActive;
		if (f_active) {
			matched = 1;
		}

		f_type = g_FilterType;
		if (f_type != 0xff) {
			if (*entity != f_type) {
				goto FAIL;
			}
			matched = 1;
		}

		f_id = g_FilterId;
		if (f_id != -1) {
			if (*(int*) (entity + 1) != f_id) {
				goto FAIL;
			}
			matched = 1;
		}

		f_v25 = g_FilterVal25;
		if (f_v25 != 0x7fff) {
			if (*(unsigned short*) (entity + 0x25) != f_v25) {
				goto FAIL;
			}
			matched = 1;
		}

		f_v27 = g_FilterVal27;
		if (f_v27 != 0x7fff) {
			if (*(unsigned short*) (entity + 0x27) != f_v27) {
				goto FAIL;
			}
			matched = 1;
		}

		f_v30 = g_FilterVal30;
		if (f_v30 != 0xff) {
			unsigned char* table = (unsigned char*) g_SomeGlobal;
			if (table[(*entity) * 588] == f_v30) {
				matched = 1;
			}
			else {
				matched = 0;
			}
		}

	DONE:
		g_SearchCount++;
		if (matched) {
			return (void*) entity;
		}

		while (1) {
			entity += 0xa9;
			g_EntitySearchPtr = entity;
			if (entity >= end) {
				if (!matched) {
					g_EntitySearchPtr = 0;
				}
				return 0;
			}
			if (*entity != 0) {
				break;
			}
		}
		goto RETRY;

	FAIL:
		matched = 0;
		goto DONE;
	}
}

/* Starts a filtered entity search. Variadic filter
 * parameters specify entity class, type, and owner
 * constraints. Returns first matching entity. */

// FUNCTION: SERVER 0x100170e0
// gm_StartFilteredEntitySearch

// DATA: SERVER 0x100a8c30
extern int DAT_100a8c30;

// DATA: SERVER 0x10030b8c
extern short DAT_10030b8c;

// DATA: SERVER 0x10030b8e
extern short DAT_10030b8e;

// DATA: SERVER 0x10030b84
extern char DAT_10030b84;

// DATA: SERVER 0x10030b88
extern int DAT_10030b88;

// DATA: SERVER 0x10030b90
extern char DAT_10030b90;

// DATA: SERVER 0x10035444
extern char* DAT_10035444;

// DATA: SERVER 0x10035449
extern char DAT_10035449;

// DATA: SERVER 0x1003544c
extern int DAT_1003544c;

// DATA: SERVER 0x10035448
extern char DAT_10035448;

// DATA: SERVER 0x10035464
extern unsigned char* DAT_10035464;

unsigned short* __cdecl gm_StartFilteredEntitySearch(int param_1, ...)
{
	int* arg_ptr;
	int i;

	if (DAT_100a8c30 == 0) {
		return (unsigned short*) 0;
	}

	DAT_10030b8c = 0x7fff;
	DAT_10030b8e = 0x7fff;
	DAT_10030b84 = (char) 0xff;
	DAT_10030b88 = -1;
	DAT_10030b90 = (char) 0xff;
	DAT_10035444 = 0;
	DAT_10035449 = 1;
	DAT_1003544c = 0;
	DAT_10035448 = 0;

	if (param_1 > 0) {
		arg_ptr = &param_1 + 1;

		for (i = param_1; i > 0; i--) {
			unsigned char ftype;

			ftype = *(unsigned char*) arg_ptr;
			switch (ftype) {
			case 0:
				DAT_10030b84 = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 1:
				DAT_10030b88 = *(arg_ptr + 1);
				arg_ptr++;
				break;
			case 2:
				strcpy(DAT_10035444, *(char**) (arg_ptr + 1));
				arg_ptr++;
				break;
			case 3:
				DAT_10030b8c = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 4:
				DAT_10030b8e = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 5:
				DAT_10030b90 = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 6:
				DAT_10035448 = 1;
				break;
			default:
				break;
			}
		}
	}

	DAT_10035464 = DAT_1014d8c0;
	return FindNextFilteredEntity();
}

/* Searches a structure/record table for a matching entry.
 * Linear search by comparison field. */

// FUNCTION: SERVER 0x10017210
// gm_SearchStruct

char* __cdecl gm_SearchStruct(void)
{
	char* p;
	char* end;
	p = g_array;
	end = p + 0xa900;
	while (p < end) {
		if (*p == 0) {
			break;
		}
		p += 0xa9;
	}
	if (p < end) {
		return p;
	}
	return 0;
}

/* Cleans up a building entity. Frees all contained entities
 * (workers, inventory, production slots) and resets the
 * building to an empty state. */

// FUNCTION: SERVER 0x10017240
// gm_CleanupBuildingEntity

/* DAT_10035a0c: base of entity array, stride 0x21c (0x87 dwords), 768 entries */

int __cdecl gm_CleanupBuildingEntity(unsigned char* param_1)
{
	int* entity_scan;

	if (param_1 == (unsigned char*) 0) {
		return -1;
	}
	if (*param_1 == 0) {
		return -2;
	}
	switch (*param_1) {
	case 0x1e:
		if (*(void**) (param_1 + 0x71) != (void*) 0) {
			m_FreeTracked(*(void**) (param_1 + 0x71));
			*(int*) (param_1 + 0x71) = 0;
		}
		*(int*) (param_1 + 0x71) = 0;
		goto cleanup_loop;
	case 0x48:
	case 0x49:
	case 0x4a:
		gv_Free3Fields(*(void**) (param_1 + 0x65));
		break;
	case 0x4b:
	case 0x4c:
	case 0x4d:
		m_FreeTracked(*(void**) (param_1 + 0x65));
		break;
	default:
		goto cleanup_loop;
	}
	*(int*) (param_1 + 0x65) = 0;
cleanup_loop:
	entity_scan = &DAT_10035a0c;
	do {
		if ((unsigned char*) entity_scan[1] == param_1) {
			entity_scan[1] = 0;
		}
		if ((unsigned char*) *entity_scan == param_1) {
			*entity_scan = 0;
		}
		entity_scan = entity_scan + 0x87;
	} while ((int) entity_scan < 0x1009ae0c);
	if (*(int*) (param_1 + 0x5d) != 0) {
		gm_FreeObjectListRecursive((char**) (param_1 + 0x5d));
	}
	*param_1 = 0;
	return 0;
}

/* Allocates default values for a building entity. Sets up
 * initial worker capacity, production slots, and storage
 * based on building type. */

// FUNCTION: SERVER 0x10017330
// gm_AllocBuildingDefaults

void __cdecl gm_AllocBuildingDefaults(unsigned char* param_1)
{
	void* query_result;
	int inner_count;
	unsigned short* item_ptr;
	unsigned char* table_ptr;

	table_ptr = &DAT_10030861;
	do {
		if (*param_1 == *(table_ptr - 1)) {
			query_result = gm_StartEntityQuery(*(int*) (param_1 + 0x5d), 2, 6, 0, 0xff);
			if (query_result != (void*) 0) {
				goto do_inner;
			}
			query_result = gm_AllocObjekt(*(int*) (param_1 + 1), 0xff, 1);
			if (query_result != (void*) 0) {
			do_inner:
				inner_count = 10;
				item_ptr = (unsigned short*) table_ptr;
				do {
					if (*item_ptr != 0 &&
						gm_StartEntityQuery(*(int*) ((int) query_result + 0x14), 1, 0, (unsigned int) *item_ptr) ==
							(void*) 0) {
						gm_AllocObjekt(*(int*) ((int) query_result + 2), (unsigned int) *item_ptr, 2);
					}
					item_ptr = item_ptr + 1;
					inner_count = inner_count - 1;
				} while (inner_count != 0);
			}
			else {
				LogMessageInternal(
					"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
					0x107f,
					"gm_AllocGebaeude(): Missing potential....",
					1
				);
			}
		}
		table_ptr = table_ptr + 0x15;
	} while ((int) table_ptr < 0x10030b6a);
}

/* Sets worker limits for a building based on its type and
 * upgrade level. Reads from the building type table. */

// FUNCTION: SERVER 0x10017400
// gm_SetBuildingWorkerLimits

void __cdecl gm_SetBuildingWorkerLimits(unsigned char* param_1)
{
	void* worker_obj;
	unsigned char limit_val;
	int type_offset;

	type_offset = DAT_100a8c30 + (unsigned int) *param_1 * 0x24d;
	worker_obj = gm_StartEntityQuery(*(int*) (param_1 + 0x5d), 2, 0, 0x2a, 6);
	if (worker_obj != (void*) 0) {
		limit_val = *(unsigned char*) (type_offset + 0x23d);
		if (((limit_val == 0) && (*(char*) (type_offset + 0x23e) == '\0')) &&
			(*(char*) (type_offset + 0x23f) != '\0')) {
			*(char*) ((int) worker_obj + 0x1c) = *(char*) (type_offset + 0x23f);
		}
		else {
			if (limit_val < 2) {
				limit_val = 2;
			}
			*(char*) ((int) worker_obj + 0x1c) = limit_val;
			limit_val = *(unsigned char*) (type_offset + 0x23e);
			if (limit_val < 2) {
				limit_val = 2;
			}
			*(char*) ((int) worker_obj + 0x1d) = limit_val;
		}
	}
	worker_obj = gm_StartEntityQuery(*(int*) (param_1 + 0x5d), 2, 0, 0x116, 6);
	if (((worker_obj != (void*) 0) && (*(char*) (type_offset + 0x23d) == '\0')) &&
		((*(char*) (type_offset + 0x23e) == '\0' && (*(char*) (type_offset + 0x23f) != '\0')))) {
		*(char*) ((int) worker_obj + 0x1c) = *(char*) (type_offset + 0x23f);
	}
}

/* Allocates a new building (Gebaeude) entity. Creates the
 * building struct, sets type, initializes production and
 * storage, and links to the town. */

// FUNCTION: SERVER 0x100174d0
// gm_AllocGebaeude

// DATA: SERVER 0x100a8c30
extern int g_entity_type_table;

// DATA: SERVER 0x10030b6c
extern int g_next_object_id;

// DATA: SERVER 0x101de450
extern int g_item_def_table;

// DATA: SERVER 0x10035880
extern int g_current_year;
// DATA: SERVER 0x10035884
extern int g_10035884;
// DATA: SERVER 0x10035888
extern int g_10035888;
// DATA: SERVER 0x1003588c
extern short g_1003588c;

char* __cdecl gm_AllocGebaeude(int param_1, int param_2)
{
	char buf[0x400];
	char* pDest;
	unsigned int gebType;
	int base;
	int var_4;
	char* geb;
	int temp_result;
	short owner_id;

	if (g_entity_type_table == 0) {
		return 0;
	}
	var_4 = 0;
	geb = gm_SearchStruct();
	temp_result = g_entity_type_table;
	if (geb == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
			0x10cb,
			"gm_AllocGebaeude(): geb overflow HELP !!!!!!",
			1
		);
		return 0;
	}
	gebType = param_1 & 0xff;
	*geb = (char) param_1;
	base = temp_result + gebType * 0x24d;

	sprintf(buf, "----->GebID= %i GebProt= %i", g_next_object_id, gebType);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x10d8, buf, 8);

	*(int*) (geb + 1) = g_next_object_id;
	g_next_object_id = g_next_object_id + 1;
	owner_id = (short) param_2;
	*(short*) (geb + 0x25) = owner_id;
	*(short*) (geb + 0x27) = owner_id;
	*(int*) (geb + 0x3d) = 0x64;
	*(int*) (geb + 0x45) = 0x64;
	geb[0x5c] = 0x64;
	{
		int* state_ptr = (int*) (geb + 0x99);
		*(short*) (geb + 0x29) = 0;
		*(int*) (geb + 0x2b) = 0;
		geb[0x2f] = 0;
		*(int*) (geb + 0x5d) = 0;
		*(int*) (geb + 0x61) = 0;
		*(int*) (geb + 0x30) = 0;
		*(int*) (geb + 0x39) = 0x7d00;
		*(int*) (geb + 0x41) = 2;
		*(int*) (geb + 0x49) = 0x3f800000;
		*(int*) (geb + 0x95) = -1;
		*state_ptr = 0;
		*(int*) (geb + 0x9d) = 0;
		*(int*) (geb + 0xa1) = 0;
		*(int*) (geb + 0xa5) = -1;
		*state_ptr = *state_ptr | 1;
	}
	pDest = geb + 0x65;
	memset(pDest, 0, 0x30);
	param_1 = 0;
	{
		unsigned short* comp_iter = (unsigned short*) (base + 0x23);
		do {
			unsigned short comp_entry = *comp_iter;
			if (comp_entry == 0) {
				break;
			}
			if (comp_entry != 0xffff) {
				unsigned int item_index = comp_entry & 0x7fff;
				char item_class = *(char*) (g_item_def_table + item_index * 0x41);
				if (item_class == '\x02' || item_class == '\x06') {
					var_4 = 1;
				}
				if ((comp_entry & 0x8000) != 0) {
					if (item_class == '\x02' || item_class == '\x06') {
						var_4 = 1;
						gm_AllocBuildingContents(geb, item_index);
					}
					else if (var_4 == 0) {
						gm_AllocObjekt(*(int*) (geb + 1), item_index, 1);
					}
				}
			}
			comp_iter = comp_iter + 1;
			param_1 = param_1 + 1;
		} while (param_1 < 0x40);
	}
	{
		short* product_iter = (short*) gm_StartEntityQuery(*(int*) (geb + 0x5d), 1, 4, 2);
		while (product_iter != 0) {
			if (*product_iter != 0xfd) {
				*(short*) (geb + 0x29) = *product_iter;
				break;
			}
			product_iter = gm_NextEntityQueryMatch();
		}
	}
	{
		unsigned short* setup_result = gm_SetupEntityQuery(geb);
		if (setup_result != 0) {
			*(short*) (geb + 0x29) = *(short*) setup_result;
		}
	}
	temp_result = gm_CheckEntityType(geb);
	if (temp_result != 0) {
		*(int*) (geb + 0x30) = 0x1388;
	}
	if (gebType - 4 < 0x4a) {
		switch (gebType) {
		case 4:
		case 5:
		case 6:
		case 7:
			*(int*) (geb + 0x69) = g_current_year;
			*(int*) (geb + 0x6d) = g_10035884;
			*(int*) (geb + 0x71) = g_10035888;
			*(short*) (geb + 0x75) = g_1003588c;
			if (owner_id != -1) {
				*(int*) (geb + 0x65) = *(int*) ((unsigned short) param_2 * 0x21c + 0x100358a4);
				break;
			}
			/* fall through */
		case 11:
		case 12:
		case 13:
			*(int*) (geb + 0x65) = -1;
			break;
		case 14:
		case 15:
		case 16:
			*(int*) (geb + 0x65) = 10;
			*(int*) (geb + 0x69) = 3;
			*(int*) (geb + 0x6d) = 5;
			break;
		case 20:
		case 21:
		case 22:
			temp_result = (int) gm_AllocObjekt(*(int*) (geb + 1), 0x1b5, 1);
			if (temp_result != 0) {
				*(char*) (temp_result + 0x22) = 0;
				*(char*) (temp_result + 0x1c) = (char) 0xff;
				*(char*) (temp_result + 0x1d) = (char) 0xff;
				*(int*) (temp_result + 0x1e) = -1;
			}
			break;
		case 30: {
			unsigned int plant_map;
			plant_map = (unsigned int) m_AllocTracked(0x600, "f3_gm:PlantMap");
			*(unsigned int*) (geb + 0x71) = plant_map;
			temp_result = 0;
			do {
				temp_result = temp_result + 0x18;
				*(char*) (temp_result + 0xd + *(int*) (geb + 0x71)) = (char) 0xff;
				*(int*) (temp_result + 0x14 + *(int*) (geb + 0x71)) = 0;
			} while (temp_result < 0x600);
		}
			/* fall through */
		case 31:
		case 32:
			*(int*) (geb + 0x30) = 100;
			*(int*) (geb + 0x49) = 0x3f4ccccd;
			break;
		case 53:
		case 54:
		case 55:
			*(int*) (geb + 0x65) = 0;
			*(short*) (geb + 0x69) = 0;
			*(short*) (geb + 0x6b) = 0;
			*(int*) (geb + 0x6d) = 0;
			break;
		case 71:
			*(int*) (geb + 0x30) = 0x13880;
			break;
		case 72:
		case 73:
		case 74:
			temp_result = AllocGraveyardField(geb);
			*(int*) (geb + 0x65) = temp_result;
			SpawnGraveyardEntities(geb, 3);
			break;
		case 75:
		case 76:
		case 77: {
			int* ahm_block = (int*) m_AllocTracked(0x3c, "AHM_INFO");
			*(int*) (geb + 0x65) = (int) ahm_block;
			*ahm_block = -1;
			break;
		}
		default:
			break;
		}
	}
	if (*geb == 0x26) {
		*(short*) (geb + 0x29) = 0x10e;
	}
	gm_SetBuildingWorkerLimits(geb);
	gm_GetBuildingTypeCategory(*(unsigned char*) geb);
	gm_AllocBuildingDefaults(geb);
	return geb;
}

/* Sets up an entity query with specific parameters. Configures
 * the query state machine for iterating filtered results. */

// FUNCTION: SERVER 0x10017910
// gm_SetupEntityQuery

unsigned short* __cdecl gm_SetupEntityQuery(unsigned char* param_1)
{
	char* building;
	int result;
	unsigned short* p;

	gm_GetBuildingTypeCategory((int) *param_1);
	building = (char*) (DAT_100a8c30 + (unsigned int) *param_1 * 0x24d);
	result = gm_CheckEntityType(param_1);
	if (result != 0) {
		return (unsigned short*) gm_StartEntityQuery(*(int*) (param_1 + 0x5d), 1, 0, 0xfd);
	}
	if (*building == 4) {
		return (unsigned short*) gm_StartEntityQuery(*(int*) (param_1 + 0x5d), 1, 0, 0x54);
	}
	p = (unsigned short*) gm_StartEntityQuery(*(int*) (param_1 + 0x5d), 1, 4, 2);
	while (p != (unsigned short*) 0 && *p == 0xfd) {
		p = gm_NextEntityQueryMatch();
	}
	return p;
}

/* Returns the category of a building type. Maps a building
 * type ID to its category (production, storage, service, etc.). */

// FUNCTION: SERVER 0x100179b0
// gm_GetBuildingTypeCategory

int __cdecl gm_GetBuildingTypeCategory(int param_1)
{
	switch (*(unsigned char*) (DAT_100a8c30 + param_1 * 0x24d)) {
	case 0xb:
	case 0xc:
	case 0xd:
		return 2;
	case 0x13:
		return 7;
	case 4:
	case 5:
	case 9:
		return 8;
	case 8:
	case 0xe:
	case 0x12:
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x1d:
	case 0x1f:
	case 0x20:
		return 1;
	case 1:
	case 3:
	case 6:
	case 0xf:
		return 3;
	case 7:
		return 4;
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x1a:
		return 5;
	case 2:
	case 0x1e:
		return 6;
	case 0x21:
		return 9;
	default:
		return 0;
	}
}

/* Searches a specific entity table (type 0x67) for a matching
 * entry. Used for specialized entity lookups. */

// FUNCTION: SERVER 0x10017A70
// gm_SearchTable67

void* __cdecl gm_SearchTable67(int id)
{
	char* p;
	int i;

	i = 0;
	p = g_table_a9;
	for (; i < 256; i++, p += 0xa9) {
		if (*(char*) p == 0) {
			continue;
		}
		if (*(int*) (p + 1) != id) {
			continue;
		}
		return (void*) (g_table_a9 + i * 0xa9);
	}
	return 0;
}

/* Checks if an entity's type matches the expected class.
 * Returns non-zero if the entity type field matches. */

// FUNCTION: SERVER 0x10017AB0
// gm_CheckEntityType

int __cdecl gm_CheckEntityType(unsigned char* entity_ptr)
{
	__asm {
		mov eax, dword ptr [esp + 4]
		test eax, eax
		jne L_nonnull
		ret

	L_nonnull:
		xor ecx, ecx
		mov edx, dword ptr [DAT_100a8c30]
		mov cl, byte ptr [eax]
		add edx, ecx
		lea eax, [ecx + ecx * 2]
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax * 2]
		lea eax, [edx + eax * 4]
		mov al, byte ptr [eax]
		cmp al, 0x0b
		je L_true
		cmp al, 0x0d
		je L_true
		cmp al, 0x0c
		je L_true
		cmp al, 0x10
		je L_true
		cmp al, 0x1c
		je L_true
		cmp al, 0x1d
		je L_true
		cmp al, 0x1f
		je L_true
		xor eax, eax
		ret

	L_true:
		mov eax, 1
		ret
	}
}

/* Assigns a building owner. Updates the building's owner
 * field and maintains the owner-to-building linkage in
 * both directions. */

// FUNCTION: SERVER 0x10017b00
// gm_AssignBuildingOwner

#define PTR_10035A10(idx) (*(unsigned char***) (((idx) * 0x21c) + 0x10035a10))
#define BYTE_100358A2(idx) (*(unsigned char*) (((idx) * 0x21c) + 0x100358a2))
#define DWORD_100358A4(idx) (*(unsigned int*) (((idx) * 0x21c) + 0x100358a4))

void __cdecl gm_AssignBuildingOwner(unsigned char* param_1, unsigned short param_2, unsigned int param_3)
{
	char building_class;
	unsigned short prev_owner;
	unsigned char* owner_building;
	int loop_count;
	unsigned short* obj_iter;
	char* type_entry;
	int owner_index;

	type_entry = dword_100a8c30 + *param_1 * 0x24d;
	*(unsigned short*) (param_1 + 0x25) = param_2;
	if (param_3 != 0xffff) {
		prev_owner = *(unsigned short*) (param_1 + 0x27);
		if ((prev_owner != 0xffff) && (PTR_10035A10(prev_owner) == (unsigned char**) param_1)) {
			PTR_10035A10(prev_owner) = 0;
		}
		*(unsigned short*) (param_1 + 0x27) = (unsigned short) param_3;
		if (*type_entry == '\x02') {
			owner_building = (unsigned char*) PTR_10035A10(param_3 & 0xffff);
			if ((owner_building == 0) || (*owner_building <= *param_1)) {
				PTR_10035A10(param_3 & 0xffff) = (unsigned char**) param_1;
			}
		}
		owner_index = param_3;
		if (((BYTE_100358A2(owner_index) == '\x06') || (BYTE_100358A2(owner_index) == '\a')) &&
			(loop_count = (int) gm_GetMsgField((int) param_1), loop_count != 0)) {
			*(unsigned char*) (loop_count + 0x165) = 0;
			*(unsigned int*) (loop_count + 0x1b4) = *(unsigned int*) (loop_count + 0x1b4) & 0xfffffffe;
			building_class = *type_entry;
			if ((building_class == '\x05') || (building_class == '\t')) {
				*(unsigned int*) (loop_count + 0x16c) = 0;
			}
		}
		loop_count = 0x5008;
		obj_iter = (unsigned short*) dword_100a8c34;
		do {
			if (((*(unsigned short*) obj_iter != 0) &&
				 (*(dword_101de450 + *(unsigned short*) obj_iter * 0x41) == '\x1d')) &&
				(*(unsigned int*) ((unsigned char*) obj_iter + 0x1c) == *(unsigned int*) (param_1 + 1))) {
				*(unsigned int*) ((unsigned char*) obj_iter + 0xa) = DWORD_100358A4(owner_index);
				if (*(unsigned int*) ((unsigned char*) obj_iter + 0x14) != 0) {
					*(unsigned int*) (*(unsigned int*) ((unsigned char*) obj_iter + 0x14) + 0xa) =
						DWORD_100358A4(owner_index);
				}
			}
			obj_iter = (unsigned short*) ((unsigned char*) obj_iter + 0x43);
			loop_count = loop_count - 1;
		} while (loop_count != 0);
	}
}

/* Allocates building contents (workers, inventory items).
 * Populates a building's slots with initial entities based
 * on the building type definition. */

// FUNCTION: SERVER 0x10017c40
// gm_AllocBuildingContents

int __cdecl gm_AllocBuildingContents(char* geb, int obj_id)
{
	char* obj;
	char* type_entry;
	unsigned int btype;
	int slot_idx;
	unsigned short slot_val;
	unsigned int item_index;
	char item_class;
	char* query;
	unsigned char limit_val;
	unsigned short obj_type;
	unsigned int season;
	char* season_base;
	char* cart_obj;
	char* goods_iter;
	char* slot_iter;
	int goods_count;

	if (g_item_def_table == 0) {
		return 0;
	}
	if (g_entity_type_table == 0) {
		return 0;
	}
	if (g_object_count + 0x40 >= 0x5008) {
		return 0;
	}

	obj = gm_AllocObjekt(*(int*) (geb + 1), obj_id, 1);

	btype = *(unsigned char*) geb;
	type_entry = (char*) (g_entity_type_table + btype + btype * 0x24c);

	/* scan component table at type_entry+0x23 to find slot matching obj_id */
	slot_idx = 0;
	if ((*(unsigned short*) (type_entry + 0x23) & 0x7fff) != (unsigned short) obj_id) {
		do {
			slot_idx = slot_idx + 1;
		} while ((*(unsigned short*) (type_entry + 0x23 + slot_idx * 2 + 2) & 0x7fff) != (unsigned short) obj_id);
	}
	slot_idx = slot_idx + 1;

	/* process remaining slots in the component table */
	if (slot_idx < 0x40) {
		do {
			slot_val = *(unsigned short*) (type_entry + 0x23 + slot_idx * 2);
			if (slot_val == 0) {
				break;
			}
			if (slot_val != 0xffff) {
				item_index = slot_val & 0x7fff;
				item_class = *(char*) (g_item_def_table + item_index * 0x41);
				if (item_class == '\x02' || item_class == '\x06') {
					slot_idx = 0x40;
				}
				else if ((slot_val & 0x8000) != 0) {
					gm_AllocObjekt(*(int*) (obj + 2), item_index, 1);
				}
			}
			slot_idx = slot_idx + 1;
		} while (slot_idx < 0x40);
	}

	/* first entity query: worker type 0x2a */
	query = (char*) gm_StartEntityQuery(*(int*) (obj + 0x14), 1, 0, 0x2a);
	if (query != (char*) 0) {
		*(int*) (query + 0x0e) = 2;
		*(int*) (query + 0x06) = *(int*) (geb + 1);
		limit_val = *(unsigned char*) (type_entry + 0x23d);
		if (limit_val == 0 && *(unsigned char*) (type_entry + 0x23e) == 0 &&
			*(unsigned char*) (type_entry + 0x23f) != 0) {
			*(unsigned char*) (query + 0x1c) = *(unsigned char*) (type_entry + 0x23f);
		}
		else {
			if (limit_val < 2) {
				limit_val = 2;
			}
			*(unsigned char*) (query + 0x1c) = limit_val;
			limit_val = *(unsigned char*) (type_entry + 0x23e);
			if (limit_val < 2) {
				limit_val = 2;
			}
			*(unsigned char*) (query + 0x1d) = limit_val;
		}
	}

	/* second entity query: merchant type 0x116 */
	query = (char*) gm_StartEntityQuery(*(int*) (obj + 0x14), 2, 0x116, 0, 6);
	if (query != (char*) 0) {
		*(int*) (query + 0x0e) = 2;
		*(int*) (query + 0x06) = *(int*) (obj + 2);
		limit_val = *(unsigned char*) (type_entry + 0x23d);
		if (limit_val == 0 && *(unsigned char*) (type_entry + 0x23e) == 0 &&
			*(unsigned char*) (type_entry + 0x23f) != 0) {
			if (*(unsigned char*) (type_entry + 0x23f) < 6) {
				*(unsigned char*) (query + 0x1c) = 6;
			}
			else {
				*(unsigned char*) (query + 0x1c) = *(unsigned char*) (type_entry + 0x23f);
			}
		}
		else {
			if (limit_val < 6) {
				limit_val = 6;
			}
			*(unsigned char*) (query + 0x1c) = limit_val;
			limit_val = *(unsigned char*) (type_entry + 0x23e);
			if (limit_val < 6) {
				limit_val = 6;
			}
			*(unsigned char*) (query + 0x1d) = limit_val;
		}
	}

	/* market stall check: types 0x92-0x97 or 0x2db */
	obj_type = *(unsigned short*) obj;
	if (!((obj_type >= 0x92 && obj_type <= 0x97) || obj_type == 0x2db)) {
		return (int) obj;
	}

	/* compute seasonal slot array base: season * (16*season + season) * 5 * 8 * 16 ... */
	season = (unsigned int) (unsigned char) g_current_season;
	{
		unsigned int a = (season << 4) + season;
		unsigned int d = a + a * 4;
		unsigned int s = season + d * 8;
		season_base = (char*) (0x1009B770 + (s << 4));
	}

	query = (char*) gm_StartEntityQuery(*(int*) (obj + 0x14), 1, 0x116, 0);
	if (query != (char*) 0) {
		*(unsigned char*) (query + 0x1c) = 0x0c;
		*(unsigned char*) (query + 0x1d) = 0;
		*(int*) (query + 0x0e) = 3;
	}
	else {
		ReportMessage(g_100314b8);
	}

	cart_obj = gm_AllocObjekt(*(int*) (obj + 2), 0xff, 1);
	goods_count = 0;
	goods_iter = (char*) 0x1002DDE0;
	slot_iter = season_base + 4;

	do {
		if (*(unsigned short*) (slot_iter + 0x38) == *(unsigned short*) geb && *(int*) slot_iter != 0) {
			if (goods_count >= 0x10) {
				LogMessageInternal(g_10031004, 0x16a6, g_10031484, 1);
			}
			else {
				gm_AllocObjekt(*(int*) (cart_obj + 2), (unsigned int) *(unsigned short*) goods_iter, 1);
				goods_count = goods_count + 1;
			}
		}
		goods_iter = goods_iter + 0x80;
		slot_iter = slot_iter + 0x80;
	} while (goods_iter < (char*) 0x10030860);

	return (int) obj;
}

/* Wrapper around gm_RemoveObjectByType. Provides a simpler
 * removal interface without filtering. */

// FUNCTION: SERVER 0x10017f30
// gm_RemoveObjectWrapper

int __cdecl gm_RemoveObjectWrapper(int param_1, unsigned int param_2)
{
	int remove_result;

	remove_result = gm_RemoveObjectByType((void**) (param_1 + 0x5d), param_2);
	if (remove_result == -2) {
		return -3;
	}
	return 0;
}

/* Removes a link from an entity. Clears a specific entity
 * reference field, breaking the association. */

// FUNCTION: SERVER 0x10017f60
// gm_RemoveEntityLink

void __cdecl gm_RemoveEntityLink(int param_1)
{
	int parent_entity;

	parent_entity = (int) gm_EntityAccumulate((void*) param_1);
	if (parent_entity != 0) {
		gm_RemoveLinkedNodeById((int*) (parent_entity + 0x5d), *(int*) (param_1 + 2));
	}
}

/* Initializes an entity if it exists. Validates the entity
 * pointer, then sets default field values. No-op on NULL. */

// FUNCTION: SERVER 0x10017f90
// gm_InitEntityIfValid

void __cdecl gm_InitEntityIfValid(short* param_1)
{
	if (param_1 != (short*) 0 && *(unsigned short*) param_1 != 0xFFFF) {
		amt_ClearEntityLinks(param_1);
	}
}

/* EntityStruct — stride 0x21c (540 bytes), 768 entries at g_entity_array (0x100358a0)
 * Field map derived from EXE cross-reference (Europa1400Gold_TL.exe):
 *   +0x00 (2)  entity_index      Self-index in array (0xFFFF = free slot)
 *   +0x02 (1)  entity_state      0x0F = dead/free, 0x06/0x07 = active types
 *   +0x04 (4)  entity_id         Unique ID from g_next_object_id
 *   +0x08 (1)  health            Init 100 (0x64)
 *   +0x09 (1)  gender
 *   +0x0A (2)  profession_type
 *   +0x0D (1)  is_active         Init 1
 *   +0x10 (4)  pos_x             float
 *   +0x14 (4)  pos_y             float
 *   +0x18 (4)  pos_z             float
 *   +0x1C (4)  scale             float (init 1000.0)
 *   +0x20 (4)  rotation          float
 *   +0x25 (2)  owner_index
 *   +0x27 (2)  parent_index      Used in gm_ResolveParentEntity
 *   +0x28 (2)  season_born       Set to g_current_year on alloc
 *   +0x50 (2)  max_hp            Init 0x7FFF
 *   +0x5C (32) ref_table[8]      Reference IDs (init -1)
 *   +0x80 (5)  name              Random chars on alloc
 *   +0x88 (168) stats_block      Skills/attributes
 *   +0x164(1)  age
 *   +0x16C(4)  home_building
 *   +0x170(4)  current_building
 *   +0x178(1)  linked_list_head  Free list for gm_FreeObjectListRecursive
 *   +0x18C(4)  target_id         Init -1
 *   +0x190(4)  ai_state          Init 4
 *   +0x1CC(4)  entity_flags      Bitfield
 *   +0x1E4(4)  move_speed        Init 1.0f (0x3F800000)
 *   +0x1F0(4)  quest_state
 *   +0x20C(4)  cutscene_id       Used in check_cutscene_ready
 *   +0x210(4)  patrol_target     Init -1
 */
struct EntityStruct {
	unsigned short word0; /* +0x00: entity_index */
	unsigned char byte2;  /* +0x02: entity_state */
	unsigned char pad3;
	int id;     /* +0x04: entity_id (g_next_object_id) */
	char byte8; /* +0x08: health */
	char pad9[0x28 - 9];
	unsigned short word28; /* +0x28: season_born */
	char pad2a[0x5c - 0x2a];
	int table5c[8]; /* +0x5C: ref_table (init -1) */
	char pad7c[0x178 - 0x7c];
	char field178; /* +0x178: linked_list_head */
	char pad179[0x21c - 0x179];
};

// DATA: SERVER 0x10035880
extern unsigned short g_something_1[1];
// DATA: SERVER 0x10035434
extern int g_citizen_count;
// DATA: SERVER 0x1009acfc
extern int g_some_limit;
// DATA: SERVER 0x100358fc
extern int g_entity_ref_table[1];

// DATA: SERVER 0x10031500
extern char g_str_10031500[];
// DATA: SERVER 0x10031538
extern char g_str_10031538[];

/* Deallocates an entity completely. Frees all linked objects,
 * removes from entity tables, and releases memory. */

// FUNCTION: SERVER 0x10017fb0
// gm_DeallocEntity
void __cdecl gm_DeallocEntity(unsigned int index, int param_2)
{
	struct EntityStruct* ent;
	int old_id;
	char buffer[512];

	ent = (struct EntityStruct*) (g_entity_array + index * 0x21c);
	old_id = ent->id;

	if (ent->byte2 == 0xF) {
		/* do nothing */
	}
	else {
		ent->byte8 = 0;
		ent->word28 = g_something_1[0];
		gm_InitEntityIfValid(ent);
		ent->byte2 = 0xF;
	}
	gm_FreeObjectListRecursive((char**) &ent->field178);

	if (param_2 == 0) {
		sprintf(buffer, g_str_10031500, old_id);
		return;
	}

	if (ent->word0 != 0xFFFF) {
		g_citizen_count--;
	}

	{
		int* ptr = g_entity_ref_table;
		while ((char*) ptr < (char*) &g_some_limit) {
			int i;
			for (i = 0; i < 8; i++) {
				if (ptr[i] == ent->id) {
					ptr[i] = -1;
				}
			}
			ptr = (int*) ((char*) ptr + 0x21c);
		}
	}

	memset(ent, 0, 0x21c);
	ent->word0 = 0xFFFF;
	ent->id = -1;
	{
		int i;
		for (i = 0; i < 8; i++) {
			ent->table5c[i] = -1;
		}
	}

	if (param_2 == 1) {
		sprintf(buffer, g_str_10031538, old_id);
	}
}

/* Initializes entity slots to default/empty values. Zeros
 * link fields and sets capacity counters. */

// FUNCTION: SERVER 0x100180D0
// gm_InitEntitySlots

void __cdecl gm_InitEntitySlots(void)
{
	int i;
	char* ptr;

	for (i = 0; i < 0x300; i++) {
		gm_DeallocEntity(i, 2);
	}

	ptr = g_entity_base;
	do {
		memset(ptr, 0, 0xAC);
		*(short*) ptr = (short) 0xFFFF;
		ptr = ptr + 0xAC;
	} while ((int) ptr < (int) g_entity_end);

	DAT_10035434 = 0;
	DAT_1003542c = 0;
	DAT_10035430 = 0;
}

/* Checks if a value is within a range [min, max]. Returns
 * non-zero if within bounds. */

// FUNCTION: SERVER 0x10018130
// gm_IsInRange

int __cdecl gm_IsInRange(int x)
{
	int r;
	r = gm_GetBuildingTypeCategory(x);
	if (r >= 10 && r <= 14) {
		return 0;
	}
	return 2;
}

/* Checks if an entity type is of a specific class. Returns
 * non-zero if the type matches the expected entity class. */

// FUNCTION: SERVER 0x10018150
// gm_EntityClassCheck
int __cdecl gm_EntityClassCheck(int type)
{
	switch (type) {
	case 5:
	case 6:
	case 13:
	case 14:
	case 25:
	case 26:
		return 2;
	case 1:
	case 2:
	case 3:
	case 4:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
	case 22:
	case 23:
	case 24:
		return 0;
	default:
		return 2;
	}
}

/* Checks if an entity's stat is at or above a threshold.
 * Used for skill/ability requirement checks. */

// FUNCTION: SERVER 0x100181a0
// gm_CheckStatLevel

// DATA: SERVER 0x10035a04
extern unsigned char g_entity_type_bytes[];

// DATA: SERVER 0x100358a0

int __cdecl gm_CheckStatLevel(int param_1, int param_2)
{
	int idx;
	int val;
	int result;

	idx = param_1 * 0x21c;
	val = gm_MapEntityStatRange((int) g_entity_type_bytes[idx]);
	if (val == param_2) {
		return (unsigned int) g_entity_type_bytes[idx];
	}
	result = (int) gm_GetEntityTableEntry(g_entity_array + idx);
	if (result == 0) {
		return 0;
	}
	return (unsigned int) *(unsigned char*) (result + 0x74 + param_2);
}

/* Maps and clamps an entity stat value to a valid range.
 * Applies min/max bounds and any stat modifiers. */

// FUNCTION: SERVER 0x10018200
// gm_MapEntityStatRange

int __cdecl gm_MapEntityStatRange(int param_1)
{
	switch (param_1) {
	case 0:
		return 0;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		return 0xb;
	case 7:
	case 8:
	case 9:
	case 10:
	case 0xb:
	case 0xc:
		return 9;
	case 0xd:
	case 0xe:
	case 0xf:
	case 0x10:
	case 0x11:
	case 0x12:
		return 7;
	case 0x13:
	case 0x14:
	case 0x15:
	case 0x16:
	case 0x17:
	case 0x18:
		return 6;
	case 0x19:
	case 0x1a:
	case 0x1b:
	case 0x1c:
	case 0x1d:
	case 0x1e:
		return 8;
	case 0x1f:
	case 0x20:
	case 0x21:
		return 0x10;
	case 0x22:
	case 0x23:
	case 0x24:
	case 0x25:
	case 0x26:
	case 0x27:
		return 5;
	case 0x28:
	case 0x29:
	case 0x2a:
	case 0x2b:
	case 0x2c:
	case 0x2d:
		return 0xc;
	case 0x2e:
	case 0x2f:
	case 0x30:
	case 0x31:
	case 0x32:
	case 0x33:
		return 1;
	case 0x34:
	case 0x35:
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
		return 10;
	case 0x3a:
	case 0x3b:
	case 0x3c:
	case 0x3d:
	case 0x3e:
	case 0x3f:
		return 2;
	case 0x40:
	case 0x41:
	case 0x42:
	case 0x43:
	case 0x44:
	case 0x45:
		return 3;
	case 0x46:
	case 0x47:
	case 0x48:
	case 0x49:
	case 0x4a:
	case 0x4b:
		return 4;
	case 0x4c:
	case 0x4d:
	case 0x4e:
	case 0x4f:
	case 0x50:
	case 0x51:
		return 0xd;
	case 0x59:
	case 0x5a:
	case 0x5b:
	case 0x5c:
	case 0x5d:
	case 0x5e:
		return 0xf;
	case 0x53:
	case 0x54:
	case 0x55:
	case 0x56:
	case 0x57:
	case 0x58:
		return 0xe;
	default:
		return 0;
	}
}

/* Returns the opposite stat index for paired stats.
 * E.g., maps strength to weakness, charisma to shyness.
 * Used for character stat balancing. */

// FUNCTION: SERVER 0x10018330
// gm_GetOppositeStatIndex

/*
 * Mirrors/reverses the position of an index within its group of 6.
 * Each group of 6 consecutive values gets its position flipped:
 *   groupStart -> groupStart+5, groupStart+1 -> groupStart+4, etc.
 * Returns 0 if the index doesn't belong to any known group.
 */
int __cdecl gm_GetOppositeStatIndex(int param_1)
{
	int result;

	result = 0;

	/* Group 1-6 (section A, row 1) */
	if ((param_1 >= 1) && (param_1 <= 6)) {
		return 7 - param_1;
	}
	/* Group 7-12 (section A, row 2) */
	if ((param_1 >= 7) && (param_1 <= 12)) {
		return 13 - param_1;
	}
	/* Group 34-39 (section B, row 1) */
	if ((param_1 >= 34) && (param_1 <= 39)) {
		return 40 - param_1;
	}
	/* Group 40-45 (section B, row 2) */
	if ((param_1 >= 40) && (param_1 <= 45)) {
		return 46 - param_1;
	}
	/* Group 46-51 (section B, row 3) */
	if ((param_1 >= 46) && (param_1 <= 51)) {
		return 52 - param_1;
	}
	/* Group 58-63 (section B, row 5) */
	if ((param_1 >= 58) && (param_1 <= 63)) {
		return 64 - param_1;
	}
	/* Group 64-69 (section B, row 6) */
	if ((param_1 >= 64) && (param_1 <= 69)) {
		return 70 - param_1;
	}
	/* Group 70-75 (section B, row 7) */
	if ((param_1 >= 70) && (param_1 <= 75)) {
		return 76 - param_1;
	}
	/* Group 13-18 (section A, row 3) */
	if ((param_1 >= 13) && (param_1 <= 18)) {
		return 19 - param_1;
	}
	/* Group 52-57 (section B, row 4) */
	if ((param_1 >= 52) && (param_1 <= 57)) {
		return 58 - param_1;
	}
	/* Group 25-30 (section A, row 5) */
	if ((param_1 >= 25) && (param_1 <= 30)) {
		return 31 - param_1;
	}
	/* Group 19-24 (section A, row 4) */
	if ((param_1 >= 19) && (param_1 <= 24)) {
		return 25 - param_1;
	}
	/* Group 76-81 (section C, row 1) */
	if ((param_1 >= 76) && (param_1 <= 81)) {
		return 82 - param_1;
	}
	/* Group 89-94 (section C, row 3) */
	if ((param_1 >= 89) && (param_1 <= 94)) {
		return 95 - param_1;
	}
	/* Group 83-88 (section C, row 2) */
	if ((param_1 >= 83) && (param_1 <= 88)) {
		result = 89 - param_1;
	}
	return result;
}

/* Generates a random stat modifier. Produces a random
 * delta value for stat variation during entity creation
 * or level-up events. */

// FUNCTION: SERVER 0x10018450
// gm_RandomStatModifier

char __cdecl gm_RandomStatModifier(char stat_value)
{
	unsigned short range;
	int masked;

	if (stat_value == 0) {
		return (char) (gm_RandomMod(0x2a) + 0x15);
	}

	masked = (int) stat_value & 0xFF;
	if ((float) masked >= DAT_100257bc) {
		range = 0xb;
	}
	else {
		range = 6;
	}

	return (char) (stat_value + (short) gm_RandomMod(range));
}

/* Looks up an entity record by its integer ID. Searches
 * the global entity table and returns a pointer to the
 * matching entity, or 0 if not found. */

// FUNCTION: SERVER 0x100184A0
// gm_LookupEntityRecordById
int __cdecl gm_LookupEntityRecordById(int search_id)
{
	char* p;
	int i;
	i = 0;
	p = (char*) 0x100358A4;
	while ((int) p < (int) 0x1009ACA4) {
		if (*(unsigned short*) (p - 4) != 0xFFFF) {
			if (*(int*) p == search_id) {
				return i * 0x21C + 0x100358A0;
			}
		}
		p += 0x21C;
		i++;
	}
	return 0;
}

/* Gets a pointer to an entity's type table entry.
 * Indexes into g_entity_type_table by the entity's type byte. */

// FUNCTION: SERVER 0x100184e0
// gm_GetEntityTableEntry

short* __cdecl gm_GetEntityTableEntry(char* param)
{
	char type;
	int table_index;

	type = param[2];
	if (type == 6 || type == 7 || type == 5) {
		if ((*(unsigned short*) (param + 0x50) & 0x8000) != 0) {
			table_index = *(unsigned short*) (param + 0x50) & 0xf;
			if (table_index >= 0 && table_index < 0x10) {
			}
			if (table_index >= 0 && table_index < 0x10) {
				return (short*) (&entity_table[table_index * 0xac]);
			}
		}
	}
	return (short*) 0;
}

/* Implementation of player identity change. Swaps player
 * entity identity between two IDs, updating all back-
 * references in buildings and citizens. */

// FUNCTION: SERVER 0x10018530
// gm_ChangePlayerIdentityImpl

int __cdecl gm_ChangePlayerIdentityImpl(int param_1, int param_2)
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

	record_a = (char*) gm_LookupEntityRecordById(param_1);
	if (record_a == 0) {
		return -1;
	}

	offset_a = 0;
	copy_count = 0x100;
	do {
		inner_loop = offset_a + (int) DAT_1014d8c0;
		if ((*(char*) (offset_a + (int) DAT_1014d8c0) != '\0') &&
			(stat_opposite = gm_GetBuildingTypeCategory((unsigned char) *(char*) (offset_a + (int) DAT_1014d8c0)),
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

	record_b = (char*) gm_LookupEntityRecordById(param_2);
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

		pSrc = (int*) record_b;
		pDst = (int*) buf1;
		for (copy_count = 0x87; copy_count != 0; copy_count--) {
			*pDst = *pSrc;
			pSrc++;
			pDst++;
		}

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
	{
		int* pDst = (int*) buf2;
		int* pSrc = (int*) record_a;
		for (copy_count = 0x87; copy_count != 0; copy_count--) {
			*pDst = *pSrc;
			pSrc++;
			pDst++;
		}
	}
	*(int*) (buf2 + 4) = saved_id;
	*(unsigned short*) buf2 = *(unsigned short*) record_b;
	*(unsigned char*) (buf2 + 2) = 9;

	offset_a = (int) index_a * 0x21c;
	{
		int* pDst = (int*) (offset_a + 0x100358a0);
		int* pSrc = (int*) buf1;
		for (copy_count = 0x87; copy_count != 0; copy_count--) {
			*pDst = *pSrc;
			pSrc++;
			pDst++;
		}
	}

	copy_count = (int) index_b * 0x21c;
	{
		int* pDst = (int*) (copy_count + 0x100358a0);
		int* pSrc = (int*) buf2;
		for (inner_loop = 0x87; inner_loop != 0; inner_loop--) {
			*pDst = *pSrc;
			pSrc++;
			pDst++;
		}
	}

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
			if (*ref_scan == param_1) {
				*ref_scan = param_2;
			}
			else if (*ref_scan == param_2) {
				*ref_scan = param_1;
			}
			ref_scan = ref_scan + 1;
			copy_count = copy_count - 1;
		} while (copy_count != 0);
		outer_scan = (int*) ((char*) outer_scan + 0x21c);
		scan_count = scan_count - 1;
	} while (scan_count != 0);

	for (pNode = *(char**) (buf2 + 0x178); pNode != 0; pNode = *(char**) (pNode + 0x3f)) {
		index_b = *(unsigned short*) pNode;
		if (index_b != 0 && *(DAT_101de450 + (int) index_b * 0x41) == '\t') {
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

// FUNCTION: SERVER 0x10018850
// gm_CreateEntityFromParents

int __cdecl gm_CreateEntityFromParents(int param_1, int param_2, int param_3, int param_4, int param_5)
{
	char work_buf[0x41c];
	int var_10;
	int var_14;
	int var_18;
	int var_1c;
	int var_20;
	int var_24;
	int var_28;

	(void) work_buf;

	var_10 = 0;
	var_14 = 0;
	var_18 = 0;
	var_1c = 0;
	var_20 = 0;
	var_24 = 0;
	var_28 = 0;

	return 0;
}

/* Queries the sum of a specific field across entities
 * matching a filter. Used for aggregate calculations
 * like total production or population counts. */

// FUNCTION: SERVER 0x100196c0
// gm_QueryEntitySum

int __cdecl gm_QueryEntitySum(int param_1, unsigned int param_2)
{
	short* ent;
	int total;

	total = 0;
	ent = gm_StartEntityQuery(param_1, 1, 4, 9);
	if (ent != (short*) 0) {
		do {
			if (*(short*) (entity_slot_table + (param_2 & 0xff) * 0x2f4) == *ent) {
				total = total + *(int*) (ent + 7);
			}
			ent = gm_NextEntityQueryMatch();
		} while (ent != (short*) 0);
	}
	return total;
}

/* Calculates the production value for a building. Sums
 * worker skill, building quality, and recipe bonuses to
 * determine output rate. */

// FUNCTION: SERVER 0x10019720
// gm_CalculateProductionValue

/* Game function - recursive entity value calculation with FPU math */
/* Accesses g_entity_table (0x101de450), calls __ftol and itself recursively */
/* Computes weighted entity stat values with caching in field_0x38 */

double __cdecl gm_CalculateProductionValue(int entity_index, int param2)
{
	char* ent;
	int cached;

	ent = g_entity_table + (entity_index << 6) + entity_index;
	cached = *(int*) (ent + 0x38);

	if (cached != 0) {
		int shifted = cached << 5;
		int masked = param2 & 0xff;
		float result = (float) shifted;
		result *= masked;
		result *= DAT_10025fb8;
		if (*(unsigned char*) (ent + 0x21) == 3) {
			result *= DAT_10025fb4;
		}
		return result;
	}

	{
		unsigned int field_22;
		unsigned short field_36;
		int divisor;
		int idx;
		double base_val;
		float modifier;
		float intermediate;

		field_22 = *(unsigned int*) (ent + 0x22);
		field_36 = *(unsigned short*) (ent + 0x36);
		divisor = (int) field_36 + (field_36 == 0);

		base_val = (double) field_22;
		idx = *(int*) (entity_index * 4 + 0x101dd8e0);
		base_val /= divisor;

		if (idx != 0) {
			char* record;
			int i;

			record = *(char**) 0x100a8c30 + idx * 0x24d;
			modifier = _DAT_100256cc;

			i = 0;
			do {
				int bval = (unsigned char) *(record + i + 0x233);
				modifier += (float) bval * DAT_10025fa8 * (float) DAT_10025fa0;
				i++;
			} while (i < 2);
		}
		else {
			modifier = DAT_100257c8;
		}

		{
			unsigned char entity_type = *(unsigned char*) ent;
			modifier *= (float) DAT_100257d0;
			intermediate = (float) (base_val * modifier);

			if (entity_type == 0x17) {
				return intermediate * DAT_10025fb0;
			}
		}

		{
			float accum;
			int j;
			short* p;
			int p2;

			p2 = param2;
			accum = intermediate;
			p = (short*) (ent + 0x2e);
			j = 0;

			do {
				unsigned short slot = *(unsigned short*) p;
				if (slot == 0) {
					break;
				}
				if (slot != 0xffff) {
					double sub;
					int weight;
					int div36;

					sub = gm_CalculateProductionValue((int) (unsigned short) slot, p2);
					weight = (int) *(unsigned short*) (p - 4);
					div36 = (int) *(unsigned short*) (ent + 0x36);
					sub *= weight;
					sub /= div36;
					accum += (float) sub;
				}
				j++;
				p++;
			} while (j < 4);

			{
				int int_val = (int) (accum * DAT_10025fac);
				int masked = p2 & 0xff;
				*(int*) (ent + 0x38) = int_val;
				return (float) masked * intermediate * DAT_10025fb8 * DAT_10025fb0;
			}
		}
	}
}

/* Sums production values across all buildings of a type.
 * Aggregates daily/weekly output for economic reporting. */

// FUNCTION: SERVER 0x100198b0
// gm_SumBuildingProductionValues

/* Game function - entity query stat accumulator */
/* Iterates entity references in a record, calls gm_CalculateProductionValue for each, accumulates results */

int __cdecl gm_SumBuildingProductionValues(char* obj, int param2)
{
	int running_sum;
	char* record;
	unsigned char idx;
	void* query;
	char have_query;
	int i;
	short* p;

	idx = *(unsigned char*) obj;
	query = 0;

	record = *(char**) 0x100a8c30 + (int) idx * 0x24d;
	running_sum = *(int*) (record + 0x249) * 0xf00;
	have_query = 0;
	i = 0;
	p = (short*) (record + 0x25);

	do {
		unsigned short entry;
		int ent_idx;
		char* ent;

		entry = *(unsigned short*) (p - 1);
		if (entry == 0) {
			break;
		}

		ent_idx = entry & 0x7fff;
		ent = g_entity_table + (ent_idx << 6) + ent_idx;

		if (!have_query) {
			unsigned char type = *(unsigned char*) ent;
			if (type != 2 && type != 6) {
				goto loop_bottom;
			}

			query = gm_StartEntityQuery(*(int*) (obj + 0x5d), 1, 0, ent_idx);
			if (!query) {
				goto loop_bottom;
			}

			running_sum =
				(int) (gm_CalculateProductionValue(*(unsigned short*) query, *(unsigned char*) ((char*) query + 0x12)) +
					   running_sum);

			if (i < 0x3f) {
				unsigned short next_entry = *(unsigned short*) p;
				int next_idx = next_entry & 0x7fff;
				unsigned char next_type = *(unsigned char*) (g_entity_table + (next_idx << 6) + next_idx);
				if (next_type == 2 || next_type == 6) {
					goto loop_bottom;
				}
				have_query = 1;
			}
		}
		else {
			if (!query) {
				goto loop_bottom;
			}

			{
				void* sub_query;
				sub_query = gm_StartEntityQuery(*(int*) ((char*) query + 0x14), 1, 0, ent_idx);
				if (sub_query) {
					running_sum = (int) (gm_CalculateProductionValue(
											 *(unsigned short*) sub_query,
											 *(unsigned char*) ((char*) sub_query + 0x12)
										 ) +
										 running_sum);
				}
			}

			if (i < 0x3f) {
				unsigned short next_entry = *(unsigned short*) p;
				int next_idx = next_entry & 0x7fff;
				unsigned char next_type = *(unsigned char*) (g_entity_table + (next_idx << 6) + next_idx);
				if (next_type == 2 || next_type == 6) {
					have_query = 0;
				}
			}
		}

	loop_bottom:
		i++;
		p++;
	} while (i < 0x40);

	{
		float result = (float) param2;
		result *= DAT_10025fb8;
		result *= running_sum;
		return (int) result;
	}
}

/* Accumulates a typed value (type 2) across entities.
 * Specialized aggregation for specific entity field types. */

// FUNCTION: SERVER 0x10019A20
// gm_AccumulateTyped2

int __cdecl gm_AccumulateTyped2(char* entity)
{
	int sum;
	int result;
	unsigned int idx;
	sum = 0;
	idx = (unsigned char) g_type_idx;
	idx = idx * 189;
	result = (int) gm_StartEntityQuery(*(int*) (entity + 0x178), 1, 0, (int) *(unsigned short*) &g_key_table[idx]);
	if (result) {
		do {
			sum += *(int*) (result + 0xe);
			result = (int) gm_NextEntityQueryMatch();
		} while (result);
	}
	return sum;
}


/* Runs an entity query and sums a field across all results.
 * Combines query iteration with field accumulation. */

// FUNCTION: SERVER 0x10019a70
// gm_EntityQuerySum

int __cdecl gm_EntityQuerySum(int param_1)
{
	int sum;
	char* entity;
	char* sub;

	sum = 0;
	entity = (char*) gm_StartEntityQuery(*(int*) ((char*) param_1 + 0x5d), 2, 0, 0x2a, 6);
	if (entity == (char*) 0) {
		return sum;
	}
	sub = (char*) gm_StartEntityQuery(*(int*) (entity + 0x14), 1, 5);
	if (sub == (char*) 0) {
		return sum;
	}
	do {
		sum =
			(int) (gm_CalculateProductionValue(*(unsigned short*) sub, *(unsigned char*) (sub + 0x12)) + (double) sum);
		sub = (char*) gm_NextEntityQueryMatch();
	} while (sub != (char*) 0);
	return sum;
}

/* Resolves a parent entity reference. Follows entity chain
 * links to find the parent. Returns parent pointer. */

// FUNCTION: SERVER 0x10019ae0
// gm_ResolveParentEntity

short* __cdecl gm_ResolveParentEntity(short* param_1)
{
	void* dynamic_ent;

	gm_ResolveEntityById(&dynamic_ent, (void**) 0, (void**) &param_1, *(int*) (param_1 + 5));
	if (param_1 == (short*) 0) {
		if (dynamic_ent != (void*) 0 && *(unsigned short*) ((int) dynamic_ent + 0x27) != 0xffff) {
			return (short*) (entity_array + (unsigned int) *(unsigned short*) ((int) dynamic_ent + 0x27) * 0x21c);
		}
		param_1 = (short*) 0;
	}
	return param_1;
}

/* Gets the type (class) of an entity as an unsigned short.
 * Reads from the entity's type field. */

// FUNCTION: SERVER 0x10019b40
// gm_GetEntityType

unsigned short __cdecl gm_GetEntityType(short* param_1)
{
	void* dynamic_ent;

	gm_ResolveEntityById(&dynamic_ent, (void**) 0, (void**) &param_1, *(int*) (param_1 + 5));
	if (param_1 != (short*) 0) {
		return *param_1;
	}
	if (dynamic_ent != (void*) 0) {
		return *(unsigned short*) ((int) dynamic_ent + 0x27);
	}
	return (short) 0xffff;
}

/* Walks an entity chain, calling a callback for each node.
 * Traverses linked entity lists for processing. */

// FUNCTION: SERVER 0x10019b80
// gm_WalkEntityChain

int __cdecl gm_EntityAccumulate(void* param_1)
{
	int result;
	int entity_id;
	void* existing_ent;
	void* static_ent;

	entity_id = *(int*) ((int) param_1 + 6);
	while (entity_id != -1) {
		result = gm_ResolveEntityById((void**) &param_1, &static_ent, &existing_ent, entity_id);
		if (result == 0) {
			return 0;
		}
		if (param_1 != (void*) 0) {
			return (int) param_1;
		}
		if (existing_ent != (void*) 0) {
			return 0;
		}
		if (static_ent != (void*) 0) {
			entity_id = *(int*) ((int) static_ent + 6);
		}
	}
	return 0;
}

/* Accumulates values along an entity chain. Walks linked
 * entities and sums a specified field. */

// FUNCTION: SERVER 0x10019BE0
// gm_EntityAccumulate

int __cdecl gm_WalkEntityChain(int raw_idx)
{
	unsigned short idx;
	int slot;
	int ent;
	int total;
	idx = (unsigned short) raw_idx;
	if (idx >= 0x300) {
		return -1;
	}
	slot = (unsigned int) idx * 0x21c + 0x100358a0;
	if (*(unsigned short*) slot == 0xFFFF) {
		return -1;
	}
	total = gm_AccumulateTyped2((char*) slot);
	ent = (int) gm_StartFilteredEntitySearch(1, 3, (int) idx);
	if (ent) {
		do {
			total += gm_SumBuildingProductionValues((char*) ent, (int) *(signed char*) (ent + 0x5c));
			total += gm_EntityQuerySum(ent);
			ent = (int) FindNextFilteredEntity();
		} while (ent);
	}
	return total;
}

/* Finds an entity by its owner. Searches for an entity
 * whose owner field matches the given ID. */

// FUNCTION: SERVER 0x10019c60
// gm_FindEntityByOwner

// DATA: SERVER 0x100358a2
extern unsigned char g_entity_state_base[];
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
int __cdecl gm_RemoveObjectByType(void**, unsigned int);

// DATA: SERVER 0x100358a0

char* __cdecl gm_GetMsgField(int param_1)
{
	unsigned char* p;
	int i;
	unsigned char type;

	if (param_1 == 0) {
		return 0;
	}
	i = 0;
	p = g_entity_state_base;
	do {
		if (p[0x162] != 0 && *(int*) (p + 0x16a) == param_1) {
			type = *p;
			if (type == 6 || type == 7 || type == 1 || type == 2) {
				return g_entity_array + i * 0x21c;
			}
		}
		p += 0x21c;
		i++;
	} while ((int) p < 0x1009aca2);
	return 0;
}

/* Gets a message field from a command packet. Reads a
 * specific field from the packet's payload section. */

// FUNCTION: SERVER 0x10019CD0
// gm_GetMsgField
int __cdecl gm_FindEntityByOwner(char* msg, char* pkt)
{
	unsigned short type;

	type = *(unsigned short*) msg;
	if (type == 0x2a || type == 0x116 || type == 0x1db || type == 0x1dc) {
		return *(int*) (pkt + 0xe) - 1;
	}
	return *(int*) (pkt + 0xe);
}

int __cdecl compute_size(char* pkt)
{
	int iVar1;
	iVar1 = *(int*) (pkt + 0xe);
	if (*(short*) pkt == 0x1dd) {
		return (iVar1 + 2) * 5;
	}
	if (iVar1 == 3) {
		return 0x50;
	}
	return iVar1 * 0x14;
}

/* Checks if an object can be produced (Kann Objekt Hergestellt).
 * Validates recipe requirements, ingredient availability,
 * worker skills, and building capability. */

// FUNCTION: SERVER 0x10019d30
// gm_KannObjektHergestellt

/* Game function - checks production capacity and entity slot availability */

int __cdecl gm_KannObjektHergestellt(char* obj, int entity_index, int requested)
{
	char* ent;
	int category;
	int is_cat2;
	int max_size;
	void* query;
	int used;
	int remaining;
	char* ent_rec;
	int count;
	int is_producer;

	ent = (char*) gm_EntityAccumulate((void*) obj);
	if (!ent) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
			0x31de,
			"gm_KannObjektHergestellt(): pCObjekt==NULL",
			1
		);
		return 0;
	}

	category = gm_GetBuildingTypeCategory((unsigned char) *ent);
	is_cat2 = (category == 2);
	max_size = compute_size(obj);

	query = gm_StartEntityQuery(*(int*) (obj + 0x14), 1, 0, entity_index);
	if (query) {
		used = gm_FindEntityByOwner(obj, query);
		remaining = max_size - used;
		if (remaining > requested) {
			goto return_requested;
		}
		return remaining;
	}

	ent_rec = g_entity_table + (entity_index << 6) + entity_index;

	if (is_cat2) {
		is_producer = (*ent_rec == 0x17);
	}
	else {
		if (*ent_rec == 0x17 || *ent_rec == 0x25) {
			is_producer = 1;
		}
		else {
			is_producer = 0;
		}
	}

	if (*(unsigned short*) obj == 0x2a) {
		count = 0;
		query = gm_StartEntityQuery(*(int*) (obj + 0x14), 1, 5);
		while (query) {
			int result_id;
			char* result_ent;

			result_id = *(unsigned short*) query;
			result_ent = g_entity_table + (result_id << 6) + result_id;

			if (is_cat2) {
				unsigned char t = *result_ent;
				if (is_producer) {
					if (t != 0x17) {
						goto skip_count;
					}
				}
				else {
					if (t == 0x17) {
						goto skip_count;
					}
				}
			}
			else {
				unsigned char t = *result_ent;
				if (is_producer) {
					if (t == 0x17) {
						goto do_count;
					}
					if (t != 0x25) {
						goto skip_count;
					}
				}
				else {
					if (t == 0x17) {
						goto skip_count;
					}
					if (t == 0x25) {
						goto skip_count;
					}
				}
			}
		do_count:
			count++;
		skip_count:
			query = gm_NextEntityQueryMatch();
		}

		if (is_producer) {
			if (count >= (unsigned char) obj[0x1c]) {
				return 0;
			}
		}
		else {
			if (count >= (unsigned char) obj[0x1d]) {
				return 0;
			}
		}
	}
	else {
		count = 0;
		query = gm_StartEntityQuery(*(int*) (obj + 0x14), 1, 5);
		while (query) {
			count++;
			query = gm_NextEntityQueryMatch();
		}
		if (count >= (unsigned char) obj[0x1c]) {
			return 0;
		}
	}

return_requested:
	if (max_size < requested) {
		return max_size;
	}
	return requested;
}

/* Checks inventory capacity. Verifies whether an entity's
 * inventory has room for additional objects of a given type. */

// FUNCTION: SERVER 0x10019ed0
// gm_CheckInventoryCapacity

/* Game function - computes available entity slots (capped at 3) */

int __cdecl gm_CheckInventoryCapacity(char* obj, int entity_index, int requested)
{
	char* table;
	unsigned char entity_type;
	int in_type_list;
	int available;
	int type_table[8];
	void* query;
	int count;

	table = g_entity_table;
	available = 0;
	entity_type = *(table + (entity_index << 6) + entity_index);
	in_type_list = 0;

	type_table[0] = 8;
	type_table[1] = 0xc;
	type_table[2] = 0x12;
	type_table[3] = 0x19;
	type_table[4] = 0x22;
	type_table[5] = 0x20;
	type_table[6] = 0x27;
	type_table[7] = available;

	if (entity_type == 9) {
		return requested;
	}

	{
		unsigned int edx;
		int val;
		int* p;

		edx = (unsigned char) entity_type;
		val = 8;
		p = type_table;

		do {
			if (val == (int) edx) {
				in_type_list = 1;
				break;
			}
			val = *++p;
		} while (val != available);
	}

	if (obj[2] == 6 || obj[2] == 7) {
		if (ahm_LookupEntityInTable(entity_index)) {
			return available;
		}
	}

	if (entity_index == 0x179 || entity_index == 0x17a) {
		return available;
	}

	if (!in_type_list) {
		return available;
	}

	query = gm_StartEntityQuery(*(int*) (obj + 0x178), 1, 0, entity_index);
	if (query) {
		count = *(int*) ((char*) query + 0xe);
		ahm_LookupEntityInTable(entity_index);
		if (count + requested > 3) {
			available = 3 - count;
			return (available < 0) ? 0 : available;
		}
		available = requested;
	}
	else {
		query = gm_StartEntityQuery(*(int*) (obj + 0x178), 1, 5);
		count = 0;
		while (query) {
			int result_id;
			char* result_ent;

			result_id = *(unsigned short*) query;
			result_ent = g_entity_table + (result_id << 6) + result_id;
			if (*result_ent != 9) {
				count++;
			}
			query = gm_NextEntityQueryMatch();
		}
		if (count >= 6) {
			available = 3;
		}
		else {
			available = (requested > 3) ? 3 : requested;
		}
	}

	return (available < 0) ? 0 : available;
}

/* Sets a field value on an entity. Writes a value at the
 * specified offset into the entity structure. */

// FUNCTION: SERVER 0x1001A060
// gm_EntitySetField

void __cdecl gm_EntitySetField(void)
{
	int entity;
	int sub;
	entity = (int) gm_StartFilteredEntitySearch(1, 0, 0x1e);
	if (!entity) {
		return;
	}
	do {
		sub = (int) gm_StartEntityQuery(*(int*) (entity + 0x5d), 1, 0, 0xff);
		if (sub) {
			sub = (int) gm_StartEntityQuery(*(int*) (sub + 0x14), 1, 5);
			if (sub) {
				do {
					if (*(int*) (sub + 0xe) != 2) {
						*(int*) (sub + 0xe) = 2;
					}
				} while ((sub = (int) gm_NextEntityQueryMatch()) != 0);
			}
		}
		entity = (int) FindNextFilteredEntity();
	} while (entity);
}

/* Returns a random integer in [0, max). Uses the game's
 * internal random number generator for deterministic
 * simulation results. */

// FUNCTION: SERVER 0x1001A0D0
// gm_RandomMod

int __cdecl gm_RandomMod(unsigned short n)
{
	if (n) {
		return rand() % n;
	}
	return 0;
}

/* Returns a random float in [0.0, 1.0). Converts the
 * integer RNG output to a normalized float value. */

// FUNCTION: SERVER 0x1001a0f0
// gm_RandomFloat01

double __cdecl gm_RandomFloat01(void)
{
	return (double) rand() * (double) _DAT_10025fbc;
}

/* Returns a random value with quadratic distribution.
 * Produces values biased toward lower numbers. Used for
 * stat rolls and probability curves. */

// FUNCTION: SERVER 0x1001a110
// gm_RandomQuadratic

float __cdecl gm_RandomQuadratic(void)
{
	float rand_val;

	rand_val = (float) gm_RandomFloat01();
	rand_val = (rand_val + rand_val) - _DAT_100256a0;
	if (rand_val < _DAT_100256cc) {
		return _DAT_100256a8 * rand_val * rand_val;
	}
	return _DAT_100256a0 * rand_val * rand_val;
}
