#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"

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
extern double dScaleFactor;
extern int g_alchemy_entity_table[];
int* __cdecl ahm_LookupEntityInTable(int);
extern dispatch_fn PTR_LAB_1002c5a0[];

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

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);

// FUNCTION: SERVER 0x1000c1e0
// ahm_ApplyColorComponent

int __cdecl ahm_ApplyColorComponent(char* color_cmd, char* target)
{
	float val;
	switch (*(int*) (color_cmd + 8)) {
	case 0:
		val = *(float*) (color_cmd + 0x10);
		*(unsigned char*) (target + 8) = (unsigned char) (int) (val * fColorScale);
		return 1;
	case 1:
		val = *(float*) (color_cmd + 0x10);
		*(unsigned char*) (target + 9) = (unsigned char) (int) (val * fColorScale);
		return 1;
	case 2:
		val = *(float*) (color_cmd + 0x10);
		*(unsigned char*) (target + 0xa) = (unsigned char) (int) (val * fColorScale);
		return 1;
	case 3:
		val = *(float*) (color_cmd + 0x10);
		*(unsigned char*) (target + 0xb) = (unsigned char) (int) (val * fColorScale);
		return 1;
	default:
		return 0;
	}
}

/* Allocates an entity slot in the alchemy system. Finds a
 * free slot in the entity table and initializes it with the
 * given parameters. */

// FUNCTION: SERVER 0x1000c280
// ahm_AllocateEntitySlot

__declspec(naked) int __cdecl ahm_AllocateEntitySlot(int cmd_payload, int arg2, int arg3)
{
	(void) cmd_payload;
	(void) arg2;
	(void) arg3;
	__asm {
		push esi
		push edi
		mov edi, dword ptr [esp + 0x10]
		xor esi, esi
		lea eax, [edi + 0xc]
	L_loop:
		cmp dword ptr [eax], 0
		je L_alloc
		inc esi
		add eax, 8
		cmp esi, 6
		jl L_loop
		pop edi
		xor eax, eax
		pop esi
		ret
	L_alloc:
		mov eax, dword ptr [esp + 0x14]
		push 0xff
		push 0
		push 6
		mov ecx, dword ptr [eax + 0x5d]
		push 2
		push ecx
		call gm_StartEntityQuery
		mov ecx, dword ptr [esp + 0x20]
		mov edx, dword ptr [g_next_object_id]
		add esp, 0x14
		mov dword ptr [ecx + 0x14], edx
		mov edx, dword ptr [ecx + 8]
		mov dword ptr [edi + esi*8 + 0xc], edx
		mov edx, dword ptr [ecx + 0x10]
		test eax, eax
		mov dword ptr [edi + esi*8 + 0x10], edx
		je L_skip_add
		mov ecx, dword ptr [ecx + 8]
		mov edx, dword ptr [eax + 2]
		push 2
		push ecx
		push edx
		call gm_AddOrAccumulateObject
		add esp, 0xc
	L_skip_add:
		xor eax, eax
		mov al, byte ptr [g_current_season]
		push eax
		call gm_RefreshMarketAvailability
		add esp, 4
		mov eax, 1
		pop edi
		pop esi
		ret
	}
}

/* Clears a slot if it matches a target value. Used during
 * alchemy cleanup to remove specific entity references. */

// FUNCTION: SERVER 0x1000C310
// ahm_SlotClearMatch

int __cdecl ahm_SlotClearMatch(char* data, char* target, char* src)
{
	int i;
	char* slot_ptr;
	int key;
	int ent;
	key = *(int*) (data + 8);
	i = 0;
	slot_ptr = target + 0xc;
	while (i < 6) {
		if (*(int*) slot_ptr == key) {
			goto found;
		}
		i++;
		slot_ptr += 8;
	}
	return 0;
found:
	ent = (int) gm_StartEntityQuery(*(int*) (src + 0x5d), 2, 6, 0, 0xff);
	if (ent) {
		gm_RemoveObjectByType((void**) (ent + 0x14), *(unsigned int*) (data + 8));
	}
	*(int*) (target + i * 8 + 0xc) = 0;
	*(int*) (target + i * 8 + 0x10) = 0;
	return 1;
}

/* Searches for a value and sets it in the target. Used for
 * alchemy recipe ingredient matching and assignment. */

// FUNCTION: SERVER 0x1000C380
// ahm_SearchAndSet

int __cdecl ahm_SearchAndSet(SRC* src, TGT* tgt)
{
	int i;
	for (i = 0; i < 6; i++) {
		if (tgt->entries[i].key == src->key) {
			tgt->entries[i].val = src->val;
			return 1;
		}
	}
	return 0;
}

