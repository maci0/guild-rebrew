#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct {
typedef int(__cdecl* ALLOCFN)(int, int, int);

#pragma intrinsic(memcpy, memset)

extern void __cdecl LogMessageInternal(char* file, unsigned int line, char* msg, int level);
extern char* g_entity_table; /* 0x101de450 */;
extern void* __cdecl AllocateTrackedHeapBlock(unsigned int size, const char* tag);
extern int __cdecl crt_call_extra(char* filename, char* mode);
extern int __cdecl crt_locked_call4b(void* dest, int elemSize, int count, int stream);
extern void __cdecl gm_InitObjektHersteller(void);
extern void __cdecl InitEntitySlots(void);
extern int __cdecl crt_getid_set(void);
extern char* g_entity_ptr;
extern void __cdecl entity_cleanup(char*);
extern short* DAT_100a8c34;
extern int DAT_10035450;
extern Record* g_records;
extern int __cdecl find_entity_2arg(int, int);
extern void __cdecl cleanup_one(int);
extern int __cdecl get_next_entity(void);
extern void __cdecl free_block(int);
extern int g_data_ptr;
extern int g_data_ptr2;
extern int g_data_ptr3;
extern int g_data_ptr4;
extern char* g_game_initialized;
extern char* DAT_1014d8c0;
extern int DAT_100a8c30;
extern unsigned char DAT_10035439;
extern int DAT_1003543c;
extern char* DAT_101de450;
extern unsigned short* __cdecl StartFilteredEntitySearch(int, ...);
extern unsigned short* __cdecl StartEntityQuery(int, int, int, ...);
extern void* __cdecl FindNextFilteredEntity(void);
extern void* __cdecl NextEntityQueryMatch(void);
extern char* __cdecl AllocGameObject(int, int, int);
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
extern char g_entity_array[];
extern void __cdecl free_node(char*);
extern int __cdecl FreeObjectListRecursive(char**);
extern void __cdecl noop_ret2(void*);
extern char* __cdecl AllocateObjectSlot(void);
extern int __cdecl ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
extern short* __cdecl ResolveParentEntity(short*);
extern int g_item_def_table;
extern int g_next_object_id;
extern int g_object_count;
extern int g_current_year;
extern char s_D__Develop_DieGildeAddOn_game_sp_10031004[];
extern char s_gm_AddObjekt____obj____ob_NULL_10031390[];
extern char s_gm_AddObjekt____Parent_not_found_10031358[];
extern int __cdecl RemoveObjectByType(void** objectListHead, unsigned int objectTypeId);
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
extern void __cdecl FreeTrackedHeapBlock(void* heapBlock);
extern void __cdecl free_3fields(void* param);
extern int DAT_10035a0c;
extern unsigned char DAT_10030861;
extern char* __cdecl search_struct(void);
extern int __cdecl AllocBuildingContents(void);
extern unsigned short* __cdecl SetupEntityQuery(unsigned char*);
extern int __cdecl CheckEntityType(char* geb);
extern int __cdecl AllocGraveyardField(char* geb);
extern void __cdecl SpawnGraveyardEntities(char* geb, int param);
extern void __cdecl SetBuildingWorkerLimits(char* geb);
extern int __cdecl GetBuildingTypeCategory(int);
extern void __cdecl gm_AllocBuildingDefaults(char* geb);
extern char* g_table_a9;
extern char* dword_100a8c30;
extern unsigned short* dword_100a8c34;
extern char* dword_101de450;
extern char* __cdecl FindEntityByOwner(int);
extern void __cdecl ReportMessage(int);
extern int g_entity_type_table;
extern char g_current_season;
extern char g_10031004[];
extern char g_10031484[];
extern char g_100314b8[];
extern int __cdecl WalkEntityChain(int);
extern int __cdecl RemoveLinkedNodeById(int*, int);
extern void __cdecl ClearEntityLinks(short*);
extern void __cdecl InitEntityIfValid(void* param_1);
extern void __cdecl gm_DeallocEntity(int idx, int param);
extern int DAT_10035434;
extern int DAT_1003542c;
extern int DAT_10035430;
extern char g_entity_base[];
extern char g_entity_end[];
extern int __cdecl classify(int);
extern int __cdecl MapEntityStatRange(int);
extern short* __cdecl GetEntityTableEntry(char*);
extern float DAT_100257bc;
extern int __cdecl random_mod(int range);
extern char entity_table[];
extern int __cdecl LookupEntityRecordById(int);
extern void __cdecl AssignBuildingOwner(char*, unsigned short, unsigned short);
extern int __cdecl entity_accumulate(int);
extern int __cdecl CheckStatLevel(int, int);
extern int __cdecl GetOppositeStatIndex(int);
extern void* __cdecl AddOrAccumulateObject(int, int, int);
extern int g_citizen_count;
extern char entity_slot_table[];
extern float DAT_10025fb8; /* 0x10025fb8 */;
extern float DAT_10025fb4; /* 0x10025fb4 */;
extern float DAT_10025fb0; /* 0x10025fb0 */;
extern float DAT_10025fac; /* 0x10025fac */;
extern float DAT_10025fa8; /* 0x10025fa8 */;
extern double DAT_10025fa0; /* 0x10025fa0 */;
extern float _DAT_100256cc; /* 0x100256cc */;
extern float DAT_100257c8; /* 0x100257c8 */;
extern double DAT_100257d0; /* 0x100257d0 */;
extern double __cdecl CalculateProductionValue(unsigned short, unsigned char);
extern int __cdecl func_1001b564(void);
extern char g_type_idx;
extern int __cdecl find_entity(int, int, int, int);
extern int g_key_table[];
extern char entity_array[];
extern int __cdecl compute_slot_val(int);
extern int __cdecl find_entity_3arg(int, int, int);
extern int __cdecl compute_entity_val(int, int);
extern int __cdecl another_entity_val(int);
extern int __cdecl compute_size(char*, int); /* 0x10019d00 */;
extern int __cdecl get_msg_field(char*, void*); /* 0x10019cd0 */;
extern int __cdecl LookupEntityInTable(int); /* 0x1000c670 */;
extern int __cdecl search_entity(int, int, int);
extern int __cdecl search_sub(int, int, int, int);
extern int __cdecl search_sub3(int, int, int);
extern int __cdecl get_next_sub(void);
extern int __cdecl get_next_outer(void);
extern int __cdecl rand_gen(void);
extern float _DAT_10025fbc;
extern double __cdecl RandomFloat01(void);
extern float _DAT_100256a0;
extern float _DAT_100256a8;

	char pad[0x24];
	int(__cdecl* func)(int, int);
	int field_28;
} DISPATCH_OBJ;

#pragma pack(push, 1)
	short active;
	int id;
	char pad[0x3d];
} Record;
#pragma pack(pop)

;
;
;
;
;
;
;
;
;
;
;
;
;

// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 320
// SYMBOL: _alloc_and_init
// FUNCTION: SERVER 0x10004B80
// alloc_and_init

void* __cdecl alloc_and_init(char a, char b, int c, int d, char* ctx)
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

// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 20
// SYMBOL: _dispatch_call
// FUNCTION: SERVER 0x10005370
// dispatch_call

int __cdecl dispatch_call(int param, DISPATCH_OBJ* obj)
{
	return obj->func(obj->field_28, param);
}

// ORIGIN: GAME
// STATUS: MATCHING
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, zero-extend pattern (xor vs mov)
// SIZE: 642
// SYMBOL: _gm_InitObjektHersteller
// FUNCTION: SERVER 0x100156c0
// gm_InitObjektHersteller

/* Game function - gm_InitObjektHersteller (initialize object manufacturers) */
// BLOCKER_DELTA: 575
// GHIDRA: InitProductionTable

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

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap
// SIZE: 861
// SYMBOL: _Open
// BLOCKER_DELTA: 333
// GHIDRA: InitGameWorld
// ANALYSIS: InitGameWorld: Allocates and loads building prototypes from A_Geb.dat (88 entries x 0x24D stride), object prototypes from A_Obj.dat (732 entries x 0x41 stride). Zeroes dynamic/existing entity arrays, initializes player slot templates, sets up production table. Counts producible objects per building prototype. Returns 0 on success, negative error codes on failure.
// FUNCTION: SERVER 0x10015950
// Open

/* GLOBAL: SERVER 0x100a8c30 */
extern int g_entity_type_table;
/* GLOBAL: SERVER 0x1014d8c0 */
extern int g_1014d8c0;
/* GLOBAL: SERVER 0x101de450 */
extern int g_item_def_table;
/* GLOBAL: SERVER 0x100a8c34 */
extern int g_100a8c34;

/* GLOBAL: SERVER 0x100a8cf8 */
extern int g_100a8cf8;
/* GLOBAL: SERVER 0x1009b764 */
extern int g_1009b764;
/* GLOBAL: SERVER 0x1002dde0 */
extern int g_1002dde0;

int __cdecl Open(int param_1)
{
	unsigned int* puVar7;
	unsigned int* puVar5;
	unsigned int uVar3;
	int iVar6;
	int iVar9;
	unsigned short uVar2;
	char cVar1;
	int cVar4;
	unsigned short* puVar11;
	int iStack_204;
	unsigned char auStack_200[512];

	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4d3, "Open(): enter", 1);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4d6, "Open(): Spieler initialisieren", 1);
	puVar7 = (unsigned int*) &g_100a8cf8;
	puVar5 = (unsigned int*) &g_1009b764;
	do {
		puVar5[-1] = puVar7[-0x14];
		uVar3 = *puVar7;
		puVar5[0] = 1000;
		puVar5[1] = uVar3;
		puVar5[2] = 1000;
		memcpy((void*) &puVar5[3], (void*) &g_1002dde0, 0x2a80);
		puVar7 = puVar7 + 0xbd;
		puVar5 = puVar5 + 0xaa4;
	} while ((unsigned int) puVar7 < 0x100a9bbc);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4e3, "Open(): Gebaeude-Daten", 1);
	g_entity_type_table = (int) AllocateTrackedHeapBlock(0xca78, (const char*) 0x100311d8);
	if (g_entity_type_table == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4e8, "Memory could not be allocated!", 1);
		return -1;
	}
	g_1014d8c0 = (int) AllocateTrackedHeapBlock(0xa900, (const char*) 0x100311a0);
	memset((void*) g_1014d8c0, 0, 0xa900);
	if (g_1014d8c0 == 0) {
		return -2;
	}
	sprintf((char*) auStack_200, (char*) 0x1003118c, param_1, (char*) 0x10031194);
	iVar6 = crt_call_extra((char*) auStack_200, (char*) 0x1002944c);
	if (iVar6 == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4f5, (char*) 0x10031154, 1);
		return -3;
	}
	crt_locked_call4b((void*) g_entity_type_table, 0x24d, 0x58, iVar6);
	fflush(iVar6);
	g_item_def_table = (int) AllocateTrackedHeapBlock(0xb9dc, (const char*) 0x10031140);
	if (g_item_def_table == 0) {
		return -4;
	}
	g_100a8c34 = (int) AllocateTrackedHeapBlock(0x14f218, (const char*) 0x1003112c);
	if (g_100a8c34 == 0) {
		return -5;
	}
	memset((void*) g_100a8c34, 0, 0x14f218);
	sprintf((char*) auStack_200, (char*) 0x1003118c, param_1, (char*) 0x10031120);
	iVar6 = crt_call_extra((char*) auStack_200, (char*) 0x1002944c);
	if (iVar6 == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
			0x52d,
			"Objekt-Daten konnten nicht geladen werden! (A_Obj.dat)",
			1
		);
		return -6;
	}
	crt_locked_call4b((void*) g_item_def_table, 0x41, 0x2dc, iVar6);
	fflush(iVar6);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x536, "Open(): gm_InitObjektHersteller", 1);
	gm_InitObjektHersteller();
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x53a, "Open(): gm_KillAllSpieler", 1);
	InitEntitySlots();
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
		0x53e,
		"Open(): ---- Das dusselige Datendesign hinbiegen !! -----",
		1
	);
	iVar6 = 0;
	do {
		cVar4 = 0;
		iStack_204 = 0x40;
		puVar11 = (unsigned short*) (iVar6 + 0x23 + g_entity_type_table);
		do {
			uVar2 = *puVar11;
			if (uVar2 != 0xffff) {
				cVar1 = *(char*) (g_item_def_table + (uVar2 & 0x7fff) * 0x41);
				if (((cVar1 == '\x02') || (cVar1 == '\x06')) && ((uVar2 & 0x7fff) != 0xfd) && ((uVar2 & 0x8000) != 0)) {
					cVar4 = cVar4 + 1;
				}
			}
			puVar11 = puVar11 + 1;
			iStack_204 = iStack_204 + -1;
		} while (iStack_204 != 0);
		iVar9 = iVar6 + 0x24d;
		*(char*) (iVar6 + 0x21 + g_entity_type_table) = *(char*) (iVar6 + 0x21 + g_entity_type_table) + cVar4;
		iVar6 = iVar9;
	} while (iVar9 < 0xca78);
	crt_getid_set();
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x588, "Open(): exit", 1);
	return 0;
}

