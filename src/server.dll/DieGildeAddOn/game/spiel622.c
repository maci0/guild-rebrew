#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
int __cdecl __ftol(void);

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
double __cdecl gm_CalculateProductionValue(int, int);
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

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
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

/* Game function - recursive entity value calculation with FPU math */
/* Accesses g_entity_table (0x101de450), calls __ftol and itself recursively */
/* Computes weighted entity stat values with caching in field_0x38 */

__declspec(naked) double __cdecl gm_CalculateProductionValue(int entity_index, int param2)
{
	(void) entity_index;
	(void) param2;
	__asm {
		mov ecx, dword ptr [esp + 4]
		_emit 0x8b
		_emit 0x15
		_emit 0x50
		_emit 0xe4
		_emit 0x1d
		_emit 0x10
		sub esp, 8
		mov eax, ecx
		shl eax, 6
		push ebx
		push esi
		add edx, eax
		mov esi, ecx
		add esi, edx
		xor ebx, ebx
		mov eax, dword ptr [esi + 0x38]
		cmp eax, ebx
		je L_compute
		shl eax, 5
		mov dword ptr [esp + 0x14], eax
		mov eax, dword ptr [esp + 0x18]
		fild dword ptr [esp + 0x14]
		and eax, 0xff
		mov dword ptr [esp + 0x18], eax
		mov al, byte ptr [esi + 0x21]
		fimul dword ptr [esp + 0x18]
		cmp al, 3
		_emit 0xd8
		_emit 0x0d
		_emit 0xb8
		_emit 0x5f
		_emit 0x02
		_emit 0x10
		jne near L_pop_done
		_emit 0xd8
		_emit 0x0d
		_emit 0xb4
		_emit 0x5f
		_emit 0x02
		_emit 0x10
		pop esi
		pop ebx
		add esp, 8
		ret
	L_compute:
		mov edx, dword ptr [esi + 0x22]
		mov ax, word ptr [esi + 0x36]
		mov dword ptr [esp + 8], edx
		xor edx, edx
		cmp ax, bx
		mov dword ptr [esp + 0xc], ebx
		sete dl
		and eax, 0xffff
		add edx, eax
		mov eax, dword ptr [ecx*4 + 0x101dd8e0]
		fild qword ptr [esp + 8]
		lea ecx, [eax + eax*2]
		mov dword ptr [esp + 0x14], edx
		_emit 0x8b
		_emit 0x15
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		fidiv dword ptr [esp + 0x14]
		shl ecx, 4
		add ecx, eax
		add edx, eax
		cmp eax, ebx
		lea ecx, [ecx + ecx*2]
		lea ecx, [edx + ecx*4]
		je L_no_record
		_emit 0xd9
		_emit 0x05
		_emit 0xcc
		_emit 0x56
		_emit 0x02
		_emit 0x10
		xor eax, eax
	L_mod_loop:
		xor edx, edx
		mov dl, byte ptr [ecx + eax + 0x233]
		inc eax
		mov dword ptr [esp + 0x14], edx
		cmp eax, 2
		fild dword ptr [esp + 0x14]
		_emit 0xd8
		_emit 0x0d
		_emit 0xa8
		_emit 0x5f
		_emit 0x02
		_emit 0x10
		_emit 0xdc
		_emit 0x0d
		_emit 0xa0
		_emit 0x5f
		_emit 0x02
		_emit 0x10
		fxch st(1)
		faddp st(1), st
		jl L_mod_loop
		jmp L_have_mod
	L_no_record:
		_emit 0xd9
		_emit 0x05
		_emit 0xc8
		_emit 0x57
		_emit 0x02
		_emit 0x10
	L_have_mod:
		_emit 0xdc
		_emit 0x0d
		_emit 0xd0
		_emit 0x57
		_emit 0x02
		_emit 0x10
		fxch st(1)
		cmp byte ptr [esi], 0x17
		fmulp st(1), st
		fstp dword ptr [esp + 0x14]
		jne L_recurse
		fld dword ptr [esp + 0x14]
		_emit 0xd8
		_emit 0x0d
		_emit 0xb0
		_emit 0x5f
		_emit 0x02
		_emit 0x10
		pop esi
		pop ebx
		add esp, 8
		ret
	L_recurse:
		push ebp
		mov ebp, dword ptr [esp + 0x1c]
		push edi
		lea edi, [esi + 0x2e]
	L_rec_loop:
		mov ax, word ptr [edi]
		test ax, ax
		je L_rec_done
		cmp ax, 0xffff
		je L_rec_next
		and eax, 0xffff
		push ebp
		push eax
		call gm_CalculateProductionValue
		xor eax, eax
		add esp, 8
		mov ax, word ptr [edi - 8]
		xor ecx, ecx
		mov cx, word ptr [esi + 0x36]
		mov dword ptr [esp + 0x20], eax
		fimul dword ptr [esp + 0x20]
		mov dword ptr [esp + 0x20], ecx
		fidiv dword ptr [esp + 0x20]
		fadd dword ptr [esp + 0x1c]
		fstp dword ptr [esp + 0x1c]
	L_rec_next:
		inc ebx
		add edi, 2
		cmp ebx, 4
		jl L_rec_loop
	L_rec_done:
		fld dword ptr [esp + 0x1c]
		_emit 0xd8
		_emit 0x0d
		_emit 0xac
		_emit 0x5f
		_emit 0x02
		_emit 0x10
		call __ftol
		and ebp, 0xff
		pop edi
		mov dword ptr [esp + 0x1c], ebp
		mov dword ptr [esi + 0x38], eax
		fild dword ptr [esp + 0x1c]
		pop ebp
		fmul dword ptr [esp + 0x14]
		_emit 0xd8
		_emit 0x0d
		_emit 0xb8
		_emit 0x5f
		_emit 0x02
		_emit 0x10
		_emit 0xd8
		_emit 0x0d
		_emit 0xb0
		_emit 0x5f
		_emit 0x02
		_emit 0x10
	L_pop_done:
		pop esi
		pop ebx
		add esp, 8
		ret
	}
}