/* Clamps a floating-point alchemy value to valid bounds.
 * Prevents stat overflow/underflow during recipe processing. */

// FUNCTION: SERVER 0x1000c3c0
// ahm_ClampFloatValue

__declspec(naked) int __cdecl ahm_ClampFloatValue(int cmd_payload, int arg2)
{
	(void) cmd_payload;
	(void) arg2;
	__asm {
		mov eax, dword ptr [esp + 4]
		mov ecx, dword ptr [esp + 8]
		fld dword ptr [eax + 0x10]
		fadd dword ptr [ecx + 4]
		fcom dword ptr g_float_const_cc
		fnstsw ax
		test ah, 0x41
		jne L_below_min
		fcom dword ptr g_float_const_a0
		fnstsw ax
		test ah, 1
		je L_above_max
		fstp dword ptr [ecx + 4]
		mov eax, 1
		ret
	L_below_min:
		fstp st(0)
		fld dword ptr g_float_const_cc
		mov eax, 1
		fstp dword ptr [ecx + 4]
		ret
	L_above_max:
		fstp st(0)
		fld dword ptr g_float_const_a0
		mov eax, 1
		fstp dword ptr [ecx + 4]
		ret
	}
}

/* Fires (activates) an alchemy entity and cleans up the
 * processing state. Finalizes the recipe output and resets
 * the alchemist for the next batch. */

// FUNCTION: SERVER 0x1000c420
// ahm_FireEntityAndCleanup

int __cdecl ahm_FireEntityAndCleanup(int cmd, int* entity_id_ptr, int parent_record)
{
	unsigned short* entity;
	void* query_result;
	unsigned int* slot_iter;
	int count;

	(void) cmd;
	entity = (unsigned short*) gm_LookupEntityRecordById(*entity_id_ptr);
	if (entity != (unsigned short*) 0) {
		query_result = gm_StartEntityQuery(*(int*) (parent_record + 0x5d), 2, 6, 0, 0xff);
		*(int*) (entity + 0xb8) = 0;
		*(int*) (entity + 0xb6) = 0;
		slot_iter = (unsigned int*) (entity_id_ptr + 3);
		count = 6;
		do {
			if (*slot_iter != 0) {
				if (query_result != (void*) 0) {
					gm_RemoveObjectByType((void**) ((int) query_result + 0x14), *slot_iter);
				}
				*slot_iter = 0;
				slot_iter[1] = 0;
			}
			slot_iter = slot_iter + 2;
			count = count - 1;
		} while (count != 0);
		for (count = 0xf; count != 0; count--) {
			*entity_id_ptr = 0;
			entity_id_ptr = entity_id_ptr + 1;
		}
		gm_DeallocEntity(*entity, 1);
		return 1;
	}
	return 0;
}

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx);
void* __cdecl m_AllocTracked(unsigned int allocSize, const char* groupTag);

/* Allocates and initializes the alchemy info structure for
 * a building. Sets up recipe slots and ingredient storage. */

// FUNCTION: SERVER 0x1000c4d0
// ahm_AllocAhmInfo

__declspec(naked) int __cdecl ahm_AllocAhmInfo(int cmd_payload, int arg2)
{
	(void) cmd_payload;
	(void) arg2;
	__asm {
		sub esp, 0x3c
		_emit 0x8d
		_emit 0x44
		_emit 0x24
		_emit 0x00
		push ebx
		push esi
		push edi
		mov edi, dword ptr [esp + 0x4c]
		push edi
		push 1
		push 4
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_n1
	L_ret0:
		pop edi
		pop esi
		pop ebx
		add esp, 0x3c
		ret
	L_n1:
		push edi
		push 1
		lea ecx, [esp + 0x18]
		push 4
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_n2
		pop edi
		pop esi
		pop ebx
		add esp, 0x3c
		ret
	L_n2:
		push edi
		push 1
		lea edx, [esp + 0x1c]
		push 1
		push edx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_n3
		pop edi
		pop esi
		pop ebx
		add esp, 0x3c
		ret
	L_n3:
		push edi
		push 1
		lea eax, [esp + 0x1d]
		push 1
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_n4
		pop edi
		pop esi
		pop ebx
		add esp, 0x3c
		ret
	L_n4:
		push edi
		push 1
		lea ecx, [esp + 0x1e]
		push 1
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_n5
		pop edi
		pop esi
		pop ebx
		add esp, 0x3c
		ret
	L_n5:
		push edi
		push 1
		lea edx, [esp + 0x1f]
		push 1
		push edx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_loop_init
	L_xor_ret0:
		pop edi
		pop esi
		xor eax, eax
		pop ebx
		add esp, 0x3c
		ret
	L_loop_init:
		xor ebx, ebx
		lea esi, [esp + 0x1c]
	L_loop:
		push edi
		push 1
		lea eax, [esi - 4]
		push 4
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je L_xor_ret0
		push edi
		push 1
		push 4
		push esi
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je L_xor_ret0
		inc ebx
		add esi, 8
		cmp ebx, 6
		jl L_loop
		mov edi, dword ptr [esp + 0x50]
		mov eax, dword ptr [edi + 0x65]
		test eax, eax
		jne L_have_buf
		push 0x1002a0f8
		push 0x3c
		call m_AllocTracked
		add esp, 8
		mov dword ptr [edi + 0x65], eax
	L_have_buf:
		mov edi, dword ptr [edi + 0x65]
		mov ecx, 0xf
		lea esi, [esp + 0xc]
		mov eax, 1
		rep movsd
		pop edi
		pop esi
		pop ebx
		add esp, 0x3c
		ret
	}
}

