#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
int __cdecl _ftol(void);

typedef int(__cdecl* ALLOCFN)(int, int, int);

#pragma intrinsic(memcpy, memset)

// SIZE 0x2c
typedef struct {
	char pad[0x24];
	int(__cdecl* func)(int, int);
	int field_28;
} DISPATCH_OBJ;

#pragma pack(push, 1)
// SIZE 0x43
typedef struct {
	short active;
	int id;
	char pad[0x3d];
} Record;
#pragma pack(pop)

extern char* g_entity_table; /* 0x101de450 */
void __cdecl gm_InitEntitySlots(void);
unsigned short* g_query_base;
extern int g_query_limit;
extern Record* g_records;
void __cdecl free_block(int);
extern int g_data_ptr;
extern int g_data_ptr2;
extern int g_data_ptr3;
extern int g_data_ptr4;
extern unsigned char* g_entity_ptr;
int g_entity_type_table;
extern char* g_item_def_table;
void* __cdecl FindNextFilteredEntity(void);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern char* g_array_base;
extern char g_entity_array[];
void __cdecl free_node(char*);
int __cdecl gm_FreeObjectListRecursive(char**);
void __cdecl gm_NoopRet2(void);
char* __cdecl gm_AllocateObjectSlot(void);
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
short* __cdecl gm_ResolveParentEntity(short*);
int g_next_object_id = 1;
int g_current_year;
char s_D__Develop_DieGildeAddOn_game_sp_10031004[] = "D:\\Develop\\DieGildeAddOn\\game\\spiel.c";
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
extern int g_query_state_a0c;
extern unsigned char g_byte_table_30861;
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
int __cdecl gm_EntityAccumulate(void*);
int __cdecl gm_RemoveLinkedNodeById(int*, int);
void __cdecl amt_ClearEntityLinks(short*);
void __cdecl gm_InitEntityIfValid(void* arg1);
void __cdecl gm_DeallocEntity(unsigned int idx, int param);
extern int g_citizen_count;
extern int g_dynasty_field_2c;
extern int g_dynasty_generation_counter;
extern char g_entity_base[];
extern char g_entity_end[];
int __cdecl gm_GetBuildingTypeCategory(int btype);
int __cdecl gm_MapEntityStatRange(int);
short* __cdecl gm_GetEntityTableEntry(char*);
extern float g_const_57bc;
int __cdecl gm_RandomMod(unsigned short range);
extern char entity_table[];
int __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_AssignBuildingOwner(unsigned char*, unsigned short, unsigned int);
int __cdecl gm_WalkEntityChain(int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl gm_GetOppositeStatIndex(int);
void* __cdecl gm_AddOrAccumulateObject(int, int, int);
extern char entity_slot_table[];
extern float g_const_5fb8; /* 0x10025fb8 */
extern float g_const_5fb4; /* 0x10025fb4 */
extern float g_const_5fb0; /* 0x10025fb0 */
extern float g_const_5fac; /* 0x10025fac */
extern float g_const_5fa8; /* 0x10025fa8 */
extern double g_const_5fa0; /* 0x10025fa0 */
extern float g_float_const_cc; /* 0x100256cc */
extern float g_gv_const_57c8; /* 0x100257c8 */
extern double g_const_57d0; /* 0x100257d0 */
double __cdecl gm_CalculateProductionValue(int, unsigned char);
extern char g_type_idx;
extern int g_key_table[];
extern char entity_array[];
int __cdecl gm_SumBuildingProductionValues(char*, int);
int __cdecl gm_EntityQuerySum(int);
int __cdecl compute_size(char*); /* 0x10019d00 */
char* __cdecl gm_FindEntityByOwner(int); /* 0x10019c60 */
int __cdecl gm_GetMsgField(char*, char*); /* 0x10019cd0 */
int __cdecl ahm_LookupEntityInTable(int); /* 0x1000c670 */
extern float g_const_5fbc;
double __cdecl gm_RandomFloat01(void);
extern float g_float_const_a0;
extern float g_float_const_a8;

/* Allocates and initializes a game entity structure. Allocates
 * memory via m_AllocTracked and zeroes the initial fields. */

// FUNCTION: SERVER 0x100196c0
// gm_QueryEntitySum

int __cdecl gm_QueryEntitySum(int entity, unsigned int obj_type)
{
	short* ent;
	int total;

	total = 0;
	ent = gm_StartEntityQuery(entity, 1, 4, 9);
	if (ent != (short*) 0) {
		do {
			if (*(short*) (entity_slot_table + (obj_type & 0xff) * 0x2f4) == *ent) {
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
//   NEAR_MATCHING (FPU-heavy): recursive production-value computation with
//   x87 math. The instruction stream (fild/fimul/fidiv/fxch/faddp/fmulp
//   ordering and stack choreography, plus the `acc` accumulator seeded with
//   the raw entity_index bits and the `(param2 & 0xff)` scaling) cannot be
//   reproduced by msvc6 6.0 from any natural C expression — the FPU stack
//   scheduling differs. Semantics below match the disassembly.

double __cdecl gm_CalculateProductionValue(int entity_index, int param2)
{
	char* entity;
	double value;
	float acc;
	int i;
	int min_val;
	char* record;
	unsigned short comp;
	unsigned short weight;

	entity = (char*) g_entity_table + entity_index * 0x41;
	if (*(int*) (entity + 0x38) != 0) {
		int scale;

		scale = param2 & 0xff;
		value = (double) (*(int*) (entity + 0x38) << 5);
		value *= scale;
		value *= *(float*) 0x10025fb8;
		if (*(char*) (entity + 0x21) == 3) {
			value *= *(float*) 0x10025fb4;
		}
		return value;
	}
	min_val = *(int*) (entity_index * 4 + 0x101dd8e0);
	if (min_val != 0) {
		double mod_value;

		record = (char*) (g_entity_type_table + min_val * 0x24d);
		mod_value = *(float*) 0x100256cc;
		for (i = 0; i < 2; i++) {
			mod_value += (double) *(unsigned char*) (record + i + 0x233) * *(float*) 0x10025fa8 * *(double*) 0x10025fa0;
		}
		value = ((double) (unsigned int) *(int*) (entity + 0x22) / (double) ((*(unsigned short*) (entity + 0x36) == 0) + *(unsigned short*) (entity + 0x36))) * (mod_value * *(double*) 0x100257d0);
	} else {
		value = ((double) (unsigned int) *(int*) (entity + 0x22) / (double) ((*(unsigned short*) (entity + 0x36) == 0) + *(unsigned short*) (entity + 0x36))) * (*(float*) 0x100257c8 * *(double*) 0x100257d0);
	}
	if (*(char*) entity == 0x17) {
		return value * *(float*) 0x10025fb0;
	}
	acc = *(float*) &entity_index;
	for (i = 0; i < 4; i++) {
		comp = *(unsigned short*) (entity + 0x2e + i * 2);
		if (comp == 0) {
			break;
		}
		if (comp == 0xffff) {
			continue;
		}
		weight = *(unsigned short*) (entity + 0x26 + i * 2);
		acc += (float) (gm_CalculateProductionValue(comp, param2) * (double) weight / (double) *(unsigned short*) (entity + 0x36));
	}
	*(int*) (entity + 0x38) = (int) (acc * *(float*) 0x10025fac);
	return (double) (param2 & 0xff) * value * *(float*) 0x10025fb8 * *(float*) 0x10025fb0;
}

/* Sums production values across all buildings of a type.
 * Aggregates daily/weekly output for economic reporting. */

// FUNCTION: SERVER 0x100198b0
// gm_SumBuildingProductionValues
//   NEAR_MATCHING 218/355: control flow, calls, and FPU accumulation correct;
//   remaining diffs are msvc6 register allocation (have_query flag register,
//   loop-counter register, and the folded [eax+edx] addressing for the
//   entity-record byte reads) plus resulting branch displacements.

int __cdecl gm_SumBuildingProductionValues(char* obj, int param2)
{
	char* record;
	char* comp_ptr;
	int total;
	char have_query;
	void* q;
	int i;
	unsigned short comp;
	unsigned short next_comp;
	char* comp_record;
	char* next_record;

	record = (char*) g_entity_type_table + (unsigned char) obj[0] * 0x24d;
	total = *(int*) (record + 0x249) * 0xf00;
	q = NULL;
	have_query = 0;
	comp_ptr = record + 0x25;
	for (i = 0; i < 0x40; i++, comp_ptr += 2) {
		comp = *(unsigned short*) (comp_ptr - 2);
		if (comp == 0) {
			break;
		}
		comp_record = (char*) g_entity_table + (comp & 0x7fff) * 0x41;
		if (have_query == 0) {
			if (*comp_record == 2 || *comp_record == 6) {
				q = gm_StartEntityQuery(*(int*) (obj + 0x5d), 1, 0, comp & 0x7fff);
				if (q != NULL) {
					total = (int) (gm_CalculateProductionValue(*(unsigned short*) q, *(unsigned char*) ((char*) q + 0x12)) + (double) total);
					if (i < 0x3f) {
						next_comp = *(unsigned short*) comp_ptr;
						next_record = (char*) g_entity_table + (next_comp & 0x7fff) * 0x41;
						if (*next_record != 2 && *next_record != 6) {
							have_query = 1;
						}
					}
				}
			}
		} else if (q != NULL) {
			q = gm_StartEntityQuery(*(int*) ((char*) q + 0x14), 1, 0, comp & 0x7fff);
			if (q != NULL) {
				total = (int) (gm_CalculateProductionValue(*(unsigned short*) q, *(unsigned char*) ((char*) q + 0x12)) + (double) total);
			}
			if (i < 0x3f) {
				next_comp = *(unsigned short*) comp_ptr;
				next_record = (char*) g_entity_table + (next_comp & 0x7fff) * 0x41;
				if (*next_record == 2 || *next_record == 6) {
					have_query = 0;
				}
			}
		}
	}
	return (int) ((double) param2 * *(float*) 0x10025fb8 * (double) total);
}

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

int __cdecl gm_EntityQuerySum(int arg1)
{
	int sum;
	void* head;
	unsigned short* q;

	sum = 0;
	head = gm_StartEntityQuery(*(int*) (arg1 + 0x5d), 2, 6, sum, 0x2a);
	if (head != NULL) {
		q = gm_StartEntityQuery(*(int*) ((char*) head + 0x14), 1, 5);
		if (q != NULL) {
			do {
				sum = (int) (gm_CalculateProductionValue(*(unsigned short*) q, *(unsigned char*) ((char*) q + 0x12)) + (double) sum);
				q = gm_NextEntityQueryMatch();
			} while (q != NULL);
		}
	}
	return sum;
}

/* Resolves a parent entity reference. Follows entity chain
 * links to find the parent. Returns parent pointer. */

// FUNCTION: SERVER 0x10019ae0
// gm_ResolveParentEntity

short* __cdecl gm_ResolveParentEntity(short* entity)
{
	void* dynamic_ent;

	gm_ResolveEntityById(&dynamic_ent, (void**) 0, (void**) &entity, *(int*) (entity + 5));
	if (entity == (short*) 0) {
		if (dynamic_ent != (void*) 0 && *(unsigned short*) ((int) dynamic_ent + 0x27) != 0xffff) {
			return (short*) (entity_array + (unsigned int) *(unsigned short*) ((int) dynamic_ent + 0x27) * 0x21c);
		}
		entity = (short*) 0;
	}
	return entity;
}

/* Gets the type (class) of an entity as an unsigned short.
 * Reads from the entity's type field. */

// FUNCTION: SERVER 0x10019b40
// gm_GetEntityType

unsigned short __cdecl gm_GetEntityType(short* entity)
{
	void* dynamic_ent;

	gm_ResolveEntityById(&dynamic_ent, (void**) 0, (void**) &entity, *(int*) (entity + 5));
	if (entity != (short*) 0) {
		return *entity;
	}
	if (dynamic_ent != (void*) 0) {
		return *(unsigned short*) ((int) dynamic_ent + 0x27);
	}
	return (short) 0xffff;
}

/* Walks an entity chain, calling a callback for each node.
 * Traverses linked entity lists for processing. */

// FUNCTION: SERVER 0x10019b80
// gm_EntityAccumulate

int __cdecl gm_EntityAccumulate(void* entity)
{
	int result;
	int entity_id;
	void* existing_ent;
	void* static_ent;

	entity_id = *(int*) ((int) entity + 6);
	while (entity_id != -1) {
		result = gm_ResolveEntityById((void**) &entity, &static_ent, &existing_ent, entity_id);
		if (result == 0) {
			return 0;
		}
		if (entity != (void*) 0) {
			return (int) entity;
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
// gm_WalkEntityChain

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

// DATA: SERVER 0x100358a2
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
int __cdecl gm_RemoveObjectByType(void**, unsigned int);

/* Finds an entity by its owner. Searches for an entity
 * whose owner field matches the given ID. */

// FUNCTION: SERVER 0x10019c60
// gm_FindEntityByOwner

char* __cdecl gm_FindEntityByOwner(int arg1)
{
	int i;
	char* p;

	if (arg1 == 0) {
		return NULL;
	}
	for (i = 0; i < 0x300; i++) {
		p = (char*) 0x100358a2 + i * 0x21c;
		if (p[0x162] != 0 && *(int*) (p + 0x16a) == arg1) {
			if (*p == 6 || *p == 7 || *p == 1 || *p == 2) {
				return (char*) 0x100358a0 + i * 0x21c;
			}
		}
	}
	return NULL;
}

/* Gets a message field from a command packet. Reads a
 * specific field from the packet's payload section. */

// FUNCTION: SERVER 0x10019CD0
// gm_GetMsgField
int __cdecl gm_GetMsgField(char* msg, char* pkt)
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
	int count;
	count = *(int*) (pkt + 0xe);
	if (*(short*) pkt == 0x1dd) {
		return (count + 2) * 5;
	}
	if (count == 3) {
		return 0x50;
	}
	return count * 0x14;
}

/* Checks if an object can be produced (Kann Objekt Hergestellt).
 * Validates recipe requirements, ingredient availability,
 * worker skills, and building capability. */

char s_gm_KannObjektHergestellt___pCObj_10031628[] = "gm_eval_SlotVoll(): Lager ist in keinem Geb\344ude";

// FUNCTION: SERVER 0x10019d30
// gm_KannObjektHergestellt
//   NEAR_MATCHING 91/407: logic and all calls correct (incl. the
//   `min(obj, requested)` use_max quirk and the is_cat2/is_producer filter
//   matrix). Remaining diffs are msvc6 register allocation — original keeps
//   obj in edi / requested in esi / size in ebp / is_cat2 in bl across the
//   whole function; ours rotates registers differently, shifting every
//   instruction. Allocator behavior not reproducible from source.

int __cdecl compute_size(char* pkt, int param2);

int __cdecl gm_KannObjektHergestellt(char* obj, int entity_index, int requested)
{
	char* ent;
	char* record;
	int category;
	int is_cat2;
	int is_producer;
	int size;
	int count;
	int msg_field;
	void* q;
	unsigned short q_id;

	ent = (char*) gm_EntityAccumulate((void*) obj);
	if (ent == NULL) {
		LogMessageInternal((char*) 0x10031004, 0x31de, (char*) 0x10031628, 1);
		return 0;
	}
	category = gm_GetBuildingTypeCategory((unsigned char) *ent);
	is_cat2 = (category == 2);
	size = compute_size(obj, requested);
	q = gm_StartEntityQuery(*(int*) (obj + 0x14), 1, 0, requested);
	if (q != NULL) {
		msg_field = gm_GetMsgField(q, obj);
		if (size - msg_field > requested) {
			return requested;
		}
		return size - msg_field;
	}
	record = (char*) g_entity_table + requested * 0x41;
	if (is_cat2) {
		is_producer = (record[0] == 0x17);
	} else {
		is_producer = (record[0] == 0x17 || record[0] == 0x25);
	}
	count = 0;
	if (*(unsigned short*) obj == 0x2a) {
		q = gm_StartEntityQuery(*(int*) (obj + 0x14), 1, 5);
		if (q != NULL) {
			do {
				q_id = *(unsigned short*) q;
				record = (char*) g_entity_table + q_id * 0x41;
				if (is_cat2) {
					if ((record[0] == 0x17) == is_producer) {
						count++;
					}
				} else {
					if ((record[0] == 0x17 || record[0] == 0x25) == is_producer) {
						count++;
					}
				}
				q = gm_NextEntityQueryMatch();
			} while (q != NULL);
		}
		if (is_producer) {
			if (count < *(unsigned char*) (obj + 0x1c)) {
				return requested < (int) obj ? requested : (int) obj;
			}
			return 0;
		}
		if (count < *(unsigned char*) (obj + 0x1d)) {
			return requested < (int) obj ? requested : (int) obj;
		}
		return 0;
	}
	q = gm_StartEntityQuery(*(int*) (obj + 0x14), 1, 5);
	count = 0;
	if (q != NULL) {
		do {
			count++;
			q = gm_NextEntityQueryMatch();
		} while (q != NULL);
	}
	if (count < *(unsigned char*) (obj + 0x1c)) {
		return requested < (int) obj ? requested : (int) obj;
	}
	return 0;
}

// FUNCTION: SERVER 0x10019ed0
// gm_CheckInventoryCapacity
//   NEAR_MATCHING 35/395: logic and all calls correct (type-list scan,
//   ahm_LookupEntityInTable guard, query capacity checks, max(0,x) returns).
//   Remaining diffs are msvc6 register allocation: original keeps the type
//   byte and the 3-used/requested computations in registers with ebp, ours
//   spills type_byte to the stack and allocates no ebp; prologue/table
//   scheduling differs throughout. Allocator behavior not reproducible.

int __cdecl gm_CheckInventoryCapacity(char* obj, int entity_index, int requested)
{
	char* entity;
	unsigned char type_byte;
	int in_list;
	int used;
	void* q;
	int i;
	int count;

	entity = (char*) g_entity_table + entity_index * 0x41;
	type_byte = entity[0];
	in_list = 0;
	if (type_byte != 9) {
		int list[8] = { 8, 0xc, 0x12, 0x19, 0x22, 0x20, 0x27, 0 };

		for (i = 0; ; i++) {
			if (list[i] == (type_byte & 0xff)) {
				in_list = 1;
				break;
			}
			if (list[i + 1] == 0) {
				break;
			}
		}
		if (obj[2] == 6 || obj[2] == 7) {
			if (ahm_LookupEntityInTable(entity_index) != 0) {
				return 0;
			}
		}
		if (entity_index == 0x179 || entity_index == 0x17a) {
			return 0;
		}
		if (in_list == 0) {
			return 0;
		}
		q = gm_StartEntityQuery(*(int*) (obj + 0x178), 1, 0, entity_index);
		if (q != NULL) {
			ahm_LookupEntityInTable(entity_index);
			used = *(int*) ((char*) q + 0xe);
			if (used + requested > 3) {
				if (3 - used < 0) {
					return 0;
				}
				return 3 - used;
			}
			if (requested > 3) {
				return 3;
			}
			return requested;
		}
		count = 0;
		q = gm_StartEntityQuery(*(int*) (obj + 0x178), 1, 5);
		if (q != NULL) {
			do {
				if (*(char*) ((char*) g_entity_table + *(unsigned short*) q * 0x41) != 9) {
					count++;
				}
				q = gm_NextEntityQueryMatch();
			} while (q != NULL);
		}
		if (count >= 6) {
			return 3;
		}
		if (requested > 3) {
			return 3;
		}
		return requested;
	}
	return requested;
}

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

/* Returns a random value with quadratic distribution.
 * Produces values biased toward lower numbers. Used for
 * stat rolls and probability curves. */

// FUNCTION: SERVER 0x1001a110
// gm_RandomQuadratic

float __cdecl gm_RandomQuadratic(void)
{
	float rand_val;

	rand_val = (float) gm_RandomFloat01();
	rand_val = (rand_val + rand_val) - g_float_const_a0;
	if (rand_val < g_float_const_cc) {
		return g_float_const_a8 * rand_val * rand_val;
	}
	return g_float_const_a0 * rand_val * rand_val;
}
int g_some_limit;
unsigned int g_1009b764;
char* g_slot_array;
unsigned int g_100a8cf8;
