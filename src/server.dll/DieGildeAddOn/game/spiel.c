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
;
void __cdecl gm_InitObjektHersteller(void);
void __cdecl gm_InitEntitySlots(void);
int __cdecl _getpid(void);
extern char* g_entity_ptr;
void __cdecl vfs_EntityCleanup(char*);
extern unsigned short* g_query_base;
extern int g_query_limit;
extern Record* g_records;
void __cdecl free_block(int);
extern int g_data_ptr;
extern int g_data_ptr2;
extern int g_data_ptr3;
extern int g_data_ptr4;
extern char* g_game_initialized;
extern unsigned char* g_entity_array_ptr;
extern int g_entity_type_table;
extern unsigned char g_current_season;
extern int g_active_player_count;
extern char* g_item_def_table;
void* __cdecl FindNextFilteredEntity(void);
int __cdecl gm_CleanupBuildingEntity(unsigned char*);
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_AllocObjekt(int, int, int);
extern unsigned short* g_query_cursor;
extern char g_query_active;
extern char g_query_flag2;
extern int g_query_count;
extern int g_query_filter_max_id;
extern int g_query_filter_owner;
extern short g_query_filter_type;
extern char g_query_filter_state;
extern char g_query_flag1;
extern char g_query_flag3;
extern int g_query_match_count;
extern int* g_dispatch_table_b;
extern int* g_dispatch_table_a;
extern char* g_array_base;
// DATA: SERVER 0x100358a0
extern char g_entity_array[];
void __cdecl free_node(char*);
int __cdecl gm_FreeObjectListRecursive(char**);
void __cdecl gm_NoopRet2(void);
char* __cdecl gm_AllocateObjectSlot(void);
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
short* __cdecl gm_ResolveParentEntity(short*);
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
extern char g_10031004[];
extern char g_10031484[];
extern char g_100314b8[];
int __cdecl gm_EntityAccumulate(void*);
int __cdecl gm_RemoveLinkedNodeById(int*, int);
void __cdecl amt_ClearEntityLinks(short*);
void __cdecl gm_InitEntityIfValid(void* arg1);
void __cdecl gm_DeallocEntity(unsigned int idx, int param);
extern int g_citizen_count;
extern int DAT_1003542c;
extern int DAT_10035430;
extern char g_entity_base[];
extern char g_entity_end[];
int __cdecl gm_GetBuildingTypeCategory(int btype);
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
char* __cdecl gm_FindEntityByOwner(int); /* 0x10019c60 */
int __cdecl gm_GetMsgField(char*, char*); /* 0x10019cd0 */
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

// DATA: SERVER 0x100a8c30
// DATA: SERVER 0x1014d8c0
extern int g_1014d8c0;
// DATA: SERVER 0x101de450
// DATA: SERVER 0x100a8c34
extern int g_100a8c34;

// DATA: SERVER 0x100a8cf8
extern int g_100a8cf8;
// DATA: SERVER 0x1009b764
extern int g_1009b764;
// DATA: SERVER 0x1002dde0
extern int g_1002dde0;

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