/* Initializes an alchemy entity with randomized properties.
 * Uses RandomBelow for stat variation within allowed ranges. */

// FUNCTION: SERVER 0x1000c600
// ahm_InitRandomEntity

int __cdecl RandomBelow(unsigned short max);

__declspec(naked) char* __cdecl ahm_InitRandomEntity(void)
{
	__asm {
		push ebx
		push 0x20
		call gm_RandomMod
		add esp, 4
		and eax, 0xffff
		mov edx, 0x20
	L_scan:
		lea ecx, [eax + eax*2]
		lea ecx, [ecx + ecx*4]
		lea ecx, [eax + ecx*4]
		mov bl, byte ptr [ecx*4 + 0x1002a2c2]
		test bl, bl
		je L_found
		dec edx
		inc eax
		and eax, 0x1f
		test edx, edx
		jne L_scan
		xor eax, eax
		pop ebx
		ret
	L_found:
		lea ecx, [eax + eax*2]
		lea edx, [ecx + ecx*4]
		lea ecx, [eax + edx*4]
		mov edx, 0xe
		shl ecx, 2
		lea eax, [ecx + 0x1002a200]
	L_fmul_loop:
		fld dword ptr [eax - 4]
		fmul dScaleFactor
		fstp dword ptr [eax]
		add eax, 0xc
		dec edx
		jne L_fmul_loop
		mov byte ptr [ecx + 0x1002a2c2], 1
		lea eax, [ecx + 0x1002a1d0]
		pop ebx
		ret
	}
}

/* Looks up an alchemy entity in the global table by ID.
 * Returns pointer to the entity's table entry. */

// FUNCTION: SERVER 0x1000c670
// ahm_LookupEntityInTable

int* __cdecl ahm_LookupEntityInTable(int entity_id)
{
	int i;
	int* p;

	for (i = 0, p = g_alchemy_entity_table; (int) p < (int) (g_alchemy_entity_table + 0x17 * 10); p += 0x17, i++) {
		if (*p == entity_id) {
			return g_alchemy_entity_table + i * 0x17;
		}
	}
	return (int*) 0;
}

/* Queries what building type an alchemy entity belongs to.
 * Returns the building type category for alchemy purposes. */

// FUNCTION: SERVER 0x1000c6a0
// ahm_QueryEntityBuildingType

__declspec(naked) int __cdecl ahm_QueryEntityBuildingType(int cmd_payload)
{
	(void) cmd_payload;
	__asm {
		mov eax, dword ptr [esp + 4]
		push esi
		push 5
		push 1
		mov ecx, dword ptr [eax + 0x178]
		push ecx
		call gm_StartEntityQuery
		mov esi, eax
		add esp, 0xc
		test esi, esi
		je L_fail
	L_loop:
		xor edx, edx
		mov dx, word ptr [esi]
		push edx
		call ahm_LookupEntityInTable
		add esp, 4
		test eax, eax
		jne L_check_type
		call gm_NextEntityQueryMatch
		mov esi, eax
		test esi, esi
		jne L_loop
		push eax
		call ahm_LookupEntityInTable
		add esp, 4
		pop esi
		ret
	L_check_type:
		mov ecx, dword ptr [eax + 0x58]
		cmp ecx, 1
		je L_check_count
		cmp ecx, 2
		jne L_ret
	L_check_count:
		mov ecx, dword ptr [esi + 0x20]
		test ecx, ecx
		jg L_ret
	L_fail:
		push 0
		call ahm_LookupEntityInTable
		add esp, 4
	L_ret:
		pop esi
		ret
	}
}

/* Calculates the payload size of a command packet based on
 * the command type and field count. Used for buffer allocation
 * and validation. */