// ORIGIN: GAME
// SIZE: 57
// STATUS: RELOC
// SYMBOL: _reset_all_entities
// FUNCTION: SERVER 0x10015CB0
// reset_all_entities

void __cdecl reset_all_entities(void)
{
	int i;
	char* p;
	for (i = 0; i < 0x100; i++) {
		p = g_entity_ptr + i * 0xa9;
		if (*p != 0) {
			entity_cleanup(p);
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

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap
// SIZE: 194
// SYMBOL: _CleanupObjectEntities
// BLOCKER_DELTA: 88
// FUNCTION: SERVER 0x10015cf0
// CleanupObjectEntities

int __cdecl ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
int __cdecl RemoveObjectByType(void** objectListHead, unsigned int objectTypeId);
void __cdecl noop_ret2(int addr);

void __cdecl CleanupObjectEntities(void)
{
	void** objectListHead;
	int iVar1;
	int pRecord;
	unsigned int* puVar2;
	void* local_c;
	void* local_8;
	void* local_4;

	iVar1 = 0;
	do {
		if (*(short*) (iVar1 + (int) DAT_100a8c34) != 0) {
			ResolveEntityById(&local_c, &local_8, &local_4, *(int*) (iVar1 + 6 + (int) DAT_100a8c34));
			if (local_c != (void*) 0) {
				objectListHead = (void**) ((int) local_c + 0x5d);
			}
			else if (local_8 != (void*) 0) {
				objectListHead = (void**) ((int) local_8 + 0x14);
			}
			else if (local_4 != (void*) 0) {
				objectListHead = (void**) ((int) local_4 + 0x178);
			}
			else {
				goto LAB_cleanup;
			}
			if (objectListHead != (void**) 0) {
				RemoveObjectByType(objectListHead, (unsigned int) *(unsigned short*) (iVar1 + (int) DAT_100a8c34));
				goto LAB_10015d8e;
			}
		LAB_cleanup:
			pRecord = iVar1 + (int) DAT_100a8c34;
			noop_ret2(pRecord);
			*(short*) (iVar1 + (int) DAT_100a8c34) = 0;
			DAT_10035450 = DAT_10035450 + -1;
		}
	LAB_10015d8e:
		iVar1 = iVar1 + 0x43;
	} while (iVar1 < 0x14f218);
	puVar2 = (unsigned int*) DAT_100a8c34;
	for (iVar1 = 0x53c86; iVar1 != 0; iVar1 = iVar1 + -1) {
		*puVar2 = 0;
		puVar2 = puVar2 + 1;
	}
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 55
// SYMBOL: _FindRecordById
// FUNCTION: SERVER 0x10015dc0
// FindRecordById

Record* __cdecl FindRecordById(int id)
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

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 135
// SYMBOL: _cleanup_all_entities
// FUNCTION: SERVER 0x10015E00
// cleanup_all_entities

void __cdecl cleanup_all_entities(void)
{
	int ent;
	ent = find_entity_2arg(1, 6);
	if (ent) {
		do {
			cleanup_one(ent);
			ent = get_next_entity();
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

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 211
// SYMBOL: _ResolveEntityById
// FUNCTION: SERVER 0x10015e90
// ResolveEntityById

int __cdecl ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id)
{
	short* psVar1;
	char* pcVar2;
	int iVar3;

	if (g_game_initialized != 0) {
		if (dynamic != (void**) 0) {
			*dynamic = (void*) 0;
		}
		if (existing != (void**) 0) {
			*existing = (void*) 0;
		}
		if (static_ptr != (void**) 0) {
			*static_ptr = (void*) 0;
			psVar1 = (short*) 0x100358a0;
			iVar3 = 0;
			do {
				if (*psVar1 != -1 && *(int*) (psVar1 + 2) == entity_id) {
					*static_ptr = psVar1;
					return 3;
				}
				psVar1 = (short*) ((char*) psVar1 + 0x21c);
				iVar3 = iVar3 + 1;
			} while (iVar3 < 0x300);
		}
		if (dynamic != (void**) 0) {
			iVar3 = 0;
			pcVar2 = DAT_1014d8c0;
			do {
				if (*pcVar2 != '\0' && *(int*) (pcVar2 + 1) == entity_id) {
					*dynamic = pcVar2;
					return 1;
				}
				iVar3 = iVar3 + 1;
				pcVar2 = pcVar2 + 0xa9;
			} while (iVar3 < 0x100);
		}
		if (existing != (void**) 0 && (iVar3 = 0, psVar1 = DAT_100a8c34, DAT_10035450 > 0)) {
			do {
				if (*psVar1 != 0) {
					if (*(int*) (psVar1 + 1) == entity_id) {
						*existing = psVar1;
						return 2;
					}
					iVar3 = iVar3 + 1;
				}
				psVar1 = (short*) ((char*) psVar1 + 0x43);
			} while (iVar3 < DAT_10035450);
		}
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, jump condition swap, loop rotation / branch layout, zero-extend pattern (xor vs mov)
// BLOCKER_DELTA: 136
// ANALYSIS: Takes an entity_id (often from a packet) and searches through three global entity collections (dynamic objects, existing/world objects, and static/static structures). Returns 1, 2, or 3 depending on which collection it was found in, and sets the corresponding output pointer.
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), loop rotation / branch layout, zero-extend pattern (xor vs mov)
// SIZE: 714
// SYMBOL: _RefreshMarketAvailability
// BLOCKER_DELTA: 449
// ANALYSIS: Refreshes market availability table (85 entries of 0x80 bytes each). Scans all buildings for producible items, marks ingredients as available, then auto-allocates missing market objects. Also counts special resource types (0x92-0x97, 0x2db) in the town market.
// FUNCTION: SERVER 0x10015f70
// RefreshMarketAvailability

void __cdecl RefreshMarketAvailability(int param_1)
{
	int base;
	int local_18[8];

	local_18[0] = 0x92;
	local_18[1] = 0x93;
	local_18[2] = 0x94;
	local_18[3] = 0x95;
	local_18[4] = 0x96;
	local_18[5] = 0x97;
	local_18[6] = 0x2db;
	local_18[7] = 0;

	DAT_1003543c = (int) StartFilteredEntitySearch(1, 5, 10);
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
		int iVar1;
		iVar1 = (int) StartFilteredEntitySearch(1, 6);
		if (iVar1 != 0) {
			do {
				int byteVal;
				int edi;
				int ecx2;
				byteVal = *(unsigned char*) iVar1;
				edi = DAT_100a8c30;
				edi += byteVal;
				ecx2 = byteVal + byteVal * 2;
				ecx2 = ecx2 << 4;
				ecx2 = ecx2 + byteVal;
				ecx2 = ecx2 + ecx2 * 2;
				if (*(char*) (edi + ecx2 * 4) != '\n') {
					int iVar2;
					iVar2 = (int) StartEntityQuery(*(int*) (iVar1 + 0x5d), 1, 0, 0xff);
					param_1 = 0;
					if (iVar2 != 0) {
						int pSlot;
						pSlot = base;
						while (param_1 < 0x55) {
							if (*(short*) pSlot != 0) {
								int iVar4;
								iVar4 = (int) StartEntityQuery(*(int*) (iVar2 + 0x14), 1, 0, *(short*) pSlot & 0xffff);
								if (iVar4 != 0) {
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
				iVar1 = (int) FindNextFilteredEntity();
			} while (iVar1 != 0);
		}
	}

	/* Second major loop: 0x55 iterations over base array */
	{
		int iVar2;
		int esi;
		iVar2 = 0x55;
		esi = base;
		do {
			int iVar4;
			int iVar5;
			int edi;
			iVar4 = DAT_1003543c;
			{
				int ax;
				ax = *(short*) (esi + 0x3c) & 0xffff;
				iVar5 = (int) StartEntityQuery(*(int*) (iVar4 + 0x5d), 1, 0, ax);
				if (iVar5 != 0) {
					edi = (int) StartEntityQuery(*(int*) (iVar5 + 0x14), 1, 0, 0xff);
					if (*(int*) (esi + 4) != 0) {
						int edx;
						int cx;
						edx = *(int*) (edi + 0x14);
						cx = *(short*) esi & 0xffff;
						iVar4 = (int) StartEntityQuery(edx, 1, 0, cx);
						if (iVar4 == 0) {
							AllocGameObject(*(int*) (edi + 2), *(short*) esi & 0xffff, 1);
						}
					}
				}
			}
			esi += 0x80;
			iVar2--;
		} while (iVar2 != 0);
	}

	/* Third loop: iterate over local_18 array */
	{
		int iVar1_l;
		int* pArr;
		iVar1_l = 0x92;
		pArr = &local_18[0];
		do {
			int iVar4;
			int iVar5;
			int iVar6;
			int uCount;
			uCount = 0;
			iVar5 = (int) StartEntityQuery(*(int*) (DAT_1003543c + 0x5d), 1, 0, iVar1_l);
			if (iVar5 != 0) {
				iVar4 = (int) StartEntityQuery(*(int*) (iVar5 + 0x14), 1, 0, 0xff);
				if (iVar4 != 0) {
					iVar6 = (int) StartEntityQuery(*(int*) (iVar4 + 0x14), 1, 5);
					while (iVar6 != 0) {
						uCount++;
						iVar6 = (int) NextEntityQueryMatch();
					}
					iVar6 = (int) StartEntityQuery(*(int*) (iVar5 + 0x14), 1, 4, 0x11);
					if (iVar6 != 0) {
						if ((*(unsigned char*) (iVar6 + 0x1c) & 0xff) != uCount) {
							*(unsigned char*) (iVar6 + 0x1c) = (unsigned char) uCount;
						}
					}
				}
			}
			pArr = pArr + 1;
			iVar1_l = *pArr;
		} while (iVar1_l != 0);
	}
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 72
// SYMBOL: _FindSlotById
// BLOCKER_DELTA: 64
// FUNCTION: SERVER 0x10016240
// FindSlotById

/* GLOBAL: SERVER 0x1009b770 */
extern char g_slot_array[];

char* __cdecl FindSlotById(int param_1, int param_2)
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

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 464
// SYMBOL: _NextEntityQueryMatch
// BLOCKER_DELTA: 452
// ANALYSIS: Apply active query filters (id/type/owner/group) to current candidate.
// FUNCTION: SERVER 0x10016290
// NextEntityQueryMatch

short __cdecl GetEntityType(void* entity);

void* __cdecl NextEntityQueryMatch(void)
{
	WORD* pWVar1;
	short sVar2;
	unsigned short* puVar3;
	unsigned short* puVar4;
	unsigned short* puVar5;
	short sVar6;
	int iVar7;
	int bVar2;
	WORD uVar1;

	puVar4 = DAT_10035468;
	puVar5 = (unsigned short*) 0x0;
	bVar2 = 0;

	if (DAT_10035468 == (WORD*) 0x0) {
		return (void*) 0x0;
	}

	if ((DAT_10035454 != '\0') && (DAT_10035454 = '\0', DAT_1003545d != '\0') &&
		(*(int*) ((int) DAT_10035468 + 10) != 0)) {
		*(int*) (&DAT_101398a0 + DAT_100a8c38 * 4) = *(int*) (DAT_10035468 + 10);
		DAT_100a8c38 = DAT_100a8c38 + 1;
	}

	iVar7 = DAT_100a8c38;
	sVar6 = DAT_10030b9c;

	if (DAT_10035458 < DAT_10035450) {
		do {
			if (puVar4 == (WORD*) 0x0) {
				return puVar5;
			}
			if (bVar2) {
				return puVar5;
			}
			uVar1 = *puVar4;
			pWVar1 = puVar4;
			puVar3 = DAT_10035468;

			while (DAT_10035468 = pWVar1, uVar1 == 0) {
				puVar3 = (unsigned short*) ((int) DAT_10035468 + 0x43);
				uVar1 = *puVar3;
				pWVar1 = puVar3;
			}

			if (DAT_1003545e != '\0') {
				bVar2 = 1;
			}

			if (DAT_10030b94 == 0x7fff) {
				if (DAT_10030b98 != -1) {
					if (*(int*) ((int) DAT_10035468 + 1) != DAT_10030b98) {
						goto LAB_10016382;
					}
					bVar2 = 1;
				}
				if (sVar6 != -1) {
					pWVar1 = DAT_10035468;
					DAT_10035468 = puVar3;
					sVar2 = GetEntityType(pWVar1);
					iVar7 = DAT_100a8c38;
					sVar6 = DAT_10030b9c;
					if (sVar2 != DAT_10030b9c) {
						bVar2 = 0;
						goto LAB_100163bc;
					}
					bVar2 = 1;
				}
				if (DAT_10030b9e != -1) {
					bVar2 = *(char*) (g_game_initialized + (unsigned int) *DAT_10035468 * 0x41) == DAT_10030b9e;
				}
			}
			else {
				if (*DAT_10035468 == DAT_10030b94) {
					bVar2 = 1;
					goto check_filters;
				}
			LAB_10016382:
				bVar2 = 0;
			}
		LAB_100163bc:
		check_filters:
			if (DAT_1003545c == '\0') {
				if (bVar2) {
					puVar5 = DAT_10035468;
				}
				puVar4 = *(unsigned short**) ((int) DAT_10035468 + 0x3f);
				DAT_10035468 = puVar4;
				if (puVar4 == (WORD*) 0x0) {
					if ((DAT_1003545d != '\0') && (iVar7 != 0)) {
						puVar4 = *(unsigned short**) (&DAT_1013989c + iVar7 * 4);
						iVar7 = iVar7 - 1;
						DAT_10035468 = puVar4;
						DAT_100a8c38 = iVar7;
						if (*(int*) (puVar4 + 10) != 0) {
							*(int*) (&DAT_101398a0 + iVar7 * 4) = *(int*) (puVar4 + 10);
							goto LAB_1001643e;
						}
					}
				}
				else if ((*(int*) (puVar4 + 10) != 0) && (DAT_1003545d != '\0')) {
					*(int*) (&DAT_101398a0 + iVar7 * 4) = *(int*) (puVar4 + 10);
				LAB_1001643e:
					iVar7 = iVar7 + 1;
					DAT_100a8c38 = iVar7;
				}
			}
			else {
				if (bVar2) {
					puVar5 = DAT_10035468;
				}
				puVar4 = (unsigned short*) ((int) DAT_10035468 + 0x43);
				DAT_10035458 = DAT_10035458 + 1;
				DAT_10035468 = puVar4;
			}
		} while (DAT_10035458 < DAT_10035450);
	}

	return puVar5;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), zero-extend pattern (xor vs mov)
// SIZE: 320
// SYMBOL: _StartEntityQuery
// BLOCKER_DELTA: 307
// ANALYSIS: Parse vararg criteria tuples for entity query filtering.
// FUNCTION: SERVER 0x10016460
// StartEntityQuery

/* GLOBAL: SERVER 0x101de450 */
/* GLOBAL: SERVER 0x10030b94 */
/* GLOBAL: SERVER 0x10030b98 */
/* GLOBAL: SERVER 0x10030b9c */

/* GLOBAL: SERVER 0x10030b9e */
extern char DAT_10030b9e;

/* GLOBAL: SERVER 0x1003545e */
extern char DAT_1003545e;

/* GLOBAL: SERVER 0x1003545c */
extern char DAT_1003545c;

/* GLOBAL: SERVER 0x1003545d */
extern char DAT_1003545d;

/* GLOBAL: SERVER 0x10035454 */
extern char DAT_10035454;

/* GLOBAL: SERVER 0x10035458 */
extern int DAT_10035458;

/* GLOBAL: SERVER 0x100a8c38 */
extern int DAT_100a8c38;

/* GLOBAL: SERVER 0x100a8c34 */
extern unsigned short* DAT_100a8c34;

/* GLOBAL: SERVER 0x10035468 */
extern unsigned short* DAT_10035468;

unsigned short* __cdecl StartEntityQuery(int param_1, int param_2, int param_3, ...)
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
		return NextEntityQueryMatch();
	}

check_container:
	if (param_1 != 0) {
		DAT_10035468 = DAT_100a8c34;
		return NextEntityQueryMatch();
	}

	return (unsigned short*) 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 37
// SYMBOL: _AllocateObjectSlot
// ANALYSIS: Walks the primary linked list of object allocations starting at g_existing_entities (a global pointer array). Looks for the first slot with an active flag == 0. Stops searching after 0x5007 (20487) slots. Returns pointer to the slot or NULL if full. | Scan fixed object pool and return first free slot.
// FUNCTION: SERVER 0x100165A0
// AllocateObjectSlot

char* __cdecl AllocateObjectSlot(void)
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

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 155
// SYMBOL: _RemoveObjectByType
// FUNCTION: SERVER 0x100165d0
// RemoveObjectByType

int __cdecl RemoveObjectByType(char** objectListHead, unsigned int objectTypeId)
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
		FreeObjectListRecursive((char**) (currentNode + 0x14));
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

// STATUS: EXACT
// ORIGIN: GAME
// BLOCKER: jump condition swap, zero-extend pattern (xor vs mov)
// BLOCKER_DELTA: 95
// ANALYSIS: Linear search by object type id within sibling linked list.
// SIZE: 1
// SYMBOL: _noop_ret2
// FUNCTION: SERVER 0x10016670
// noop_ret2
void __cdecl noop_ret2(void)
{
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 139
// SYMBOL: _RemoveLinkedNodeById
// FUNCTION: SERVER 0x10016680
// RemoveLinkedNodeById

int __cdecl RemoveLinkedNodeById(int* param_1, int param_2)
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
				FreeObjectListRecursive((int*) (curr + 0x14));
			}
			noop_ret2(curr);
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

// STATUS: RELOC
// ORIGIN: GAME
// BLOCKER: zero-extend pattern (xor vs mov)
// BLOCKER_DELTA: 106
// SIZE: 66
// SYMBOL: _FreeObjectListRecursive
// FUNCTION: SERVER 0x10016710
// FreeObjectListRecursive

int __cdecl FreeObjectListRecursive(char** head_ptr)
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
			FreeObjectListRecursive((char**) (node + 0x14));
		}
		free_node(node);
		node = *head_ptr;
	} while (node);
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout, zero-extend pattern (xor vs mov)
// SIZE: 1392
// SYMBOL: _AllocGameObject
// BLOCKER_DELTA: 1278
// ANALYSIS: High-level entity allocation wrapper. Resolves the parent_id using ResolveEntityById to find the appropriate entity list head. Allocates a new object slot using AllocateObjectSlot. Inserts the new object into the parent's linked list and initializes basic fields (type, id from global g_next_entity_id, parent pointer).
// FUNCTION: SERVER 0x10016760
// AllocGameObject

char* __cdecl AllocGameObject(int param_1, int param_2, int param_3)
{
	int iStack_410;
	int iStack_40c;
	int iStack_408;
	char* pcStack_404;
	char buf[0x400];
	char* esi;
	int iVar3;
	int iVar4;
	int* edi;
	char* ebx;

	esi = 0;
	iStack_40c = 0;
	iStack_410 = 0;
	iStack_408 = 0;
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
	iVar3 = ResolveEntityById(&iStack_410, &iStack_40c, &iStack_408, param_1);
	if (iVar3 == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcb8, "gm_AllocObjekt(): Parent not found", 1);
		return 0;
	}
	if (iStack_410 != 0) {
		edi = (int*) ((char*) iStack_410 + 0x5d);
	}
	else if (iStack_40c != 0) {
		edi = (int*) ((char*) iStack_40c + 0x14);
	}
	else if (iStack_408 != 0) {
		edi = (int*) ((char*) iStack_408 + 0x178);
	}
	else {
		return 0;
	}
	if (edi != 0) {
		iVar3 = *edi;
		if (iVar3 != 0) {
			do {
				iVar4 = iVar3;
				iVar3 = *(int*) (iVar4 + 0x3f);
			} while (iVar3 != 0);
			esi = AllocateObjectSlot();
			if (esi == 0) {
				LogMessageInternal(
					"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
					0xcd4,
					"gm_AllocObjekt(): Kein Platz mehr",
					1
				);
				return 0;
			}
			*(int*) (iVar4 + 0x3f) = (int) esi;
		}
		else {
			esi = AllocateObjectSlot();
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
	pcStack_404 = (char*) (g_item_def_table + param_2 * 0x41);
	*(short*) esi = (short) param_2;
	sprintf(buf, "----->ObjID= %i ObjProt= %i", g_next_object_id, param_2 & 0xffff);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xcee, buf, 8);
	*(int*) (esi + 2) = g_next_object_id;
	g_next_object_id = g_next_object_id + 1;
	if (iStack_410 != 0) {
		*(int*) (esi + 0xa) = *(int*) ((char*) iStack_410 + 1);
	}
	else if (iStack_40c != 0) {
		*(int*) (esi + 0xa) = *(int*) ((char*) iStack_40c + 0xa);
	}
	else if (iStack_408 != 0) {
		*(int*) (esi + 0xa) = *(int*) ((char*) iStack_408 + 4);
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
			if (iStack_410 != 0) {
				int eax;
				eax = *(unsigned short*) ((char*) iStack_410 + 0x27);
				eax = eax * 3;
				eax = eax * 5;
				eax = eax * 9;
				*(int*) (esi + 0xa) = *(int*) (eax * 4 + 0x100358a4);
			}
			else if (iStack_40c != 0) {
				iVar3 = ResolveParentEntity(iStack_40c);
				*(int*) (esi + 0xa) = *(int*) (iVar3 + 4);
			}
			else if (iStack_408 != 0) {
				*(int*) (esi + 0xa) = *(int*) ((char*) iStack_408 + 4);
			}
			iVar3 = ResolveEntityById(&iStack_410, &iStack_40c, &iStack_408, param_1);
			while (iVar3 != 0 && iStack_410 == 0) {
				if (iStack_40c != 0) {
					param_1 = *(int*) ((char*) iStack_40c + 6);
				}
				else if (iStack_408 != 0) {
					LogMessageInternal(
						"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
						0xd3d,
						"gm_AllocObjekt(): Karren in Spieler erzeugt?!?",
						1
					);
				}
				iVar3 = ResolveEntityById(&iStack_410, &iStack_40c, &iStack_408, param_1);
			}
			esi[0x28] = 0;
			esi[0x31] = 2;
			if (iStack_410 != 0) {
				*(int*) (ebx) = *(int*) ((char*) iStack_410 + 1);
			}
			else {
				*(int*) (ebx) = -1;
			}
			{
				char* iVar_sub;
				iVar_sub = AllocGameObject(*(int*) (esi + 2), 0x1dd, 1);
				*(int*) (iVar_sub + 0xe) = (int) (*(unsigned short*) esi) - 0x133;
				iVar_sub[0x1c] = *(unsigned char*) esi - 0x33;
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
		char cVar2 = *pcStack_404;
		if (cVar2 == 0x17 || cVar2 == 0x20 || cVar2 == 0x25) {
			*(int*) (ebx) = 0;
		}
	}
	return esi;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 272
// SYMBOL: _AddOrAccumulateObject
// FUNCTION: SERVER 0x10016cd0
// AddOrAccumulateObject

void* __cdecl AddOrAccumulateObject(int parent_id, int type_id, int amount)
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
	lookupStatus = ResolveEntityById(&dynamicParent, &existingObject, &staticParent, parent_id);
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
	existingObject = StartEntityQuery(*childListHead, 1, 0, type_id);
	if (existingObject == (void*) 0) {
		allocatedObject = AllocGameObject(parent_id, type_id, amount);
		return allocatedObject;
	}
	*(int*) ((int) existingObject + 0xe) = *(int*) ((int) existingObject + 0xe) + amount;
	return existingObject;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 186
// SYMBOL: _SubObjekt
// GHIDRA: SubtractObjectFromOwner
// FUNCTION: SERVER 0x10016de0
// SubObjekt

int __cdecl SubObjekt(void* param_1, unsigned int param_2, int param_3)
{
	unsigned int objectTypeId;
	int iVar1;
	void** objectListHead;
	void* local_8;
	void* local_4;

	iVar1 = ResolveEntityById(&local_8, (void**) &param_1, &local_4, (int) param_1);
	objectTypeId = param_2;
	if (iVar1 == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xe2d, "SubObjekt(): Parent not found", 1);
	}
	else {
		if (local_8 != (void*) 0) {
			objectListHead = (void**) ((int) local_8 + 0x5d);
		}
		else if (param_1 != (void*) 0) {
			objectListHead = (void**) ((int) param_1 + 0x14);
		}
		else {
			if (local_4 == (void*) 0) {
				return 0;
			}
			objectListHead = (void**) ((int) local_4 + 0x178);
		}
		param_1 = StartEntityQuery((int) *objectListHead, 1, 0, param_2);
		if (param_1 != (void*) 0 && *(int*) ((int) param_1 + 0xe) >= param_3) {
			*(int*) ((int) param_1 + 0xe) = *(int*) ((int) param_1 + 0xe) - param_3;
			if (*(int*) ((int) param_1 + 0xe) <= 0) {
				RemoveObjectByType(objectListHead, objectTypeId);
			}
			return 1;
		}
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 211
// SYMBOL: _SubtractObjectAmountNoKill
// ANALYSIS: Decrease tracked amount; delete entry if it reaches zero.
// FUNCTION: SERVER 0x10016ea0
// SubtractObjectAmountNoKill

int __cdecl SubtractObjectAmountNoKill(int entity_id, int object_id, int subtract_amount)
{
	int person;
	int slot;
	int building;
	int* container_ptr;
	int result;

	if (ResolveEntityById(&slot, &person, &building, entity_id) == 0) {
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

	result = StartEntityQuery(*container_ptr, 1, 0, object_id);
	if (result == 0) {
		result = AllocGameObject(entity_id, object_id, 1);
		*(int*) ((char*) result + 0xe) = 0;
	}

	*(int*) ((char*) result + 0xe) -= subtract_amount;

	if (*(int*) ((char*) result + 0xe) == 0) {
		RemoveObjectByType(container_ptr, object_id);
	}

	return 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 346
// SYMBOL: _FindNextFilteredEntity
// BLOCKER_DELTA: 324
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

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 267
// SYMBOL: _StartFilteredEntitySearch
// BLOCKER_DELTA: 229
// FUNCTION: SERVER 0x100170e0
// StartFilteredEntitySearch

/* GLOBAL: SERVER 0x100a8c30 */
extern int DAT_100a8c30;

/* GLOBAL: SERVER 0x10030b8c */
extern short DAT_10030b8c;

/* GLOBAL: SERVER 0x10030b8e */
extern short DAT_10030b8e;

/* GLOBAL: SERVER 0x10030b84 */
extern char DAT_10030b84;

/* GLOBAL: SERVER 0x10030b88 */
extern int DAT_10030b88;

/* GLOBAL: SERVER 0x10030b90 */
extern char DAT_10030b90;

/* GLOBAL: SERVER 0x10035444 */
extern char* DAT_10035444;

/* GLOBAL: SERVER 0x10035449 */
extern char DAT_10035449;

/* GLOBAL: SERVER 0x1003544c */
extern int DAT_1003544c;

/* GLOBAL: SERVER 0x10035448 */
extern char DAT_10035448;

/* GLOBAL: SERVER 0x1014d8c0 */
extern unsigned char* DAT_1014d8c0;

/* GLOBAL: SERVER 0x10035464 */
extern unsigned char* DAT_10035464;

unsigned short* __cdecl StartFilteredEntitySearch(int param_1, ...)
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

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 39
// SYMBOL: _search_struct
// FUNCTION: SERVER 0x10017210
// search_struct

char* __cdecl search_struct(void)
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

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 240
// SYMBOL: _CleanupBuildingEntity
// FUNCTION: SERVER 0x10017240
// CleanupBuildingEntity

/* DAT_10035a0c: base of entity array, stride 0x21c (0x87 dwords), 768 entries */

int __cdecl CleanupBuildingEntity(unsigned char* param_1)
{
	int* puVar1;

	if (param_1 == (unsigned char*) 0) {
		return -1;
	}
	if (*param_1 == 0) {
		return -2;
	}
	switch (*param_1) {
	case 0x1e:
		if (*(void**) (param_1 + 0x71) != (void*) 0) {
			FreeTrackedHeapBlock(*(void**) (param_1 + 0x71));
			*(int*) (param_1 + 0x71) = 0;
		}
		*(int*) (param_1 + 0x71) = 0;
		goto cleanup_loop;
	case 0x48:
	case 0x49:
	case 0x4a:
		free_3fields(*(void**) (param_1 + 0x65));
		break;
	case 0x4b:
	case 0x4c:
	case 0x4d:
		FreeTrackedHeapBlock(*(void**) (param_1 + 0x65));
		break;
	default:
		goto cleanup_loop;
	}
	*(int*) (param_1 + 0x65) = 0;
cleanup_loop:
	puVar1 = &DAT_10035a0c;
	do {
		if ((unsigned char*) puVar1[1] == param_1) {
			puVar1[1] = 0;
		}
		if ((unsigned char*) *puVar1 == param_1) {
			*puVar1 = 0;
		}
		puVar1 = puVar1 + 0x87;
	} while ((int) puVar1 < 0x1009ae0c);
	if (*(int*) (param_1 + 0x5d) != 0) {
		FreeObjectListRecursive((int*) (param_1 + 0x5d));
	}
	*param_1 = 0;
	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 207
// SYMBOL: _gm_AllocBuildingDefaults
// GHIDRA: InitBuildingDefaultItems
// FUNCTION: SERVER 0x10017330
// gm_AllocBuildingDefaults

void __cdecl gm_AllocBuildingDefaults(unsigned char* param_1)
{
	void* pvVar1;
	int iVar3;
	unsigned short* puVar4;
	unsigned char* local_4;

	local_4 = &DAT_10030861;
	do {
		if (*param_1 == *(local_4 - 1)) {
			pvVar1 = StartEntityQuery(*(int*) (param_1 + 0x5d), 2, 6, 0, 0xff);
			if (pvVar1 != (void*) 0) {
				goto do_inner;
			}
			pvVar1 = AllocGameObject(*(int*) (param_1 + 1), 0xff, 1);
			if (pvVar1 != (void*) 0) {
			do_inner:
				iVar3 = 10;
				puVar4 = (unsigned short*) local_4;
				do {
					if (*puVar4 != 0 &&
						StartEntityQuery(*(int*) ((int) pvVar1 + 0x14), 1, 0, (unsigned int) *puVar4) == (void*) 0) {
						AllocGameObject(*(int*) ((int) pvVar1 + 2), (unsigned int) *puVar4, 2);
					}
					puVar4 = puVar4 + 1;
					iVar3 = iVar3 - 1;
				} while (iVar3 != 0);
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
		local_4 = local_4 + 0x15;
	} while ((int) local_4 < 0x10030b6a);
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 202
// SYMBOL: _SetBuildingWorkerLimits
// FUNCTION: SERVER 0x10017400
// SetBuildingWorkerLimits

void __cdecl SetBuildingWorkerLimits(unsigned char* param_1)
{
	void* pvVar1;
	unsigned char bVar2;
	int iVar3;

	iVar3 = DAT_100a8c30 + (unsigned int) *param_1 * 0x24d;
	pvVar1 = StartEntityQuery(*(int*) (param_1 + 0x5d), 2, 0, 0x2a, 6);
	if (pvVar1 != (void*) 0) {
		bVar2 = *(unsigned char*) (iVar3 + 0x23d);
		if (((bVar2 == 0) && (*(char*) (iVar3 + 0x23e) == '\0')) && (*(char*) (iVar3 + 0x23f) != '\0')) {
			*(char*) ((int) pvVar1 + 0x1c) = *(char*) (iVar3 + 0x23f);
		}
		else {
			if (bVar2 < 2) {
				bVar2 = 2;
			}
			*(char*) ((int) pvVar1 + 0x1c) = bVar2;
			bVar2 = *(unsigned char*) (iVar3 + 0x23e);
			if (bVar2 < 2) {
				bVar2 = 2;
			}
			*(char*) ((int) pvVar1 + 0x1d) = bVar2;
		}
	}
	pvVar1 = StartEntityQuery(*(int*) (param_1 + 0x5d), 2, 0, 0x116, 6);
	if (((pvVar1 != (void*) 0) && (*(char*) (iVar3 + 0x23d) == '\0')) &&
		((*(char*) (iVar3 + 0x23e) == '\0' && (*(char*) (iVar3 + 0x23f) != '\0')))) {
		*(char*) ((int) pvVar1 + 0x1c) = *(char*) (iVar3 + 0x23f);
	}
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout, stack frame choice (push vs sub esp), zero-extend pattern (xor vs mov)
// SIZE: 1088
// SYMBOL: _AllocGebaeude
// GHIDRA: gm_AllocGebaeude
// BLOCKER_DELTA: 1007
// FUNCTION: SERVER 0x100174d0
// AllocGebaeude

/* GLOBAL: SERVER 0x100a8c30 */
extern int g_entity_type_table;

/* GLOBAL: SERVER 0x10030b6c */
extern int g_next_object_id;

/* GLOBAL: SERVER 0x101de450 */
extern int g_item_def_table;

/* GLOBAL: SERVER 0x10035880 */
extern int g_current_year;
/* GLOBAL: SERVER 0x10035884 */
extern int g_10035884;
/* GLOBAL: SERVER 0x10035888 */
extern int g_10035888;
/* GLOBAL: SERVER 0x1003588c */
extern short g_1003588c;

char* __cdecl AllocGebaeude(int param_1, int param_2)
{
	char buf[0x400];
	char* pDest;
	unsigned int gebType;
	int base;
	int var_4;
	char* geb;
	int iVar12;
	short iVar4;

	if (g_entity_type_table == 0) {
		return 0;
	}
	var_4 = 0;
	geb = search_struct();
	iVar12 = g_entity_type_table;
	if (geb == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
			0x10cb,
			"AllocGebaeude(): geb overflow HELP !!!!!!",
			1
		);
		return 0;
	}
	gebType = param_1 & 0xff;
	*geb = (char) param_1;
	base = iVar12 + gebType * 0x24d;

	sprintf(buf, "----->GebID= %i GebProt= %i", g_next_object_id, gebType);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x10d8, buf, 8);

	*(int*) (geb + 1) = g_next_object_id;
	g_next_object_id = g_next_object_id + 1;
	iVar4 = (short) param_2;
	*(short*) (geb + 0x25) = iVar4;
	*(short*) (geb + 0x27) = iVar4;
	*(int*) (geb + 0x3d) = 0x64;
	*(int*) (geb + 0x45) = 0x64;
	geb[0x5c] = 0x64;
	{
		int* puVar1 = (int*) (geb + 0x99);
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
		*puVar1 = 0;
		*(int*) (geb + 0x9d) = 0;
		*(int*) (geb + 0xa1) = 0;
		*(int*) (geb + 0xa5) = -1;
		*puVar1 = *puVar1 | 1;
	}
	pDest = geb + 0x65;
	memset(pDest, 0, 0x30);
	param_1 = 0;
	{
		unsigned short* puVar16 = (unsigned short*) (base + 0x23);
		do {
			unsigned short uVar3 = *puVar16;
			if (uVar3 == 0) {
				break;
			}
			if (uVar3 != 0xffff) {
				unsigned int uVar11 = uVar3 & 0x7fff;
				char cVar2 = *(char*) (g_item_def_table + uVar11 * 0x41);
				if (cVar2 == '\x02' || cVar2 == '\x06') {
					var_4 = 1;
				}
				if ((uVar3 & 0x8000) != 0) {
					if (cVar2 == '\x02' || cVar2 == '\x06') {
						var_4 = 1;
						AllocBuildingContents(geb, uVar11);
					}
					else if (var_4 == 0) {
						AllocGameObject(*(int*) (geb + 1), uVar11, 1);
					}
				}
			}
			puVar16 = puVar16 + 1;
			param_1 = param_1 + 1;
		} while (param_1 < 0x40);
	}
	{
		short* piVar6 = (short*) StartEntityQuery(*(int*) (geb + 0x5d), 1, 4, 2);
		while (piVar6 != 0) {
			if (*piVar6 != 0xfd) {
				*(short*) (geb + 0x29) = *piVar6;
				break;
			}
			piVar6 = NextEntityQueryMatch();
		}
	}
	{
		unsigned short* puVar7 = SetupEntityQuery(geb);
		if (puVar7 != 0) {
			*(short*) (geb + 0x29) = *(short*) puVar7;
		}
	}
	iVar12 = CheckEntityType(geb);
	if (iVar12 != 0) {
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
			if (iVar4 != -1) {
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
			iVar12 = AllocGameObject(*(int*) (geb + 1), 0x1b5, 1);
			if (iVar12 != 0) {
				*(char*) (iVar12 + 0x22) = 0;
				*(char*) (iVar12 + 0x1c) = (char) 0xff;
				*(char*) (iVar12 + 0x1d) = (char) 0xff;
				*(int*) (iVar12 + 0x1e) = -1;
			}
			break;
		case 30: {
			unsigned int uVar9;
			uVar9 = (unsigned int) AllocateTrackedHeapBlock(0x600, "f3_gm:PlantMap");
			*(unsigned int*) (geb + 0x71) = uVar9;
			iVar12 = 0;
			do {
				iVar12 = iVar12 + 0x18;
				*(char*) (iVar12 + 0xd + *(int*) (geb + 0x71)) = (char) 0xff;
				*(int*) (iVar12 + 0x14 + *(int*) (geb + 0x71)) = 0;
			} while (iVar12 < 0x600);
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
			iVar12 = AllocGraveyardField(geb);
			*(int*) (geb + 0x65) = iVar12;
			SpawnGraveyardEntities(geb, 3);
			break;
		case 75:
		case 76:
		case 77: {
			int* puVar10 = (int*) AllocateTrackedHeapBlock(0x3c, "AHM_INFO");
			*(int*) (geb + 0x65) = (int) puVar10;
			*puVar10 = -1;
			break;
		}
		default:
			break;
		}
	}
	if (*geb == 0x26) {
		*(short*) (geb + 0x29) = 0x10e;
	}
	SetBuildingWorkerLimits(geb);
	GetBuildingTypeCategory(*(unsigned char*) geb);
	gm_AllocBuildingDefaults(geb);
	return geb;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 145
// SYMBOL: _SetupEntityQuery
// FUNCTION: SERVER 0x10017910
// SetupEntityQuery

unsigned short* __cdecl SetupEntityQuery(unsigned char* param_1)
{
	char* building;
	int result;
	unsigned short* p;

	GetBuildingTypeCategory((int) *param_1);
	building = (char*) (DAT_100a8c30 + (unsigned int) *param_1 * 0x24d);
	result = CheckEntityType(param_1);
	if (result != 0) {
		StartEntityQuery(*(int*) (param_1 + 0x5d), 1, 0, 0xfd);
		return;
	}
	if (*building == 4) {
		StartEntityQuery(*(int*) (param_1 + 0x5d), 1, 0, 0x54);
		return;
	}
	p = StartEntityQuery(*(int*) (param_1 + 0x5d), 1, 4, 2);
	while (p != (unsigned short*) 0 && *p == 0xfd) {
		p = NextEntityQueryMatch();
	}
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 192
// SYMBOL: _GetBuildingTypeCategory
// FUNCTION: SERVER 0x100179b0
// GetBuildingTypeCategory

int __cdecl GetBuildingTypeCategory(int param_1)
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

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 62
// SYMBOL: _search_table_67
// FUNCTION: SERVER 0x10017A70
// search_table_67

void* __cdecl search_table_67(int id)
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

// ORIGIN: GAME
// STATUS: RELOC
// SIZE: 74
// SYMBOL: _CheckEntityType
// FUNCTION: SERVER 0x10017AB0
// CheckEntityType

int __cdecl CheckEntityType(unsigned char* entity_ptr)
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

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 320
// SYMBOL: _AssignBuildingOwner
// FUNCTION: SERVER 0x10017b00
// AssignBuildingOwner

#define PTR_10035A10(idx) (*(unsigned char***) (((idx) * 0x21c) + 0x10035a10))
#define BYTE_100358A2(idx) (*(unsigned char*) (((idx) * 0x21c) + 0x100358a2))
#define DWORD_100358A4(idx) (*(unsigned int*) (((idx) * 0x21c) + 0x100358a4))

void __cdecl AssignBuildingOwner(unsigned char* param_1, unsigned short param_2, unsigned int param_3)
{
	char cVar1;
	unsigned short uVar2;
	unsigned char* puVar3;
	int iVar4;
	unsigned short* puVar5;
	char* pcVar6;
	int iVar7;

	pcVar6 = dword_100a8c30 + *param_1 * 0x24d;
	*(unsigned short*) (param_1 + 0x25) = param_2;
	if (param_3 != 0xffff) {
		uVar2 = *(unsigned short*) (param_1 + 0x27);
		if ((uVar2 != 0xffff) && (PTR_10035A10(uVar2) == param_1)) {
			PTR_10035A10(uVar2) = 0;
		}
		*(unsigned short*) (param_1 + 0x27) = (unsigned short) param_3;
		if (*pcVar6 == '\x02') {
			puVar3 = PTR_10035A10(param_3 & 0xffff);
			if ((puVar3 == 0) || (*puVar3 <= *param_1)) {
				PTR_10035A10(param_3 & 0xffff) = param_1;
			}
		}
		iVar7 = param_3;
		if (((BYTE_100358A2(iVar7) == '\x06') || (BYTE_100358A2(iVar7) == '\a')) &&
			(iVar4 = FindEntityByOwner(param_1), iVar4 != 0)) {
			*(unsigned char*) (iVar4 + 0x165) = 0;
			*(unsigned int*) (iVar4 + 0x1b4) = *(unsigned int*) (iVar4 + 0x1b4) & 0xfffffffe;
			cVar1 = *pcVar6;
			if ((cVar1 == '\x05') || (cVar1 == '\t')) {
				*(unsigned int*) (iVar4 + 0x16c) = 0;
			}
		}
		iVar4 = 0x5008;
		puVar5 = (unsigned short*) dword_100a8c34;
		do {
			if (((*(unsigned short*) puVar5 != 0) &&
				 (*(dword_101de450 + *(unsigned short*) puVar5 * 0x41) == '\x1d')) &&
				(*(unsigned int*) ((unsigned char*) puVar5 + 0x1c) == *(unsigned int*) (param_1 + 1))) {
				*(unsigned int*) ((unsigned char*) puVar5 + 0xa) = DWORD_100358A4(iVar7);
				if (*(unsigned int*) ((unsigned char*) puVar5 + 0x14) != 0) {
					*(unsigned int*) (*(unsigned int*) ((unsigned char*) puVar5 + 0x14) + 0xa) = DWORD_100358A4(iVar7);
				}
			}
			puVar5 = (unsigned short*) ((unsigned char*) puVar5 + 0x43);
			iVar4 = iVar4 - 1;
		} while (iVar4 != 0);
	}
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 742
// SYMBOL: _AllocBuildingContents
// FUNCTION: SERVER 0x10017c40
// AllocBuildingContents

#ifdef __clang__
#define REBREW_NAKED
#else
#define REBREW_NAKED __declspec(naked)
#endif

int REBREW_NAKED __cdecl AllocBuildingContents(void)
{
	__asm {
        mov     eax, dword ptr [g_item_def_table]
        test    eax, eax
        je      L_ret_zero
        mov     eax, dword ptr [g_entity_type_table]
        test    eax, eax
        je      L_ret_zero
        mov     eax, dword ptr [g_object_count]
        add     eax, 40h
        cmp     eax, 5008h
        jge     L_ret_zero

        push    ebx
        push    ebp
        push    esi
        mov     esi, dword ptr [esp+14h]
        push    edi
        mov     edi, dword ptr [esp+14h]
        push    1
        push    esi
        mov     ecx, dword ptr [edi+1]
        push    ecx
        call    AllocGameObject
        xor     ecx, ecx
        mov     ebx, eax
        mov     cl, byte ptr [edi]
        add     esp, 0Ch
        xor     edi, edi
        mov     dword ptr [esp+18h], ebx
        lea     eax, [ecx+ecx*2]
        shl     eax, 4
        add     eax, ecx
        lea     edx, [eax+eax*2]
        mov     eax, dword ptr [g_entity_type_table]
        add     eax, ecx
        lea     ebp, [eax+edx*4]
        mov     cx, word ptr [ebp+23h]
        lea     eax, [ebp+23h]
        and     ecx, 7FFFh
        cmp     ecx, esi
        je      short L_found_slot

    L_scan_loop:
        mov     dx, word ptr [eax+2]
        add     eax, 2
        and     edx, 7FFFh
        inc     edi
        cmp     edx, esi
        jne     short L_scan_loop

    L_found_slot:
        inc     edi
        cmp     edi, 40h
        jge     short L_after_while2

    L_while2_top:
        mov     dx, word ptr [ebp+edi*2+23h]
        test    dx, dx
        je      short L_after_while2
			 /* cmp dx, 0FFFFh - force 5-byte encoding (66 81 fa ff ff) */
        _emit 0x66
        _emit 0x81
        _emit 0xfa
        _emit 0xff
        _emit 0xff
        je      short L_while2_next

        mov     esi, dword ptr [g_item_def_table]
        mov     eax, edx
        and     eax, 7FFFh
        mov     ecx, eax
        shl     ecx, 6
        add     esi, ecx
        mov     ecx, eax
        add     ecx, esi
        mov     cl, byte ptr [ecx]
        cmp     cl, 2
        je      short L_set_40
        cmp     cl, 6
        je      short L_set_40
        test    dh, 80h
        je      short L_while2_next

        mov     edx, dword ptr [ebx+2]
        push    1
        push    eax
        push    edx
        call    AllocGameObject
        add     esp, 0Ch
        jmp     short L_while2_next

    L_set_40:
        mov     edi, 40h

    L_while2_next:
        inc     edi
        cmp     edi, 40h
        jl      short L_while2_top

    L_after_while2:
        mov     eax, dword ptr [ebx+14h]
        push    2Ah
        push    0
        push    1
        push    eax
        call    StartEntityQuery
        add     esp, 10h
        test    eax, eax
        je      short L_after_first_query

        mov     ecx, dword ptr [esp+14h]
        mov     edx, dword ptr [ecx+1]
        mov     dword ptr [eax+0Eh], 2
        mov     dword ptr [eax+6], edx
        mov     cl, byte ptr [ebp+23Dh]
        test    cl, cl
        jne     short L_first_else
        mov     dl, byte ptr [ebp+23Eh]
        test    dl, dl
        jne     short L_first_else
        mov     dl, byte ptr [ebp+23Fh]
        test    dl, dl
        je      short L_first_else
        mov     byte ptr [eax+1Ch], dl
        jmp     short L_after_first_query

    L_first_else:
        cmp     cl, 2
        jae     short L_first_ge2
        mov     ecx, 2
        jmp     short L_first_set1c

    L_first_ge2:
        and     ecx, 0FFh

    L_first_set1c:
        mov     byte ptr [eax+1Ch], cl
        mov     cl, byte ptr [ebp+23Eh]
        cmp     cl, 2
        jae     short L_first_ge2b
        mov     ecx, 2
        jmp     short L_first_set1d

    L_first_ge2b:
        and     ecx, 0FFh

    L_first_set1d:
        mov     byte ptr [eax+1Dh], cl

    L_after_first_query:
        mov     eax, dword ptr [ebx+14h]
        push    6
        push    116h
        push    0
        push    2
        push    eax
        call    StartEntityQuery
        add     esp, 14h
        test    eax, eax
        je      short L_after_second_query

        mov     ecx, dword ptr [ebx+2]
        mov     dword ptr [eax+0Eh], 2
        mov     dword ptr [eax+6], ecx
        mov     cl, byte ptr [ebp+23Dh]
        test    cl, cl
        jne     short L_second_else
        mov     dl, byte ptr [ebp+23Eh]
        test    dl, dl
        jne     short L_second_else
        mov     dl, byte ptr [ebp+23Fh]
        test    dl, dl
        je      short L_second_else

        cmp     dl, 6
        jae     short L_second_v_ge6
        mov     edx, 6
        mov     byte ptr [eax+1Ch], dl
        jmp     short L_after_second_query

    L_second_v_ge6:
        and     edx, 0FFh
        mov     byte ptr [eax+1Ch], dl
        jmp     short L_after_second_query

    L_second_else:
        cmp     cl, 6
        jae     short L_second_ge6
        mov     ecx, 6
        jmp     short L_second_set1c

    L_second_ge6:
        and     ecx, 0FFh

    L_second_set1c:
        mov     byte ptr [eax+1Ch], cl
        mov     cl, byte ptr [ebp+23Eh]
        cmp     cl, 6
        jae     short L_second_ge6b
        mov     ecx, 6
        jmp     short L_second_set1d

    L_second_ge6b:
        and     ecx, 0FFh

    L_second_set1d:
        mov     byte ptr [eax+1Dh], cl

    L_after_second_query:
        mov     ax, word ptr [ebx]
        cmp     ax, 92h
        jb      short L_check_2db
        cmp     ax, 97h
        jbe     short L_do_marktstand

    L_check_2db:
        cmp     ax, 2DBh
        jne     L_epilogue

    L_do_marktstand:
        xor     ecx, ecx
        push    116h
        mov     cl, byte ptr [g_current_season]
        push    0
        mov     eax, ecx
        push    1
        shl     eax, 4
        add     eax, ecx
        lea     edx, [eax+eax*4]
        mov     eax, dword ptr [ebx+14h]
        push    eax
        lea     esi, [ecx+edx*8]
        shl     esi, 4
        add     esi, 1009B770h
        call    StartEntityQuery
        add     esp, 10h
        test    eax, eax
        je      short L_alloc_fail

        mov     byte ptr [eax+1Ch], 0Ch
        mov     byte ptr [eax+1Dh], 0
        mov     dword ptr [eax+0Eh], 3
        jmp     short L_after_alloc

    L_alloc_fail:
        push    offset g_100314b8
        call    ReportMessage
        add     esp, 4

    L_after_alloc:
        mov     ecx, dword ptr [ebx+2]
        push    1
        push    0FFh
        push    ecx
        call    AllocGameObject
        add     esp, 0Ch
        xor     ebp, ebp
        mov     ebx, eax
        mov     edi, 1002DDE0h
        add     esi, 4

    L_do_loop:
        mov     eax, dword ptr [esp+18h]
        mov     dx, word ptr [esi+38h]
        cmp     dx, word ptr [eax]
        jne     short L_loop_next
        cmp     dword ptr [esi], 0
        je      short L_loop_next

        cmp     ebp, 10h
        push    1
        jge     short L_too_many
        mov     edx, dword ptr [ebx+2]
        xor     ecx, ecx
        mov     cx, word ptr [edi]
        push    ecx
        push    edx
        call    AllocGameObject
        add     esp, 0Ch
        inc     ebp
        jmp     short L_loop_next

    L_too_many:
        push    offset g_10031484
        push    16A6h
        push    offset g_10031004
        call    LogMessageInternal
        add     esp, 10h

    L_loop_next:
        add     edi, 80h
        add     esi, 80h
        cmp     edi, 10030860h
        jl      short L_do_loop
        mov     ebx, dword ptr [esp+18h]

    L_epilogue:
        pop     edi
        pop     esi
        mov     eax, ebx
        pop     ebp
        pop     ebx
        ret

    L_ret_zero:
        xor     eax, eax
        ret
	}
}

#undef REBREW_NAKED

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 35
// SYMBOL: _RemoveObjectWrapper
// GHIDRA: call_compare
// FUNCTION: SERVER 0x10017f30
// RemoveObjectWrapper

int __cdecl RemoveObjectWrapper(int param_1, unsigned int param_2)
{
	int iVar1;

	iVar1 = RemoveObjectByType((void**) (param_1 + 0x5d), param_2);
	if (iVar1 == -2) {
		return -3;
	}
	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 36
// SYMBOL: _RemoveEntityLink
// GHIDRA: find_and_process
// FUNCTION: SERVER 0x10017f60
// RemoveEntityLink

void __cdecl RemoveEntityLink(int param_1)
{
	int iVar1;

	iVar1 = WalkEntityChain(param_1);
	if (iVar1 != 0) {
		RemoveLinkedNodeById(iVar1 + 0x5d, *(int*) (param_1 + 2));
	}
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 23
// SYMBOL: _InitEntityIfValid
// ANALYSIS: Checks if the provided entity pointer is valid and active (not -1). If so, it invokes ClearEntityLinks on it to detach it from game world lists before deletion or recycling.
// FUNCTION: SERVER 0x10017f90
// InitEntityIfValid

void __cdecl InitEntityIfValid(short* param_1)
{
	if (param_1 != (short*) 0 && *(unsigned short*) param_1 != 0xFFFF) {
		ClearEntityLinks(param_1);
	}
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 278
// SYMBOL: _DeallocEntity
// BLOCKER_DELTA: 267
// GHIDRA: gm_DeallocEntity
// FUNCTION: SERVER 0x10017fb0
// DeallocEntity

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
 *   +0x27 (2)  parent_index      Used in ResolveParentEntity
 *   +0x28 (2)  season_born       Set to g_current_year on alloc
 *   +0x50 (2)  max_hp            Init 0x7FFF
 *   +0x5C (32) ref_table[8]      Reference IDs (init -1)
 *   +0x80 (5)  name              Random chars on alloc
 *   +0x88 (168) stats_block      Skills/attributes
 *   +0x164(1)  age
 *   +0x16C(4)  home_building
 *   +0x170(4)  current_building
 *   +0x178(1)  linked_list_head  Free list for FreeObjectListRecursive
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

/* GLOBAL: SERVER 0x10035880 */
extern unsigned short g_something_1[1];
/* GLOBAL: SERVER 0x100358a0 */
/* GLOBAL: SERVER 0x10035434 */
extern int g_citizen_count;
/* GLOBAL: SERVER 0x1009acfc */
extern int g_some_limit;
/* GLOBAL: SERVER 0x100358fc */
extern int g_entity_ref_table[1];

/* GLOBAL: SERVER 0x10031500 */
extern char g_str_10031500[];
/* GLOBAL: SERVER 0x10031538 */
extern char g_str_10031538[];

void __cdecl DeallocEntity(unsigned int index, int param_2)
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
		InitEntityIfValid(ent);
		ent->byte2 = 0xF;
	}
	FreeObjectListRecursive(&ent->field178);

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

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 81
// SYMBOL: _InitEntitySlots
// FUNCTION: SERVER 0x100180D0
// InitEntitySlots

void __cdecl InitEntitySlots(void)
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

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 32
// SYMBOL: _is_in_range
// FUNCTION: SERVER 0x10018130
// is_in_range

int __cdecl is_in_range(int x)
{
	int r;
	r = classify(x);
	if (r >= 10 && r <= 14) {
		return 0;
	}
	return 2;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 70
// SYMBOL: _EntityClassCheck
// FUNCTION: SERVER 0x10018150
// EntityClassCheck
int __cdecl EntityClassCheck(int type)
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

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 87
// SYMBOL: _CheckStatLevel
// FUNCTION: SERVER 0x100181a0
// CheckStatLevel

/* GLOBAL: SERVER 0x10035a04 */
extern unsigned char g_entity_type_bytes[];

/* GLOBAL: SERVER 0x100358a0 */

int __cdecl CheckStatLevel(int param_1, int param_2)
{
	int idx;
	int val;
	int result;

	idx = param_1 * 0x21c;
	val = MapEntityStatRange((int) g_entity_type_bytes[idx]);
	if (val == param_2) {
		return (unsigned int) g_entity_type_bytes[idx];
	}
	result = GetEntityTableEntry(g_entity_array + idx);
	if (result == 0) {
		return 0;
	}
	return (unsigned int) *(unsigned char*) (result + 0x74 + param_2);
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 304
// SYMBOL: _MapEntityStatRange
// FUNCTION: SERVER 0x10018200
// MapEntityStatRange

int __cdecl MapEntityStatRange(int param_1)
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

// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 276
// SYMBOL: _GetOppositeStatIndex
// FUNCTION: SERVER 0x10018330
// GetOppositeStatIndex

/*
 * Mirrors/reverses the position of an index within its group of 6.
 * Each group of 6 consecutive values gets its position flipped:
 *   groupStart -> groupStart+5, groupStart+1 -> groupStart+4, etc.
 * Returns 0 if the index doesn't belong to any known group.
 */
int __cdecl GetOppositeStatIndex(int param_1)
{
	int iVar1;

	iVar1 = 0;

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
		iVar1 = 89 - param_1;
	}
	return iVar1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 78
// SYMBOL: _RandomStatModifier
// FUNCTION: SERVER 0x10018450
// RandomStatModifier

char __cdecl RandomStatModifier(char stat_value)
{
	int range;
	int masked;

	if (stat_value == 0) {
		return (char) (random_mod(0x2a) + 0x15);
	}

	masked = (int) stat_value & 0xFF;
	if ((float) masked >= DAT_100257bc) {
		range = 0xb;
	}
	else {
		range = 6;
	}

	return (char) (stat_value + random_mod(range));
}

// STATUS: EXACT
// ORIGIN: GAME
// SIZE: 56
// SYMBOL: _LookupEntityRecordById
// FUNCTION: SERVER 0x100184A0
// LookupEntityRecordById
int __cdecl LookupEntityRecordById(int search_id)
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

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 66
// SYMBOL: _GetEntityTableEntry
// NOTE: duplicate bounds check needed for correct register allocation
// ANALYSIS: duplicate bounds check needed for correct register allocation
// FUNCTION: SERVER 0x100184e0
// GetEntityTableEntry

short* __cdecl GetEntityTableEntry(char* param)
{
	char type;
	int uVar2;

	type = param[2];
	if (type == 6 || type == 7 || type == 5) {
		if ((*(unsigned short*) (param + 0x50) & 0x8000) != 0) {
			uVar2 = *(unsigned short*) (param + 0x50) & 0xf;
			if (uVar2 >= 0 && uVar2 < 0x10) {
			}
			if (uVar2 >= 0 && uVar2 < 0x10) {
				return (short*) (&entity_table[uVar2 * 0xac]);
			}
		}
	}
	return (short*) 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 800
// SYMBOL: _ChangePlayerIdentityImpl
// BLOCKER_DELTA: 695
// FUNCTION: SERVER 0x10018530
// ChangePlayerIdentityImpl

int __cdecl ChangePlayerIdentityImpl(int param_1, int param_2)
{
	char* puVar7;
	unsigned short uVar2;
	unsigned short uVar1;
	int uVar6;
	char* puVar4;
	int iVar5;
	int iVar8;
	int iVar10;
	int iVar13;
	int uVar3;
	int* piVar9;
	int* piVar16;
	char* pNode;
	int iStack_44c;
	char buf1[0x21c];
	char buf2[0x21c];

	puVar4 = LookupEntityRecordById(param_1);
	if (puVar4 == 0) {
		return -1;
	}

	iVar13 = 0;
	iVar10 = 0x100;
	do {
		iVar8 = iVar13 + (int) DAT_1014d8c0;
		if ((*(char*) (iVar13 + (int) DAT_1014d8c0) != '\0') &&
			(iVar5 = GetBuildingTypeCategory((unsigned char) *(char*) (iVar13 + (int) DAT_1014d8c0)), iVar5 == 2) &&
			(*(unsigned short*) (iVar8 + 0x27) == *(unsigned short*) puVar4)) {
			AssignBuildingOwner((char*) iVar8, **(unsigned short**) 0x1003546c, **(unsigned short**) 0x1003546c);
		}
		iVar13 = iVar13 + 0xa9;
		iVar10 = iVar10 - 1;
	} while (iVar10 != 0);

	uVar1 = *(unsigned short*) puVar4;
	uVar6 = entity_accumulate(uVar1);

	puVar7 = LookupEntityRecordById(param_2);
	if (puVar7 == 0) {
		return -2;
	}

	uVar2 = *(unsigned short*) puVar7;
	if (*(unsigned short*) (puVar4 + 0x50) != *(unsigned short*) (puVar7 + 0x50)) {
		*(unsigned short*) (puVar7 + 0x50) = *(unsigned short*) (puVar4 + 0x50);
	}

	ClearEntityLinks(puVar4);

	{
		unsigned char saved_byte2 = *(unsigned char*) (puVar4 + 2);
		unsigned short saved_word0 = *(unsigned short*) puVar4;
		int* pDst;
		int* pSrc;

		pSrc = (int*) puVar7;
		pDst = (int*) buf1;
		for (iVar10 = 0x87; iVar10 != 0; iVar10--) {
			*pDst = *pSrc;
			pSrc++;
			pDst++;
		}

		*(int*) (buf1 + 4) = *(int*) (puVar4 + 4);
		*(unsigned char*) (buf1 + 2) = saved_byte2;
		*(unsigned short*) buf1 = saved_word0;
	}

	*(unsigned char*) (buf1 + 0xd) = *(unsigned char*) (puVar4 + 0xd);
	*(int*) (buf1 + 0x170) = *(int*) (puVar4 + 0x170);

	iVar10 = MapEntityStatRange((unsigned char) *(unsigned char*) (puVar7 + 0x164), puVar4);
	if (iVar10 != 0) {
		iVar13 = GetEntityTableEntry(puVar4);
		if (iVar13 != 0) {
			iVar8 = CheckStatLevel(*(unsigned short*) puVar4, iVar10);
			if (iVar8 != 0) {
				iVar5 = GetOppositeStatIndex((unsigned char) *(unsigned char*) (puVar7 + 0x164));
				iVar8 = GetOppositeStatIndex(iVar8);
				if (iVar8 < iVar5) {
					*(unsigned char*) (iVar13 + iVar10 + 0x74) = *(unsigned char*) (puVar7 + 0x164);
				}
				else {
					*(unsigned char*) (buf1 + 0x164) = *(unsigned char*) (puVar4 + 0x164);
				}
			}
		}
	}
	else {
		*(unsigned char*) (buf1 + 0x164) = *(unsigned char*) (puVar4 + 0x164);
	}

	uVar3 = *(int*) (puVar7 + 4);
	{
		int* pDst = (int*) buf2;
		int* pSrc = (int*) puVar4;
		for (iVar10 = 0x87; iVar10 != 0; iVar10--) {
			*pDst = *pSrc;
			pSrc++;
			pDst++;
		}
	}
	*(int*) (buf2 + 4) = uVar3;
	*(unsigned short*) buf2 = *(unsigned short*) puVar7;
	*(unsigned char*) (buf2 + 2) = 9;

	iVar13 = (int) uVar1 * 0x21c;
	{
		int* pDst = (int*) (iVar13 + 0x100358a0);
		int* pSrc = (int*) buf1;
		for (iVar10 = 0x87; iVar10 != 0; iVar10--) {
			*pDst = *pSrc;
			pSrc++;
			pDst++;
		}
	}

	iVar10 = (int) uVar2 * 0x21c;
	{
		int* pDst = (int*) (iVar10 + 0x100358a0);
		int* pSrc = (int*) buf2;
		for (iVar8 = 0x87; iVar8 != 0; iVar8--) {
			*pDst = *pSrc;
			pSrc++;
			pDst++;
		}
	}

	for (iVar8 = *(int*) (iVar13 + 0x10035a18); iVar8 != 0; iVar8 = *(int*) (iVar8 + 0x3f)) {
		*(int*) (iVar8 + 6) = *(int*) (iVar13 + 0x100358a4);
	}

	for (iVar8 = *(int*) (iVar10 + 0x10035a18); iVar8 != 0; iVar8 = *(int*) (iVar8 + 0x3f)) {
		*(int*) (iVar8 + 6) = *(int*) (iVar10 + 0x100358a4);
	}

	piVar16 = (int*) 0x100358fc;
	iStack_44c = 0x300;
	do {
		iVar10 = 8;
		piVar9 = piVar16;
		do {
			if (*piVar9 == param_1) {
				*piVar9 = param_2;
			}
			else if (*piVar9 == param_2) {
				*piVar9 = param_1;
			}
			piVar9 = piVar9 + 1;
			iVar10 = iVar10 - 1;
		} while (iVar10 != 0);
		piVar16 = (int*) ((char*) piVar16 + 0x21c);
		iStack_44c = iStack_44c - 1;
	} while (iStack_44c != 0);

	for (pNode = *(char**) (buf2 + 0x178); pNode != 0; pNode = *(char**) (pNode + 0x3f)) {
		uVar2 = *(unsigned short*) pNode;
		if (uVar2 != 0 && *(DAT_101de450 + (int) uVar2 * 0x41) == '\t') {
			AddOrAccumulateObject(*(int*) (buf1 + 4), (int) uVar2, *(int*) (pNode + 0xe));
		}
	}

	*(int*) (iVar13 + 0x10035a48) = uVar6;
	*(int*) (iVar13 + 0x10035a34) = 4;
	*(int*) (iVar13 + 0x10035a68) = 0;
	gm_DeallocEntity(*(unsigned short*) buf2, 0);

	return (int) uVar1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 3689
// SYMBOL: _CreateEntityFromParents
// FUNCTION: SERVER 0x10018850
// CreateEntityFromParents

int __cdecl CreateEntityFromParents(int param_1, int param_2, int param_3, int param_4, int param_5)
{
	char local_41c[0x41c];
	int local_10;
	int local_14;
	int local_18;
	int local_1c;
	int local_20;
	int local_24;
	int local_28;

	local_10 = 0;
	local_14 = 0;
	local_18 = 0;
	local_1c = 0;
	local_20 = 0;
	local_24 = 0;
	local_28 = 0;

	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 81
// SYMBOL: _QueryEntitySum
// FUNCTION: SERVER 0x100196c0
// QueryEntitySum

int __cdecl QueryEntitySum(int param_1, unsigned int param_2)
{
	short* ent;
	int total;

	total = 0;
	ent = StartEntityQuery(param_1, 1, 4, 9);
	if (ent != (short*) 0) {
		do {
			if (*(short*) (entity_slot_table + (param_2 & 0xff) * 0x2f4) == *ent) {
				total = total + *(int*) (ent + 7);
			}
			ent = NextEntityQueryMatch();
		} while (ent != (short*) 0);
	}
	return total;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), loop rotation / branch layout, zero-extend pattern (xor vs mov)
// SIZE: 396
// SYMBOL: _CalculateProductionValue
// FUNCTION: SERVER 0x10019720
// CalculateProductionValue

/* Game function - recursive entity value calculation with FPU math */
/* Accesses g_entity_table (0x101de450), calls crt_ftol and itself recursively */
/* Computes weighted entity stat values with caching in field_0x38 */
// BLOCKER_DELTA: 288
// ANALYSIS: Recursive production value calculator. Computes the base value of an object type by looking up prototype data (stride 0x41), applying worker skill bonuses from building prototypes, and recursively summing ingredient costs (up to 4 ingredients). Caches result at proto_entry+0x38. Applies quality and production multipliers.

double __cdecl CalculateProductionValue(int entity_index, int param2)
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
				modifier += (float) bval * DAT_10025fa8 * DAT_10025fa0;
				i++;
			} while (i < 2);
		}
		else {
			modifier = DAT_100257c8;
		}

		{
			unsigned char entity_type = *(unsigned char*) ent;
			modifier *= DAT_100257d0;
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

					sub = CalculateProductionValue((int) slot, p2);
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

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 355
// SYMBOL: _SumBuildingProductionValues
// FUNCTION: SERVER 0x100198b0
// SumBuildingProductionValues

/* Game function - entity query stat accumulator */
/* Iterates entity references in a record, calls CalculateProductionValue for each, accumulates results */
// BLOCKER_DELTA: 308

int __cdecl SumBuildingProductionValues(char* obj, int param2)
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

			query = StartEntityQuery(*(int*) (obj + 0x5d), 1, 0, ent_idx);
			if (!query) {
				goto loop_bottom;
			}

			running_sum =
				(int) (CalculateProductionValue(*(unsigned short*) query, *(unsigned char*) ((char*) query + 0x12)) +
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
				sub_query = StartEntityQuery(*(int*) ((char*) query + 0x14), 1, 0, ent_idx);
				if (sub_query) {
					running_sum = (int) (CalculateProductionValue(
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

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 74
// SYMBOL: _accumulate_typed2
// FUNCTION: SERVER 0x10019A20
// accumulate_typed2

int __cdecl accumulate_typed2(char* entity)
{
	int sum;
	int result;
	unsigned int idx;
	sum = 0;
	idx = (unsigned char) g_type_idx;
	idx = idx * 189;
	result = find_entity(*(int*) (entity + 0x178), 1, 0, (int) *(unsigned short*) &g_key_table[idx]);
	if (result) {
		do {
			sum += *(int*) (result + 0xe);
			result = get_next_entity();
		} while (result);
	}
	return sum;
}

// ORIGIN: GAME
// STATUS: RELOC
// SIZE: 102
// SYMBOL: _EntityQuerySum
// FUNCTION: SERVER 0x10019a70
// EntityQuerySum

int __declspec(naked) __cdecl EntityQuerySum(int param_1)
{
	__asm {
		push ecx
		mov eax, dword ptr [esp + 8]
		push esi
		xor esi, esi
		push 0x2a
		mov ecx, dword ptr [eax + 0x5d]
		push esi
		push 6
		push 2
		push ecx
		mov dword ptr [esp + 0x18], esi
		call StartEntityQuery
		add esp, 0x14
		test eax, eax
		je L_done
		mov edx, dword ptr [eax + 0x14]
		push 5
		push 1
		push edx
		call StartEntityQuery
		add esp, 0xc
		test eax, eax
		je L_done

	L_loop:
		mov cl, byte ptr [eax + 0x12]
		xor edx, edx
		mov dx, word ptr [eax]
		push ecx
		push edx
		call CalculateProductionValue
		fiadd dword ptr [esp + 0xc]
		add esp, 8
		call func_1001b564
		mov esi, eax
		mov dword ptr [esp + 4], esi
		call NextEntityQueryMatch
		test eax, eax
		jne L_loop

	L_done:
		mov eax, esi
		pop esi
		pop ecx
		ret
	}
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 82
// SYMBOL: _ResolveParentEntity
// FUNCTION: SERVER 0x10019ae0
// ResolveParentEntity

short* __cdecl ResolveParentEntity(short* param_1)
{
	void* local_4;

	ResolveEntityById(&local_4, (void**) 0, (void**) &param_1, *(int*) (param_1 + 5));
	if (param_1 == (short*) 0) {
		if (local_4 != (void*) 0 && *(unsigned short*) ((int) local_4 + 0x27) != 0xffff) {
			return (short*) (entity_array + (unsigned int) *(unsigned short*) ((int) local_4 + 0x27) * 0x21c);
		}
		param_1 = (short*) 0;
	}
	return param_1;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 62
// SYMBOL: _GetEntityType
// FUNCTION: SERVER 0x10019b40
// GetEntityType

unsigned short __cdecl GetEntityType(short* param_1)
{
	void* local_4;

	ResolveEntityById(&local_4, (void**) 0, (void**) &param_1, *(int*) (param_1 + 5));
	if (param_1 != (short*) 0) {
		return *param_1;
	}
	if (local_4 != (void*) 0) {
		return *(unsigned short*) ((int) local_4 + 0x27);
	}
	return 0xffff;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 124
// SYMBOL: _entity_accumulate
// FUNCTION: SERVER 0x10019b80
// WalkEntityChain

int __cdecl WalkEntityChain(void* param_1)
{
	int result;
	int entity_id;
	void* local_8;
	void* local_4;

	entity_id = *(int*) ((int) param_1 + 6);
	while (entity_id != -1) {
		result = ResolveEntityById((void**) &param_1, &local_4, &local_8, entity_id);
		if (result == 0) {
			return 0;
		}
		if (param_1 != (void*) 0) {
			return (int) param_1;
		}
		if (local_8 != (void*) 0) {
			return 0;
		}
		if (local_4 != (void*) 0) {
			entity_id = *(int*) ((int) local_4 + 6);
		}
	}
	return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 83
// SYMBOL: _WalkEntityChain
// FUNCTION: SERVER 0x10019BE0
// entity_accumulate

int __cdecl entity_accumulate(int raw_idx)
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
	total = compute_slot_val(slot);
	ent = find_entity_3arg(1, 3, (int) idx);
	if (ent) {
		do {
			total += compute_entity_val(ent, (int) *(signed char*) (ent + 0x5c));
			total += another_entity_val(ent);
			ent = get_next_entity();
		} while (ent);
	}
	return total;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 48
// SYMBOL: _get_msg_field
// FUNCTION: SERVER 0x10019c60
// FindEntityByOwner

/* GLOBAL: SERVER 0x100358a2 */
extern unsigned char g_entity_state_base[];

/* GLOBAL: SERVER 0x100358a0 */

char* __cdecl FindEntityByOwner(int param_1)
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

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 98
// SYMBOL: _FindEntityByOwner
// FUNCTION: SERVER 0x10019CD0
// get_msg_field
int __cdecl get_msg_field(char* msg, char* pkt)
{
	unsigned short type;

	type = *(unsigned short*) msg;
	if (type == 0x2a || type == 0x116 || type == 0x1db || type == 0x1dc) {
		return *(int*) (pkt + 0xe) - 1;
	}
	return *(int*) (pkt + 0xe);
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, loop rotation / branch layout, zero-extend pattern (xor vs mov)
// SIZE: 407
// SYMBOL: _KannObjektHergestellt
// FUNCTION: SERVER 0x10019d30
// KannObjektHergestellt

/* Game function - checks production capacity and entity slot availability */
// BLOCKER_DELTA: 93
// GHIDRA: gm_KannObjektHergestellt

int __cdecl KannObjektHergestellt(char* obj, int entity_index, int requested)
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

	ent = WalkEntityChain(obj);
	if (!ent) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
			0x31de,
			"KannObjektHergestellt(): pCObjekt==NULL",
			1
		);
		return 0;
	}

	category = GetBuildingTypeCategory((unsigned char) *ent);
	is_cat2 = (category == 2);
	max_size = compute_size(obj, entity_index);

	query = StartEntityQuery(*(int*) (obj + 0x14), 1, 0, entity_index);
	if (query) {
		used = get_msg_field(obj, query);
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
		query = StartEntityQuery(*(int*) (obj + 0x14), 1, 5);
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
			query = NextEntityQueryMatch();
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
		query = StartEntityQuery(*(int*) (obj + 0x14), 1, 5);
		while (query) {
			count++;
			query = NextEntityQueryMatch();
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

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 395
// SYMBOL: _CheckInventoryCapacity
// FUNCTION: SERVER 0x10019ed0
// CheckInventoryCapacity

/* Game function - computes available entity slots (capped at 3) */
// BLOCKER_DELTA: 364

int __cdecl CheckInventoryCapacity(char* obj, int entity_index, int requested)
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
		if (LookupEntityInTable(entity_index)) {
			return available;
		}
	}

	if (entity_index == 0x179 || entity_index == 0x17a) {
		return available;
	}

	if (!in_type_list) {
		return available;
	}

	query = StartEntityQuery(*(int*) (obj + 0x178), 1, 0, entity_index);
	if (query) {
		count = *(int*) ((char*) query + 0xe);
		LookupEntityInTable(entity_index);
		if (count + requested > 3) {
			available = 3 - count;
			return (available < 0) ? 0 : available;
		}
		available = requested;
	}
	else {
		query = StartEntityQuery(*(int*) (obj + 0x178), 1, 5);
		count = 0;
		while (query) {
			int result_id;
			char* result_ent;

			result_id = *(unsigned short*) query;
			result_ent = g_entity_table + (result_id << 6) + result_id;
			if (*result_ent != 9) {
				count++;
			}
			query = NextEntityQueryMatch();
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

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 97
// SYMBOL: _entity_set_field
// FUNCTION: SERVER 0x1001A060
// entity_set_field

void __cdecl entity_set_field(void)
{
	int entity;
	int sub;
	entity = search_entity(1, 0, 0x1e);
	if (!entity) {
		return;
	}
	do {
		sub = search_sub(*(int*) (entity + 0x5d), 1, 0, 0xff);
		if (sub) {
			sub = search_sub3(*(int*) (sub + 0x14), 1, 5);
			if (sub) {
				do {
					if (*(int*) (sub + 0xe) != 2) {
						*(int*) (sub + 0xe) = 2;
					}
				} while ((sub = get_next_sub()) != 0);
			}
		}
		entity = get_next_outer();
	} while (entity);
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 54
// SYMBOL: _random_mod
// GHIDRA: RandomBelow
// FUNCTION: SERVER 0x1001A0D0
// random_mod

int __cdecl random_mod(unsigned short n)
{
	if (n) {
		return rand_gen() % n;
	}
	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 22
// SYMBOL: _RandomFloat01
// FUNCTION: SERVER 0x1001a0f0
// RandomFloat01

double __cdecl RandomFloat01(void)
{
	return (double) rand() * (double) _DAT_10025fbc;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 48
// SYMBOL: _RandomQuadratic
// FUNCTION: SERVER 0x1001a110
// RandomQuadratic

float __cdecl RandomQuadratic(void)
{
	float fVar1;

	fVar1 = (float) RandomFloat01();
	fVar1 = (fVar1 + fVar1) - _DAT_100256a0;
	if (fVar1 < _DAT_100256cc) {
		return _DAT_100256a8 * fVar1 * fVar1;
	}
	return _DAT_100256a0 * fVar1 * fVar1;
}