__declspec(naked) void __cdecl gm_CleanupObjectEntities(void)
{
	__asm {
		sub esp, 0xc
		push esi
		push edi
		xor esi, esi
	L_top:
		mov eax, dword ptr [g_query_base]
		cmp word ptr [esi + eax], 0
		je L_next
		mov eax, dword ptr [esi + eax + 6]
		lea ecx, [esp + 0x10]
		push eax
		lea edx, [esp + 0x10]
		push ecx
		lea eax, [esp + 0x10]
		push edx
		push eax
		call gm_ResolveEntityById
		mov eax, dword ptr [esp + 0x18]
		add esp, 0x10
		test eax, eax
		je L_chk_existing
		add eax, 0x5d
		jmp L_test_head
	L_chk_existing:
		mov eax, dword ptr [esp + 0xc]
		test eax, eax
		je L_chk_static
		add eax, 0x14
		jmp L_test_head
	L_chk_static:
		mov eax, dword ptr [esp + 0x10]
		test eax, eax
		je L_cleanup
		add eax, 0x178
	L_test_head:
		test eax, eax
		je L_cleanup
		mov edx, dword ptr [g_query_base]
		xor ecx, ecx
		mov cx, word ptr [esi + edx]
		push ecx
		push eax
		call gm_RemoveObjectByType
		add esp, 8
		jmp L_next
	L_cleanup:
		mov eax, dword ptr [g_query_base]
		lea ecx, [esi + eax]
		push ecx
		call gm_NoopRet2
		mov edx, dword ptr [g_query_base]
		add esp, 4
		mov word ptr [esi + edx], 0
		mov eax, dword ptr [g_query_limit]
		dec eax
		mov dword ptr [g_query_limit], eax
	L_next:
		add esi, 0x43
		cmp esi, 0x14f218
		jl L_top
		mov edi, dword ptr [g_query_base]
		mov ecx, 0x53c86
		xor eax, eax
		rep stosd
		pop edi
		pop esi
		add esp, 0xc
		ret
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

__declspec(naked) int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id)
{
	(void) dynamic;
	(void) existing;
	(void) static_ptr;
	(void) entity_id;
	__asm {
		_emit 0xa1
		_emit 0x50
		_emit 0xe4
		_emit 0x1d
		_emit 0x10
		push ebx
		push esi
		test eax, eax
		push edi
		je near L_ret0
		mov edi, dword ptr [esp + 0x10]
		test edi, edi
		je L_chk_existing
		mov dword ptr [edi], 0
	L_chk_existing:
		mov ebx, dword ptr [esp + 0x14]
		test ebx, ebx
		je L_chk_static
		mov dword ptr [ebx], 0
	L_chk_static:
		mov edx, dword ptr [esp + 0x18]
		mov esi, dword ptr [esp + 0x1c]
		test edx, edx
		je L_dyn
		mov dword ptr [edx], 0
		mov eax, 0x100358a0
		xor ecx, ecx
	L_static_loop:
		_emit 0x66
		_emit 0x81
		_emit 0x38
		_emit 0xff
		_emit 0xff
		je L_static_next
		cmp dword ptr [eax + 4], esi
		je L_found_static
	L_static_next:
		add eax, 0x21c
		inc ecx
		cmp ecx, 0x300
		jl L_static_loop
	L_dyn:
		test edi, edi
		je L_existing
		_emit 0xa1
		_emit 0xc0
		_emit 0xd8
		_emit 0x14
		_emit 0x10
		xor ecx, ecx
	L_dyn_loop:
		cmp byte ptr [eax], 0
		je L_dyn_next
		cmp dword ptr [eax + 1], esi
		je L_found_dyn
	L_dyn_next:
		inc ecx
		add eax, 0xa9
		cmp ecx, 0x100
		jl L_dyn_loop
		jmp L_existing
	L_found_static:
		pop edi
		pop esi
		mov dword ptr [edx], eax
		mov eax, 3
		pop ebx
		ret
	L_found_dyn:
		mov dword ptr [edi], eax
		pop edi
		pop esi
		mov eax, 1
		pop ebx
		ret
	L_existing:
		test ebx, ebx
		je L_ret0
		_emit 0x8b
		_emit 0x15
		_emit 0x50
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0xa1
		_emit 0x34
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		xor ecx, ecx
		test edx, edx
		jle L_ret0
	L_ex_loop:
		cmp word ptr [eax], 0
		je L_ex_next
		cmp dword ptr [eax + 2], esi
		je L_found_existing
		inc ecx
	L_ex_next:
		add eax, 0x43
		cmp ecx, edx
		jl L_ex_loop
	L_ret0:
		pop edi
		pop esi
		xor eax, eax
		pop ebx
		ret
	L_found_existing:
		pop edi
		pop esi
		mov dword ptr [ebx], eax
		mov eax, 2
		pop ebx
		ret
	}
}

/* Refreshes market availability. Recalculates which goods
 * are available for trade based on current building production
 * and inventory states. */

// FUNCTION: SERVER 0x10016240
// gm_FindSlotById

// DATA: SERVER 0x1009b770
extern char g_slot_array[];

__declspec(naked) char* __cdecl gm_FindSlotById(int arg1, int arg2)
{
	(void) arg1;
	(void) arg2;
	__asm {
		mov edx, dword ptr [esp + 4]
		xor ecx, ecx
		mov eax, edx
		push esi
		shl eax, 4
		add eax, edx
		mov esi, dword ptr [esp + 0xc]
		push edi
		lea eax, [eax + eax*4]
		lea edx, [edx + eax*8]
		shl edx, 4
		lea eax, [edx + 0x1009b770]
	L_loop:
		xor edi, edi
		mov di, word ptr [eax]
		cmp edi, esi
		je L_found
		inc ecx
		add eax, 0x80
		cmp ecx, 0x55
		jl L_loop
		pop edi
		xor eax, eax
		pop esi
		ret
	L_found:
		shl ecx, 7
		pop edi
		pop esi
		lea eax, [ecx + edx + 0x1009b770]
		ret
	}
}

/* Returns the next matching entity from an active query.
 * Advances the query iterator and returns the next entity
 * that matches the query criteria. */

// DATA: SERVER 0x10030b9e

// DATA: SERVER 0x1003545e

// DATA: SERVER 0x1003545c

// DATA: SERVER 0x1003545d

// DATA: SERVER 0x10035454

// DATA: SERVER 0x10035458

// DATA: SERVER 0x100a8c38

// DATA: SERVER 0x10035468

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

__declspec(naked) int __cdecl gm_RemoveObjectByType(char** objectListHead, unsigned int objectTypeId)
{
	(void) objectListHead;
	(void) objectTypeId;
	__asm {
		push ebx
		push ebp
		mov ebp, dword ptr [esp + 0xc]
		xor ebx, ebx
		push esi
		push edi
		test ebp, ebp
		jne L_have_head
		pop edi
		pop esi
		pop ebp
		or eax, 0xffffffff
		pop ebx
		ret
	L_have_head:
		mov esi, dword ptr [ebp]
		test esi, esi
		jne L_have_node
		pop edi
		pop esi
		pop ebp
		or eax, 0xffffffff
		pop ebx
		ret
	L_have_node:
		mov eax, dword ptr [esp + 0x18]
		xor edi, edi
	L_loop:
		xor ecx, ecx
		mov cx, word ptr [esi]
		cmp ecx, eax
		je L_found
		mov ebx, esi
		mov esi, dword ptr [esi + 0x3f]
		inc edi
		test esi, esi
		jne L_loop
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffffe
		pop ebx
		ret
	L_found:
		test esi, esi
		jne L_unlink
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffffe
		pop ebx
		ret
	L_unlink:
		mov ecx, dword ptr [esi + 0x14]
		lea eax, [esi + 0x14]
		test ecx, ecx
		je L_skip_free
		push eax
		call gm_FreeObjectListRecursive
		add esp, 4
	L_skip_free:
		push esi
		call gm_NoopRet2
		add esp, 4
		test edi, edi
		jne L_unlink_prev
		mov edx, dword ptr [esi + 0x3f]
		mov dword ptr [ebp], edx
		jmp L_finalize
	L_unlink_prev:
		mov eax, dword ptr [esi + 0x3f]
		mov dword ptr [ebx + 0x3f], eax
	L_finalize:
		mov word ptr [esi], 0
		_emit 0xa1
		_emit 0x50
		_emit 0x54
		_emit 0x03
		_emit 0x10
		dec eax
		pop edi
		pop esi
		_emit 0xa3
		_emit 0x50
		_emit 0x54
		_emit 0x03
		_emit 0x10
		pop ebp
		xor eax, eax
		pop ebx
		ret
	}
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

__declspec(naked) int __cdecl gm_RemoveLinkedNodeById(int* arg1, int arg2)
{
	(void) arg1;
	(void) arg2;
	__asm {
		push ebx
		push ebp
		mov ebp, dword ptr [esp + 0xc]
		push esi
		xor ebx, ebx
		push edi
		mov esi, dword ptr [ebp]
		test esi, esi
		jne L_loopstart
		pop edi
		pop esi
		pop ebp
		or eax, 0xffffffff
		pop ebx
		ret
	L_loopstart:
		mov eax, dword ptr [esp + 0x18]
		xor edi, edi
	L_loop:
		cmp dword ptr [esi + 2], eax
		je L_found
		mov ebx, esi
		mov esi, dword ptr [esi + 0x3f]
		inc edi
		test esi, esi
		jne L_loop
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffffe
		pop ebx
		ret
	L_found:
		test esi, esi
		jne L_doremove
		pop edi
		pop esi
		pop ebp
		mov eax, 0xfffffffe
		pop ebx
		ret
	L_doremove:
		mov ecx, dword ptr [esi + 0x14]
		lea eax, [esi + 0x14]
		test ecx, ecx
		je L_skipfree
		push eax
		call gm_FreeObjectListRecursive
		add esp, 4
	L_skipfree:
		push esi
		call gm_NoopRet2
		add esp, 4
		test edi, edi
		jne L_unlinkprev
		mov eax, dword ptr [esi + 0x3f]
		mov dword ptr [ebp], eax
		jmp L_finish
	L_unlinkprev:
		mov ecx, dword ptr [esi + 0x3f]
		mov dword ptr [ebx + 0x3f], ecx
	L_finish:
		mov word ptr [esi], 0
		mov eax, dword ptr [g_query_limit]
		dec eax
		pop edi
		pop esi
		mov dword ptr [g_query_limit], eax
		pop ebp
		xor eax, eax
		pop ebx
		ret
	}
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

int __cdecl gm_SubObjekt(void* parent_id, unsigned int obj_type, int count)
{
	unsigned int objectTypeId;
	int resolve_result;
	void** objectListHead;
	void* dynamic_ent;
	void* static_ent;

	resolve_result = gm_ResolveEntityById(&dynamic_ent, (void**) &parent_id, &static_ent, (int) parent_id);
	objectTypeId = obj_type;
	if (resolve_result == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xe2d, "gm_SubObjekt(): Parent not found", 1);
	}
	else {
		if (dynamic_ent != (void*) 0) {
			objectListHead = (void**) ((int) dynamic_ent + 0x5d);
		}
		else if (parent_id != (void*) 0) {
			objectListHead = (void**) ((int) parent_id + 0x14);
		}
		else {
			if (static_ent == (void*) 0) {
				return 0;
			}
			objectListHead = (void**) ((int) static_ent + 0x178);
		}
		parent_id = gm_StartEntityQuery((int) *objectListHead, 1, 0, obj_type);
		if (parent_id != (void*) 0 && *(int*) ((int) parent_id + 0xe) >= count) {
			*(int*) ((int) parent_id + 0xe) = *(int*) ((int) parent_id + 0xe) - count;
			if (*(int*) ((int) parent_id + 0xe) <= 0) {
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

__declspec(naked) int __cdecl gm_SubObjektNoKill(int entity_id, int object_id, int subtract_amount)
{
	(void) entity_id;
	(void) object_id;
	(void) subtract_amount;
	__asm {
		sub esp, 8
		lea eax, [esp + 4]
		lea ecx, [esp + 0xc]
		_emit 0x8d
		_emit 0x54
		_emit 0x24
		_emit 0x00
		push ebx
		mov ebx, dword ptr [esp + 0x10]
		push edi
		push ebx
		push eax
		push ecx
		push edx
		call gm_ResolveEntityById
		add esp, 0x10
		test eax, eax
		jne L_have_entity
		push 1
		push 0x100313d4
		push 0xe5c
		push 0x10031004
		call LogMessageInternal
		add esp, 0x10
	L_zero_ret:
		pop edi
		xor eax, eax
		pop ebx
		add esp, 8
		ret
	L_have_entity:
		mov eax, dword ptr [esp + 8]
		test eax, eax
		je L_chk_person
		lea edi, [eax + 0x5d]
		jmp L_have_container
	L_chk_person:
		mov eax, dword ptr [esp + 0x14]
		test eax, eax
		je L_chk_building
		lea edi, [eax + 0x14]
		jmp L_have_container
	L_chk_building:
		mov eax, dword ptr [esp + 0xc]
		test eax, eax
		je L_zero_ret
		lea edi, [eax + 0x178]
	L_have_container:
		mov eax, dword ptr [edi]
		push esi
		mov esi, dword ptr [esp + 0x1c]
		push esi
		push 0
		push 1
		push eax
		call gm_StartEntityQuery
		add esp, 0x10
		mov dword ptr [esp + 0x18], eax
		test eax, eax
		jne L_have_result
		push 1
		push esi
		push ebx
		call gm_AllocObjekt
		mov dword ptr [esp + 0x24], eax
		mov dword ptr [eax + 0xe], 0
		mov eax, dword ptr [esp + 0x24]
		add esp, 0xc
	L_have_result:
		mov ecx, dword ptr [esp + 0x20]
		mov edx, dword ptr [eax + 0xe]
		sub edx, ecx
		mov dword ptr [eax + 0xe], edx
		mov edx, dword ptr [esp + 0x18]
		mov eax, dword ptr [edx + 0xe]
		test eax, eax
		jne L_skip_remove
		push esi
		push edi
		call gm_RemoveObjectByType
		add esp, 8
	L_skip_remove:
		pop esi
		pop edi
		mov eax, 1
		pop ebx
		add esp, 8
		ret
	}
}

/* Finds the next entity matching filter criteria. Used
 * internally by entity query iteration. Advances past
 * non-matching entities. */

// FUNCTION: SERVER 0x10016f80
// FindNextFilteredEntity

__declspec(naked) void* __cdecl FindNextFilteredEntity(void)
{
	__asm {
		_emit 0xa1
		_emit 0xc0
		_emit 0xd8
		_emit 0x14
		_emit 0x10
		push esi
		xor cl, cl
		lea esi, [eax + 0xa900]
		_emit 0xa1
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		test eax, eax
		jne L_chk_count
		xor eax, eax
		pop esi
		ret
	L_chk_count:
		_emit 0x81
		_emit 0x3d
		_emit 0x4c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0x00
		_emit 0x01
		_emit 0x00
		_emit 0x00
		jle L_chk_flag
		xor eax, eax
		pop esi
		ret
	L_chk_flag:
		_emit 0xa0
		_emit 0x49
		_emit 0x54
		_emit 0x03
		_emit 0x10
		test al, al
		je L_no_flag
		_emit 0xa1
		_emit 0x64
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0xc6
		_emit 0x05
		_emit 0x49
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0x00
		cmp eax, esi
		jae near L_ret0_pop1
	L_advance_check_flag:
		cmp byte ptr [eax], 0
		jne L_filter_start
		add eax, 0xa9
		cmp eax, esi
		_emit 0xa3
		_emit 0x64
		_emit 0x54
		_emit 0x03
		_emit 0x10
		jb L_advance_check_flag
		jmp L_filter_start
	L_no_flag:
		_emit 0xa1
		_emit 0x64
		_emit 0x54
		_emit 0x03
		_emit 0x10
	L_no_flag_loop:
		add eax, 0xa9
		cmp eax, esi
		_emit 0xa3
		_emit 0x64
		_emit 0x54
		_emit 0x03
		_emit 0x10
		jae near L_ret0_pop1
		cmp byte ptr [eax], 0
		je L_no_flag_loop
	L_filter_start:
		cmp eax, esi
		jb L_main_loop
	L_ret0_pop1:
		xor eax, eax
		pop esi
		ret
	L_main_loop:
		push ebx
		_emit 0x8a
		_emit 0x1d
		_emit 0x90
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		push ebp
		_emit 0x66
		_emit 0x8b
		_emit 0x2d
		_emit 0x8c
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		push edi
		_emit 0x8b
		_emit 0x3d
		_emit 0x88
		_emit 0x0b
		_emit 0x03
		_emit 0x10
	L_check_again:
		_emit 0x8a
		_emit 0x15
		_emit 0x48
		_emit 0x54
		_emit 0x03
		_emit 0x10
		test dl, dl
		je L_chk_type
		mov cl, 1
	L_chk_type:
		_emit 0x8a
		_emit 0x15
		_emit 0x84
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		cmp dl, 0xff
		je L_chk_id
		cmp byte ptr [eax], dl
		jne near L_zero_cl
		mov cl, 1
	L_chk_id:
		cmp edi, -1
		je L_chk_v25
		cmp dword ptr [eax + 1], edi
		jne near L_zero_cl
		mov cl, 1
	L_chk_v25:
		cmp bp, 0x7fff
		je L_chk_v27
		cmp word ptr [eax + 0x25], bp
		jne L_zero_cl
		mov cl, 1
	L_chk_v27:
		_emit 0x66
		_emit 0x8b
		_emit 0x15
		_emit 0x8e
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		cmp dx, 0x7fff
		je L_chk_v30
		cmp word ptr [eax + 0x27], dx
		jne L_zero_cl
		mov cl, 1
	L_chk_v30:
		cmp bl, 0xff
		je L_check_count
		xor edx, edx
		_emit 0x8b
		_emit 0x2d
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		mov dl, byte ptr [eax]
		add ebp, edx
		lea ecx, [edx + edx*2]
		shl ecx, 4
		add ecx, edx
		lea ecx, [ecx + ecx*2]
		mov dl, byte ptr [ebp + ecx*4]
		_emit 0x66
		_emit 0x8b
		_emit 0x2d
		_emit 0x8c
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		cmp dl, bl
		sete cl
	L_check_count:
		_emit 0x8b
		_emit 0x15
		_emit 0x4c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		inc edx
		test cl, cl
		_emit 0x89
		_emit 0x15
		_emit 0x4c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		jne L_check_done
	L_inner_loop:
		add eax, 0xa9
		cmp eax, esi
		_emit 0xa3
		_emit 0x64
		_emit 0x54
		_emit 0x03
		_emit 0x10
		jae L_final_check_zero
		cmp byte ptr [eax], 0
		je L_inner_loop
	L_check_done:
		cmp eax, esi
		jae L_final_check_cl
		test cl, cl
		je near L_check_again
		pop edi
		pop ebp
		pop ebx
		pop esi
		ret
	L_zero_cl:
		xor cl, cl
		jmp L_check_count
	L_final_check_cl:
		test cl, cl
		jne L_have_eax
	L_final_check_zero:
		xor eax, eax
		_emit 0xa3
		_emit 0x64
		_emit 0x54
		_emit 0x03
		_emit 0x10
	L_have_eax:
		pop edi
		pop ebp
		pop ebx
		pop esi
		ret
	}
}

void* __cdecl FindNextFilteredEntity_unused(void)
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

// DATA: SERVER 0x100a8c30

// DATA: SERVER 0x10030b8c
extern short g_query_filter_extra2;

// DATA: SERVER 0x10030b8e
extern short g_query_filter_extra3;

// DATA: SERVER 0x10030b84
extern char DAT_10030b84;

// DATA: SERVER 0x10030b88
extern int g_query_filter_extra1;

// DATA: SERVER 0x10030b90
extern char g_query_filter_extra4;

// DATA: SERVER 0x10035444
extern char* g_dynasty_field_44;

// DATA: SERVER 0x10035449
extern char DAT_10035449;

// DATA: SERVER 0x1003544c
extern int DAT_1003544c;

// DATA: SERVER 0x10035448
extern char g_dynasty_field_48;

// DATA: SERVER 0x10035464
extern unsigned char* g_query_filter_base;

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

int __cdecl gm_CleanupBuildingEntity(unsigned char* building)
{
	int* entity_scan;

	if (building == (unsigned char*) 0) {
		return -1;
	}
	if (*building == 0) {
		return -2;
	}
	switch (*building) {
	case 0x1e:
		if (*(void**) (building + 0x71) != (void*) 0) {
			m_FreeTracked(*(void**) (building + 0x71));
			*(int*) (building + 0x71) = 0;
		}
		*(int*) (building + 0x71) = 0;
		goto cleanup_loop;
	case 0x48:
	case 0x49:
	case 0x4a:
		gv_Free3Fields(*(void**) (building + 0x65));
		break;
	case 0x4b:
	case 0x4c:
	case 0x4d:
		m_FreeTracked(*(void**) (building + 0x65));
		break;
	default:
		goto cleanup_loop;
	}
	*(int*) (building + 0x65) = 0;
cleanup_loop:
	entity_scan = &DAT_10035a0c;
	do {
		if ((unsigned char*) entity_scan[1] == building) {
			entity_scan[1] = 0;
		}
		if ((unsigned char*) *entity_scan == building) {
			*entity_scan = 0;
		}
		entity_scan = entity_scan + 0x87;
	} while ((int) entity_scan < 0x1009ae0c);
	if (*(int*) (building + 0x5d) != 0) {
		gm_FreeObjectListRecursive((char**) (building + 0x5d));
	}
	*building = 0;
	return 0;
}

/* Allocates default values for a building entity. Sets up
 * initial worker capacity, production slots, and storage
 * based on building type. */

// FUNCTION: SERVER 0x10017330
// gm_AllocBuildingDefaults

void __cdecl gm_AllocBuildingDefaults(unsigned char* building)
{
	void* query_result;
	int inner_count;
	unsigned short* item_ptr;
	unsigned char* table_ptr;

	table_ptr = &DAT_10030861;
	do {
		if (*building == *(table_ptr - 1)) {
			query_result = gm_StartEntityQuery(*(int*) (building + 0x5d), 2, 6, 0, 0xff);
			if (query_result != (void*) 0) {
				goto do_inner;
			}
			query_result = gm_AllocObjekt(*(int*) (building + 1), 0xff, 1);
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

__declspec(naked) void __cdecl gm_SetBuildingWorkerLimits(unsigned char* arg1)
{
	(void) arg1;
	__asm {
		push esi
		push edi
		mov edi, dword ptr [esp + 0xc]
		xor ecx, ecx
		_emit 0x8b
		_emit 0x15
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		push 6
		mov cl, byte ptr [edi]
		push 0x2a
		add edx, ecx
		push 0
		lea eax, [ecx + ecx*2]
		push 2
		shl eax, 4
		add eax, ecx
		lea eax, [eax + eax*2]
		lea esi, [edx + eax*4]
		mov eax, dword ptr [edi + 0x5d]
		push eax
		call gm_StartEntityQuery
		add esp, 0x14
		test eax, eax
		je L_second
		mov cl, byte ptr [esi + 0x23d]
		test cl, cl
		jne L_else
		mov dl, byte ptr [esi + 0x23e]
		test dl, dl
		jne L_else
		mov dl, byte ptr [esi + 0x23f]
		test dl, dl
		je L_else
		mov byte ptr [eax + 0x1c], dl
		jmp L_second
	L_else:
		cmp cl, 2
		jae L_keep_cl
		mov ecx, 2
		jmp L_store_1c
	L_keep_cl:
		and ecx, 0xff
	L_store_1c:
		mov byte ptr [eax + 0x1c], cl
		mov cl, byte ptr [esi + 0x23e]
		cmp cl, 2
		jae L_keep_cl2
		mov ecx, 2
		jmp L_store_1d
	L_keep_cl2:
		and ecx, 0xff
	L_store_1d:
		mov byte ptr [eax + 0x1d], cl
	L_second:
		mov ecx, dword ptr [edi + 0x5d]
		push 6
		push 0x116
		push 0
		push 2
		push ecx
		call gm_StartEntityQuery
		add esp, 0x14
		test eax, eax
		je L_done
		mov cl, byte ptr [esi + 0x23d]
		test cl, cl
		jne L_done
		mov cl, byte ptr [esi + 0x23e]
		test cl, cl
		jne L_done
		mov cl, byte ptr [esi + 0x23f]
		test cl, cl
		je L_done
		mov byte ptr [eax + 0x1c], cl
	L_done:
		pop edi
		pop esi
		ret
	}
}

/* Allocates a new building (Gebaeude) entity. Creates the
 * building struct, sets type, initializes production and
 * storage, and links to the town. */

// DATA: SERVER 0x100a8c30

// DATA: SERVER 0x10030b6c

// DATA: SERVER 0x101de450

// DATA: SERVER 0x10035880
// DATA: SERVER 0x10035884
extern int g_10035884;
// DATA: SERVER 0x10035888
extern int g_10035888;
// DATA: SERVER 0x1003588c
extern short g_1003588c;

char* __cdecl gm_AllocGebaeude(int building_type, int location_id)
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
	gebType = building_type & 0xff;
	*geb = (char) building_type;
	base = temp_result + gebType * 0x24d;

	sprintf(buf, "----->GebID= %i GebProt= %i", g_next_object_id, gebType);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x10d8, buf, 8);

	*(int*) (geb + 1) = g_next_object_id;
	g_next_object_id = g_next_object_id + 1;
	owner_id = (short) location_id;
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
	{
		unsigned short* comp_iter = (unsigned short*) (base + 0x23);
		for (building_type = 0; building_type < 0x40; building_type++) {
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
		}
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
				*(int*) (geb + 0x65) = *(int*) ((unsigned short) location_id * 0x21c + 0x100358a4);
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

unsigned short* __cdecl gm_SetupEntityQuery(unsigned char* entity)
{
	char* type_entry;
	int result;
	unsigned short* p;

	gm_GetBuildingTypeCategory((int) *entity);
	type_entry = (char*) (g_entity_type_table + (unsigned int) *entity * 0x24d);
	result = gm_CheckEntityType(entity);
	if (result != 0) {
		return (unsigned short*) gm_StartEntityQuery(*(int*) (entity + 0x5d), 1, 0, 0xfd);
	}
	if (*type_entry == 4) {
		return (unsigned short*) gm_StartEntityQuery(*(int*) (entity + 0x5d), 1, 0, 0x54);
	}
	p = (unsigned short*) gm_StartEntityQuery(*(int*) (entity + 0x5d), 1, 4, 2);
	while (p != (unsigned short*) 0 && *p == 0xfd) {
		p = gm_NextEntityQueryMatch();
	}
	return p;
}

/* Returns the category of a building type. Maps a building
 * type ID to its category (production, storage, service, etc.). */

// FUNCTION: SERVER 0x100179b0
// gm_GetBuildingTypeCategory

int __cdecl gm_GetBuildingTypeCategory(int arg1)
{
	switch (*(unsigned char*) (g_entity_type_table + arg1 * 0x24d)) {
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

__declspec(naked) int __cdecl gm_CheckEntityType(unsigned char* entity_ptr)
{
	(void) entity_ptr;
	__asm {
		mov eax, dword ptr [esp + 4]
		test eax, eax
		jne L_nonnull
		ret

	L_nonnull:
		xor ecx, ecx
		mov edx, dword ptr [g_entity_type_table]
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

void __cdecl gm_AssignBuildingOwner(unsigned char* building, unsigned short new_owner, unsigned int owner_slot)
{
	char building_class;
	unsigned short prev_owner;
	unsigned char* owner_building;
	int loop_count;
	unsigned short* obj_iter;
	char* type_entry;
	int owner_index;

	type_entry = dword_100a8c30 + *building * 0x24d;
	*(unsigned short*) (building + 0x25) = new_owner;
	if (owner_slot != 0xffff) {
		prev_owner = *(unsigned short*) (building + 0x27);
		if ((prev_owner != 0xffff) && (PTR_10035A10(prev_owner) == (unsigned char**) building)) {
			PTR_10035A10(prev_owner) = 0;
		}
		*(unsigned short*) (building + 0x27) = (unsigned short) owner_slot;
		if (*type_entry == '\x02') {
			owner_building = (unsigned char*) PTR_10035A10(owner_slot & 0xffff);
			if ((owner_building == 0) || (*owner_building <= *building)) {
				PTR_10035A10(owner_slot & 0xffff) = (unsigned char**) building;
			}
		}
		owner_index = owner_slot;
		if (((BYTE_100358A2(owner_index) == '\x06') || (BYTE_100358A2(owner_index) == '\a')) &&
			(loop_count = (int) gm_FindEntityByOwner((int) building), loop_count != 0)) {
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
				(*(unsigned int*) ((unsigned char*) obj_iter + 0x1c) == *(unsigned int*) (building + 1))) {
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

// FUNCTION: SERVER 0x10017f30
// gm_RemoveObjectWrapper

int __cdecl gm_RemoveObjectWrapper(int entity_record, unsigned int obj_type)
{
	int remove_result;

	remove_result = gm_RemoveObjectByType((void**) (entity_record + 0x5d), obj_type);
	if (remove_result == -2) {
		return -3;
	}
	return 0;
}

/* Removes a link from an entity. Clears a specific entity
 * reference field, breaking the association. */

// FUNCTION: SERVER 0x10017f60
// gm_RemoveEntityLink

void __cdecl gm_RemoveEntityLink(int entity)
{
	int parent_entity;

	parent_entity = (int) gm_EntityAccumulate((void*) entity);
	if (parent_entity != 0) {
		gm_RemoveLinkedNodeById((int*) (parent_entity + 0x5d), *(int*) (entity + 2));
	}
}

/* Initializes an entity if it exists. Validates the entity
 * pointer, then sets default field values. No-op on NULL. */

// FUNCTION: SERVER 0x10017f90
// gm_InitEntityIfValid

void __cdecl gm_InitEntityIfValid(short* entity)
{
	if (entity != (short*) 0 && *(unsigned short*) entity != 0xFFFF) {
		amt_ClearEntityLinks(entity);
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
__declspec(naked) void __cdecl gm_DeallocEntity(unsigned int index, int arg2)
{
	(void) index;
	(void) arg2;
	__asm {
		sub esp, 0x204
		mov eax, dword ptr [esp + 0x208]
		push ebx
		push ebp
		push esi
		lea eax, [eax + eax*2]
		push edi
		mov bl, 0xf
		lea eax, [eax + eax*4]
		lea ebp, [eax + eax*8]
		shl ebp, 2
		mov al, byte ptr [ebp + 0x100358a2]
		mov edi, dword ptr [ebp + 0x100358a4]
		lea esi, [ebp + 0x100358a0]
		cmp al, bl
		mov dword ptr [esp + 0x10], edi
		je L_after_init
		mov byte ptr [esi + 8], 0
		_emit 0x66
		_emit 0xa1
		_emit 0x80
		_emit 0x58
		_emit 0x03
		_emit 0x10
		push esi
		mov word ptr [esi + 0x28], ax
		call gm_InitEntityIfValid
		add esp, 4
		mov byte ptr [esi + 2], bl
	L_after_init:
		lea ecx, [esi + 0x178]
		push ecx
		call gm_FreeObjectListRecursive
		mov ebx, dword ptr [esp + 0x220]
		add esp, 4
		test ebx, ebx
		je L_param2_zero
		_emit 0x66
		_emit 0x81
		_emit 0x3e
		_emit 0xff
		_emit 0xff
		je L_skip_dec
		_emit 0xff
		_emit 0x0d
		_emit 0x34
		_emit 0x54
		_emit 0x03
		_emit 0x10
	L_skip_dec:
		mov edx, 0x100358fc
	L_ref_outer:
		mov eax, edx
		mov ecx, 8
	L_ref_inner:
		mov edi, dword ptr [eax]
		cmp edi, dword ptr [esi + 4]
		jne L_ref_inner_next
		mov dword ptr [eax], 0xffffffff
	L_ref_inner_next:
		add eax, 4
		dec ecx
		jne L_ref_inner
		add edx, 0x21c
		cmp edx, 0x1009acfc
		jl L_ref_outer
		mov ecx, 0x87
		xor eax, eax
		mov edi, esi
		rep stosd
		or eax, 0xffffffff
		mov word ptr [esi], 0xffff
		lea edi, [ebp + 0x100358fc]
		mov ecx, 8
		mov dword ptr [ebp + 0x100358a4], eax
		cmp ebx, 1
		rep stosd
		jne L_skip_log
		mov edx, dword ptr [esp + 0x10]
		lea eax, [esp + 0x14]
		push edx
		push 0x10031538
		push eax
		call sprintf
		add esp, 0xc
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x204
		ret
	L_param2_zero:
		push edi
		lea ecx, [esp + 0x18]
		push 0x10031500
		push ecx
		call sprintf
		add esp, 0xc
	L_skip_log:
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x204
		ret
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

	g_citizen_count = 0;
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

int __cdecl gm_CheckStatLevel(int entity_idx, int stat_id)
{
	int idx;
	int val;
	int result;

	idx = entity_idx * 0x21c;
	val = gm_MapEntityStatRange((int) g_entity_type_bytes[idx]);
	if (val == stat_id) {
		return (unsigned int) g_entity_type_bytes[idx];
	}
	result = (int) gm_GetEntityTableEntry(g_entity_array + idx);
	if (result == 0) {
		return 0;
	}
	return (unsigned int) *(unsigned char*) (result + 0x74 + stat_id);
}

/* Maps and clamps an entity stat value to a valid range.
 * Applies min/max bounds and any stat modifiers. */

// FUNCTION: SERVER 0x10018200
// gm_MapEntityStatRange

int __cdecl gm_MapEntityStatRange(int stat_id)
{
	switch (stat_id) {
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
int __cdecl gm_GetOppositeStatIndex(int stat_id)
{
	int result;

	result = 0;

	/* Group 1-6 (section A, row 1) */
	if ((stat_id >= 1) && (stat_id <= 6)) {
		return 7 - stat_id;
	}
	/* Group 7-12 (section A, row 2) */
	if ((stat_id >= 7) && (stat_id <= 12)) {
		return 13 - stat_id;
	}
	/* Group 34-39 (section B, row 1) */
	if ((stat_id >= 34) && (stat_id <= 39)) {
		return 40 - stat_id;
	}
	/* Group 40-45 (section B, row 2) */
	if ((stat_id >= 40) && (stat_id <= 45)) {
		return 46 - stat_id;
	}
	/* Group 46-51 (section B, row 3) */
	if ((stat_id >= 46) && (stat_id <= 51)) {
		return 52 - stat_id;
	}
	/* Group 58-63 (section B, row 5) */
	if ((stat_id >= 58) && (stat_id <= 63)) {
		return 64 - stat_id;
	}
	/* Group 64-69 (section B, row 6) */
	if ((stat_id >= 64) && (stat_id <= 69)) {
		return 70 - stat_id;
	}
	/* Group 70-75 (section B, row 7) */
	if ((stat_id >= 70) && (stat_id <= 75)) {
		return 76 - stat_id;
	}
	/* Group 13-18 (section A, row 3) */
	if ((stat_id >= 13) && (stat_id <= 18)) {
		return 19 - stat_id;
	}
	/* Group 52-57 (section B, row 4) */
	if ((stat_id >= 52) && (stat_id <= 57)) {
		return 58 - stat_id;
	}
	/* Group 25-30 (section A, row 5) */
	if ((stat_id >= 25) && (stat_id <= 30)) {
		return 31 - stat_id;
	}
	/* Group 19-24 (section A, row 4) */
	if ((stat_id >= 19) && (stat_id <= 24)) {
		return 25 - stat_id;
	}
	/* Group 76-81 (section C, row 1) */
	if ((stat_id >= 76) && (stat_id <= 81)) {
		return 82 - stat_id;
	}
	/* Group 89-94 (section C, row 3) */
	if ((stat_id >= 89) && (stat_id <= 94)) {
		return 95 - stat_id;
	}
	/* Group 83-88 (section C, row 2) */
	if ((stat_id >= 83) && (stat_id <= 88)) {
		result = 89 - stat_id;
	}
	return result;
}

/* Generates a random stat modifier. Produces a random
 * delta value for stat variation during entity creation
 * or level-up events. */

// FUNCTION: SERVER 0x10018450
// gm_RandomStatModifier

__declspec(naked) char __cdecl gm_RandomStatModifier(char stat_value)
{
	(void) stat_value;
	__asm {
		push ebx
		mov bl, byte ptr [esp + 8]
		test bl, bl
		jne L_nonzero
		push 0x2a
		call gm_RandomMod
		add esp, 4
		add al, 0x15
		pop ebx
		ret
	L_nonzero:
		mov eax, dword ptr [esp + 8]
		and eax, 0xff
		mov dword ptr [esp + 8], eax
		fild dword ptr [esp + 8]
		fcomp DAT_100257bc
		fnstsw ax
		test ah, 1
		mov eax, 0xb
		je L_call
		mov eax, 6
	L_call:
		push eax
		call gm_RandomMod
		add esp, 4
		add bl, al
		mov al, bl
		pop ebx
		ret
	}
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
extern unsigned char g_entity_state_base[];
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

extern char s_gm_KannObjektHergestellt___pCObj_10031628[];

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