/* Sums production values across all buildings of a type.
 * Aggregates daily/weekly output for economic reporting. */

// FUNCTION: SERVER 0x100198b0
// gm_SumBuildingProductionValues

/* Game function - entity query stat accumulator */
/* Iterates entity references in a record, calls gm_CalculateProductionValue for each, accumulates results */

__declspec(naked) int __cdecl gm_SumBuildingProductionValues(char* obj, int param2)
{
	(void) obj;
	(void) param2;
	__asm {
		push ecx
		mov eax, dword ptr [esp + 8]
		xor ecx, ecx
		push ebx
		push ebp
		mov cl, byte ptr [eax]
		push esi
		push edi
		xor esi, esi
		lea eax, [ecx + ecx*2]
		xor bl, bl
		shl eax, 4
		add eax, ecx
		lea edx, [eax + eax*2]
		_emit 0xa1
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		add eax, ecx
		mov ecx, dword ptr [eax + edx*4 + 0x249]
		lea eax, [eax + edx*4]
		imul ecx, ecx, 0xf00
		mov dword ptr [esp + 0x10], ecx
		xor ebp, ebp
		lea edi, [eax + 0x25]
	L_loop:
		mov ax, word ptr [edi - 2]
		test ax, ax
		je near L_exit
		_emit 0x8b
		_emit 0x15
		_emit 0x50
		_emit 0xe4
		_emit 0x1d
		_emit 0x10
		and eax, 0x7fff
		mov ecx, eax
		shl ecx, 6
		add edx, ecx
		mov ecx, eax
		add ecx, edx
		test bl, bl
		jne L_have_query
		mov cl, byte ptr [ecx]
		cmp cl, 2
		je L_call_q
		cmp cl, 6
		jne near L_loop_next
	L_call_q:
		push eax
		mov eax, dword ptr [esp + 0x1c]
		push 0
		push 1
		mov ecx, dword ptr [eax + 0x5d]
		push ecx
		call gm_StartEntityQuery
		mov esi, eax
		add esp, 0x10
		test esi, esi
		je near L_loop_next
		mov dl, byte ptr [esi + 0x12]
		xor eax, eax
		mov ax, word ptr [esi]
		push edx
		push eax
		call gm_CalculateProductionValue
		fiadd dword ptr [esp + 0x18]
		add esp, 8
		call __ftol
		cmp ebp, 0x3f
		mov dword ptr [esp + 0x10], eax
		jge near L_loop_next
		mov ax, word ptr [edi]
		_emit 0x8b
		_emit 0x15
		_emit 0x50
		_emit 0xe4
		_emit 0x1d
		_emit 0x10
		and eax, 0x7fff
		mov ecx, eax
		shl ecx, 6
		add edx, ecx
		mov al, byte ptr [eax + edx]
		cmp al, 2
		je L_loop_next
		cmp al, 6
		je L_loop_next
		mov bl, 1
		jmp L_loop_next
	L_have_query:
		test esi, esi
		je L_loop_next
		push eax
		mov eax, dword ptr [esi + 0x14]
		push 0
		push 1
		push eax
		call gm_StartEntityQuery
		add esp, 0x10
		test eax, eax
		je L_sub_skip
		mov cl, byte ptr [eax + 0x12]
		xor edx, edx
		mov dx, word ptr [eax]
		push ecx
		push edx
		call gm_CalculateProductionValue
		fiadd dword ptr [esp + 0x18]
		add esp, 8
		call __ftol
		mov dword ptr [esp + 0x10], eax
	L_sub_skip:
		cmp ebp, 0x3f
		jge L_loop_next
		mov ax, word ptr [edi]
		_emit 0x8b
		_emit 0x15
		_emit 0x50
		_emit 0xe4
		_emit 0x1d
		_emit 0x10
		and eax, 0x7fff
		mov ecx, eax
		shl ecx, 6
		add edx, ecx
		mov al, byte ptr [eax + edx]
		cmp al, 2
		je L_clear_q
		cmp al, 6
		jne L_loop_next
	L_clear_q:
		xor bl, bl
	L_loop_next:
		inc ebp
		add edi, 2
		cmp ebp, 0x40
		jl near L_loop
	L_exit:
		fild dword ptr [esp + 0x1c]
		_emit 0xd8
		_emit 0x0d
		_emit 0xb8
		_emit 0x5f
		_emit 0x02
		_emit 0x10
		fimul dword ptr [esp + 0x10]
		call __ftol
		pop edi
		pop esi
		pop ebp
		pop ebx
		pop ecx
		ret
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

__declspec(naked) int __cdecl gm_EntityQuerySum(int arg1)
{
	(void) arg1;
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
		call gm_StartEntityQuery
		add esp, 0x14
		test eax, eax
		je L_done
		mov edx, dword ptr [eax + 0x14]
		push 5
		push 1
		push edx
		call gm_StartEntityQuery
		add esp, 0xc
		test eax, eax
		je L_done
	L_loop:
		mov cl, byte ptr [eax + 0x12]
		xor edx, edx
		mov dx, word ptr [eax]
		push ecx
		push edx
		call gm_CalculateProductionValue
		fiadd dword ptr [esp + 0xc]
		add esp, 8
		call __ftol
		mov esi, eax
		mov dword ptr [esp + 4], esi
		call gm_NextEntityQueryMatch
		test eax, eax
		jne L_loop
	L_done:
		mov eax, esi
		pop esi
		pop ecx
		ret
	}
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
__declspec(naked) char* __cdecl gm_FindEntityByOwner(int arg1)
{
	(void) arg1;
	__asm {
		push edi
		mov edi, dword ptr [esp + 8]
		xor eax, eax
		test edi, edi
		jne L_start
		pop edi
		ret
	L_start:
		push esi
		xor esi, esi
		mov ecx, 0x100358a2
	L_loop:
		mov dl, byte ptr [ecx + 0x162]
		test dl, dl
		je L_next
		cmp dword ptr [ecx + 0x16a], edi
		jne L_next
		mov dl, byte ptr [ecx]
		cmp dl, 6
		je L_found
		cmp dl, 7
		je L_found
		cmp dl, 1
		je L_found
		cmp dl, 2
		je L_found
	L_next:
		add ecx, 0x21c
		inc esi
		cmp ecx, 0x1009aca2
		jl L_loop
		pop esi
		pop edi
		ret
	L_found:
		lea eax, [esi + esi*2]
		pop esi
		pop edi
		lea eax, [eax + eax*4]
		lea eax, [eax + eax*8]
		lea eax, [eax*4 + 0x100358a0]
		ret
	}
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

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) int __cdecl compute_size(char* pkt)
{
	__asm {
		_emit 0x8b
		_emit 0x44
		_emit 0x24
		_emit 0x04
		_emit 0x66
		_emit 0x81
		_emit 0x38
		_emit 0xdd
		_emit 0x01
		_emit 0x8b
		_emit 0x40
		_emit 0x0e
		_emit 0x75
		_emit 0x07
		_emit 0x83
		_emit 0xc0
		_emit 0x02
		_emit 0x8d
		_emit 0x04
		_emit 0x80
		_emit 0xc3
		_emit 0x83
		_emit 0xf8
		_emit 0x03
		_emit 0x75
		_emit 0x06
		_emit 0xb8
		_emit 0x50
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0xc3
		_emit 0x8d
		_emit 0x04
		_emit 0x80
		_emit 0xc1
		_emit 0xe0
		_emit 0x02
		_emit 0xc3
	}
}
#else
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
#endif

/* Checks if an object can be produced (Kann Objekt Hergestellt).
 * Validates recipe requirements, ingredient availability,
 * worker skills, and building capability. */

char s_gm_KannObjektHergestellt___pCObj_10031628[] = "gm_eval_SlotVoll(): Lager ist in keinem Geb\344ude";

// FUNCTION: SERVER 0x10019d30
// gm_KannObjektHergestellt

__declspec(naked) int __cdecl gm_KannObjektHergestellt(char* obj, int entity_index, int requested)
{
	(void) obj;
	(void) entity_index;
	(void) requested;
	__asm {
		push ebx
		push ebp
		push esi
		push edi
		mov edi, dword ptr [esp + 0x14]
		push edi
		call gm_EntityAccumulate
		add esp, 4
		test eax, eax
		jne L_have_ent
		push 1
		push offset s_gm_KannObjektHergestellt___pCObj_10031628
		push 0x31de
		push offset s_D__Develop_DieGildeAddOn_game_sp_10031004
		call LogMessageInternal
		add esp, 0x10
		xor eax, eax
		pop edi
		pop esi
		pop ebp
		pop ebx
		ret
	L_have_ent:
		xor ecx, ecx
		mov cl, byte ptr [eax]
		push ecx
		call gm_GetBuildingTypeCategory
		mov esi, dword ptr [esp + 0x1c]
		xor ebx, ebx
		cmp eax, 2
		push esi
		push edi
		sete bl
		call compute_size
		mov edx, dword ptr [edi + 0x14]
		push esi
		push 0
		mov ebp, eax
		push 1
		push edx
		mov dword ptr [esp + 0x30], ebp
		call gm_StartEntityQuery
		add esp, 0x1c
		test eax, eax
		je L_no_query
		push eax
		push edi
		call gm_GetMsgField
		mov ecx, ebp
		add esp, 8
		sub ecx, eax
		mov eax, dword ptr [esp + 0x1c]
		cmp ecx, eax
		jg near L_done
		pop edi
		pop esi
		pop ebp
		mov eax, ecx
		pop ebx
		ret
	L_no_query:
		_emit 0x8b
		_emit 0x0d
		_emit 0x50
		_emit 0xe4
		_emit 0x1d
		_emit 0x10
		mov eax, esi
		shl eax, 6
		add ecx, eax
		add esi, ecx
		test ebx, ebx
		je L_not_cat2
		mov al, byte ptr [esi]
		xor edx, edx
		cmp al, 0x17
		sete dl
		mov ebp, edx
		jmp L_after_producer
	L_not_cat2:
		mov al, byte ptr [esi]
		cmp al, 0x17
		je L_is_producer
		cmp al, 0x25
		je L_is_producer
		xor ebp, ebp
		jmp L_after_producer
	L_is_producer:
		mov ebp, 1
	L_after_producer:
		cmp word ptr [edi], 0x2a
		jne near L_not_2a
		mov eax, dword ptr [edi + 0x14]
		push 5
		push 1
		push eax
		xor esi, esi
		call gm_StartEntityQuery
		add esp, 0xc
		test eax, eax
		je L_query_done
	L_iter:
		xor ecx, ecx
		mov cx, word ptr [eax]
		_emit 0xa1
		_emit 0x50
		_emit 0xe4
		_emit 0x1d
		_emit 0x10
		mov edx, ecx
		shl edx, 6
		add eax, edx
		add ecx, eax
		test ebx, ebx
		je L_check_no_cat2
		mov al, byte ptr [ecx]
		test ebp, ebp
		je L_check_not_producer
		cmp al, 0x17
		jne L_skip
		jmp L_count
	L_check_not_producer:
		cmp al, 0x17
		je L_skip
		jmp L_count
	L_check_no_cat2:
		mov cl, byte ptr [ecx]
		test ebp, ebp
		je L_check_no_cat2_notprod
		cmp cl, 0x17
		je L_count
		cmp cl, 0x25
		jne L_skip
		jmp L_count
	L_check_no_cat2_notprod:
		cmp cl, 0x17
		je L_skip
		cmp cl, 0x25
		je L_skip
	L_count:
		inc esi
	L_skip:
		call gm_NextEntityQueryMatch
		test eax, eax
		jne L_iter
	L_query_done:
		test ebp, ebp
		je L_use_1d
		xor ecx, ecx
		mov cl, byte ptr [edi + 0x1c]
		cmp esi, ecx
		jl L_use_max
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		ret
	L_use_1d:
		xor edx, edx
		mov dl, byte ptr [edi + 0x1d]
		cmp esi, edx
		jl L_use_max
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		ret
	L_not_2a:
		mov eax, dword ptr [edi + 0x14]
		push 5
		push 1
		push eax
		xor esi, esi
		call gm_StartEntityQuery
		add esp, 0xc
		test eax, eax
		je L_count_done
	L_count_loop:
		inc esi
		call gm_NextEntityQueryMatch
		test eax, eax
		jne L_count_loop
	L_count_done:
		xor ecx, ecx
		mov cl, byte ptr [edi + 0x1c]
		cmp esi, ecx
		jl L_use_max
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		ret
	L_use_max:
		mov eax, dword ptr [esp + 0x1c]
		mov ecx, dword ptr [esp + 0x14]
		cmp ecx, eax
		jge L_done
		mov eax, ecx
	L_done:
		pop edi
		pop esi
		pop ebp
		pop ebx
		ret
	}
}

/* Checks inventory capacity. Verifies whether an entity's
 * inventory has room for additional objects of a given type. */

// FUNCTION: SERVER 0x10019ed0
// gm_CheckInventoryCapacity

/* Game function - computes available entity slots (capped at 3) */

__declspec(naked) int __cdecl gm_CheckInventoryCapacity(char* obj, int entity_index, int requested)
{
	(void) obj;
	(void) entity_index;
	(void) requested;
	__asm {
		sub esp, 0x20
		push ebx
		_emit 0x8b
		_emit 0x0d
		_emit 0x50
		_emit 0xe4
		_emit 0x1d
		_emit 0x10
		push ebp
		push esi
		push edi
		mov edi, dword ptr [esp + 0x38]
		mov eax, edi
		xor ebp, ebp
		shl eax, 6
		add ecx, eax
		mov eax, edi
		add eax, ecx
		xor esi, esi
		mov dword ptr [esp + 0x10], 8
		mov dword ptr [esp + 0x14], 0xc
		mov al, byte ptr [eax]
		mov dword ptr [esp + 0x18], 0x12
		cmp al, 9
		mov dword ptr [esp + 0x1c], 0x19
		mov dword ptr [esp + 0x20], 0x22
		mov dword ptr [esp + 0x24], 0x20
		mov dword ptr [esp + 0x28], 0x27
		mov dword ptr [esp + 0x2c], ebp
		jne L_not9
		mov eax, dword ptr [esp + 0x3c]
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x20
		ret
	L_not9:
		mov edx, eax
		mov eax, 8
		and edx, 0xff
		lea ecx, [esp + 0x10]
	L_scan:
		cmp eax, edx
		je L_in_list
		mov eax, dword ptr [ecx + 4]
		add ecx, 4
		cmp eax, ebp
		jne L_scan
		jmp L_scan_done
	L_in_list:
		mov esi, 1
	L_scan_done:
		mov ebx, dword ptr [esp + 0x34]
		mov al, byte ptr [ebx + 2]
		cmp al, 6
		je L_check_ahm
		cmp al, 7
		jne L_check_idx
	L_check_ahm:
		push edi
		call ahm_LookupEntityInTable
		add esp, 4
		test eax, eax
		jne near L_ret_zero
	L_check_idx:
		cmp edi, 0x179
		je near L_ret_zero
		cmp edi, 0x17a
		je near L_ret_zero
		test esi, esi
		je near L_ret_zero
		mov edx, dword ptr [ebx + 0x178]
		push edi
		push 0
		push 1
		push edx
		call gm_StartEntityQuery
		mov esi, eax
		add esp, 0x10
		test esi, esi
		je L_no_q
		push edi
		call ahm_LookupEntityInTable
		mov esi, dword ptr [esi + 0xe]
		mov eax, dword ptr [esp + 0x40]
		add esp, 4
		lea ecx, [esi + eax]
		cmp ecx, 3
		jle L_use_req
		mov ebp, 3
		xor eax, eax
		sub ebp, esi
		pop edi
		test ebp, ebp
		setl al
		dec eax
		pop esi
		and eax, ebp
		pop ebp
		pop ebx
		add esp, 0x20
		ret
	L_no_q:
		mov edx, dword ptr [ebx + 0x178]
		push 5
		push 1
		push edx
		xor esi, esi
		call gm_StartEntityQuery
		add esp, 0xc
		test eax, eax
		je L_after_q2
	L_q2_loop:
		_emit 0x8b
		_emit 0x15
		_emit 0x50
		_emit 0xe4
		_emit 0x1d
		_emit 0x10
		xor ecx, ecx
		mov cx, word ptr [eax]
		mov eax, ecx
		shl eax, 6
		add edx, eax
		cmp byte ptr [ecx + edx], 9
		je L_q2_skip
		inc esi
	L_q2_skip:
		call gm_NextEntityQueryMatch
		test eax, eax
		jne L_q2_loop
		cmp esi, 6
		jge L_use_3
	L_after_q2:
		mov eax, dword ptr [esp + 0x3c]
		mov ebp, 3
		cmp eax, 3
		jg L_use_3
	L_use_req:
		mov ebp, eax
	L_use_3:
		xor eax, eax
		pop edi
		test ebp, ebp
		setl al
		dec eax
		pop esi
		and eax, ebp
		pop ebp
		pop ebx
		add esp, 0x20
		ret
	L_ret_zero:
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		add esp, 0x20
		ret
	}
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
	return (double) rand() * (double) g_const_5fbc;
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
