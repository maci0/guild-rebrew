#include "../../Units/Error/error.h"
#include "../../Units/m_alloc/m_alloc.h"
#include "../../Units/vfs/vfs.h"
#include "../game/entity.h"

#include <stdlib.h>

int __cdecl AllocGraveyardField(int);
extern int g_1002576c[];
extern int g_1002575c[];
extern void amt_FindEntity26(int);
extern void amt_FindEntity27(int);
extern char gm_RandomMod(int);
extern unsigned char __ftol();
extern void gm_AddOrAccumulateObject(int, int, int);
extern char g_100a9820[];
extern char g_1014d8e0[];
extern char g_10139820[];
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
extern int g_save_version;
extern int g_1002d4f0;
extern int g_1002d4f4;
extern char g_1002d4f8;
extern char g_1002d4fc;
extern int DAT_100a8c34;
extern int DAT_10035450;
int __cdecl ls_LoadGraveyardData(int param_1, int param_2);
int __cdecl ahm_AllocAhmInfo(int param_1, int param_2);
extern int g_file_version; /* 0x1002d4ec */
;
extern int g_entity_array_ptr; /* 0x1014d8c0 */
;
extern int g_101de454; /* 0x101de454 */
;
extern int g_101de55c; /* 0x101de55c */
;
extern unsigned int gm_LookupEntityRecordById(unsigned int);
extern int gm_ResolveEntityById(void**, void**, void**, int);
extern void gm_EntitySetField(void);
extern int g_101deae8;
extern int g_101deac0;
extern int g_101de560;
extern int g_save_info[2];
extern int OpenVfsStream(char*, char*, int);
int ls_LoadSavegameHeader(int, char*);
int ls_LoadExistingEntities(int);
unsigned int ls_LoadBuildingEntityState(unsigned int);
int ls_LoadDynamicEntities(void*);
int ls_LoadEntities(int);
int ls_LoadTownData(int);
extern int amt_fio_LoadAemter(int, int);
extern unsigned int ls_ID2Ptr(void);

/* Loads graveyard-specific data from a save file. Reads
 * production slots, worker assignments, and field states
 * for graveyard buildings. */

// FUNCTION: SERVER 0x10012000
// ls_LoadGraveyardData

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);

__declspec(naked) int __cdecl ls_LoadGraveyardData(int param_1, int param_2)
{
	(void) param_1;
	(void) param_2;
	__asm {
		push ecx
		mov eax, dword ptr [esp + 0xc]
		push ebx
		push ebp
		push esi
		push edi
		push eax
		call AllocGraveyardField
		mov ebx, eax
		add esp, 4
		test ebx, ebx
		mov dword ptr [esp + 0x10], ebx
		jne L_first_read
		pop edi
		pop esi
		pop ebp
		pop ebx
		pop ecx
		ret
	L_first_read:
		mov esi, dword ptr [esp + 0x18]
		push esi
		push 1
		push 4
		push ebx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_read2
		pop edi
		pop esi
		pop ebp
		pop ebx
		pop ecx
		ret
	L_read2:
		push esi
		lea edi, [ebx + 4]
		push 1
		push 4
		push edi
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_read3
		pop edi
		pop esi
		pop ebp
		pop ebx
		pop ecx
		ret
	L_read3:
		push esi
		push 1
		lea ecx, [ebx + 0x18]
		push 1
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_read4
		pop edi
		pop esi
		pop ebp
		pop ebx
		pop ecx
		ret
	L_read4:
		push esi
		push 1
		lea edx, [ebx + 0x19]
		push 1
		push edx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_read5
		pop edi
		pop esi
		pop ebp
		pop ebx
		pop ecx
		ret
	L_read5:
		push esi
		push 1
		lea eax, [ebx + 0x1a]
		push 1
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_read6
		pop edi
		pop esi
		pop ebp
		pop ebx
		pop ecx
		ret
	L_read6:
		push esi
		push 1
		lea ecx, [ebx + 0x1b]
		push 1
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_loop1_init
	L_fail0:
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		pop ecx
		ret
	L_loop1_init:
		mov edx, dword ptr [edi]
		mov ebp, dword ptr [ebx + 0x20]
		mov dword ptr [esp + 0x1c], 0
		mov eax, dword ptr [edx*4 + 0x1002576c]
		test eax, eax
		jle near L_loop2_setup
		lea edi, [ebp + 0x14]
	L_loop1:
		push esi
		push 1
		push 4
		push ebp
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je L_fail0
		push esi
		push 1
		lea eax, [edi - 0x10]
		push 0x10
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je L_fail0
		push esi
		push 1
		push 0x10
		push edi
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je L_fail0
		push esi
		push 1
		lea ecx, [edi + 0x10]
		push 5
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je L_fail0
		push esi
		push 1
		lea edx, [edi + 0x18]
		push 4
		push edx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_fail0
		push esi
		push 1
		lea eax, [edi + 0x1c]
		push 4
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_fail0
		push esi
		push 1
		lea ecx, [edi + 0x20]
		push 4
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_fail0
		push esi
		push 1
		lea edx, [edi + 0x24]
		push 4
		push edx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_fail0
		push esi
		push 1
		lea eax, [edi + 0x28]
		push 4
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_fail0
		push esi
		push 1
		lea ecx, [edi + 0x2c]
		push 4
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_fail0
		mov edx, dword ptr [ebx + 4]
		mov eax, dword ptr [esp + 0x1c]
		inc eax
		add ebp, 0x44
		mov ecx, dword ptr [edx*4 + 0x1002576c]
		add edi, 0x44
		cmp eax, ecx
		mov dword ptr [esp + 0x1c], eax
		jl near L_loop1
	L_loop2_setup:
		mov eax, dword ptr [esp + 0x10]
		mov ebx, dword ptr [ebx + 0x1c]
		add eax, 4
		xor ebp, ebp
		mov ecx, dword ptr [eax]
		mov eax, dword ptr [ecx*4 + 0x1002575c]
		test eax, eax
		jle near L_success
		lea edi, [ebx + 8]
	L_loop2:
		push esi
		push 1
		push 4
		push ebx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_fail0
		push esi
		push 1
		lea edx, [edi - 4]
		push 4
		push edx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_fail0
		push esi
		push 1
		push 2
		push edi
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_fail0
		push esi
		push 1
		lea eax, [edi + 2]
		push 2
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_fail0
		push esi
		push 1
		lea ecx, [edi + 4]
		push 1
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_fail0
		push esi
		push 1
		lea edx, [esp + 0x24]
		push 4
		push edx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_fail0
		mov eax, dword ptr [esp + 0x1c]
		add ebx, 0x14
		mov ecx, eax
		add edi, 0x14
		shl ecx, 4
		add ecx, eax
		mov eax, dword ptr [esp + 0x10]
		inc ebp
		mov edx, dword ptr [eax + 0x20]
		add eax, 4
		lea ecx, [edx + ecx*4]
		mov dword ptr [edi - 0xc], ecx
		mov edx, dword ptr [eax]
		cmp ebp, dword ptr [edx*4 + 0x1002575c]
		jl near L_loop2
	L_success:
		pop edi
		pop esi
		pop ebp
		mov eax, 1
		pop ebx
		pop ecx
		ret
	}
}

int __cdecl ls_LoadGraveyardData_unused(int param_1, int param_2)
{
	int field_base;
	int ret;
	int ptr;
	int edi;
	int i;
	(void) param_1;
	(void) param_2;
	(void) field_base;
	(void) ret;
	(void) ptr;
	(void) edi;
	(void) i;
	return 0;
}

/* Initializes a new dynasty entity during save loading.
 * Creates the dynasty's family tree root and initial
 * member entities with default stats. */

// FUNCTION: SERVER 0x100122e0
// ls_InitNewDynastyEntity

__declspec(naked) void ls_InitNewDynastyEntity(int param_1, int param_2, char* param_3, char* param_4)
{
	(void) param_1;
	(void) param_2;
	(void) param_3;
	(void) param_4;
	__asm {
		mov eax, dword ptr [esp + 4]
		push ebp
		mov ebp, dword ptr [esp + 0x14]
		cmp eax, 0x15
		push esi
		jne L_not_15
		mov edx, dword ptr [ebp + 0x1cc]
		mov eax, dword ptr [ebp + 4]
		or dh, 0x10
		push eax
		mov dword ptr [ebp + 0x1cc], edx
		call amt_FindEntity26
		jmp L_after_amt
	L_not_15:
		mov esi, dword ptr [ebp + 0x1cc]
		mov ecx, dword ptr [ebp + 4]
		or esi, 0x2000
		push ecx
		mov dword ptr [ebp + 0x1cc], esi
		call amt_FindEntity27
	L_after_amt:
		mov dx, word ptr [esp + 0x18]
		add esp, 4
		mov word ptr [ebp + 0xa], dx
		mov dword ptr [esp + 0x14], 0x100a9820
		push ebx
		xor ebx, ebx
		push edi
		mov byte ptr [ebp + 0xc], bl
	L_outer_body:
		mov edi, dword ptr [esp + 0x1c]
		xor esi, esi
		sub edi, 0x100a9820
	L_inner_loop:
		push 0x40
		call gm_RandomMod
		sub al, 0x20
		add esp, 4
		mov byte ptr [edi + esi + 0x100a9820], al
		mov byte ptr [edi + esi + 0x1014d8e0], bl
		inc esi
		cmp esi, 0x300
		jl L_inner_loop
		mov eax, dword ptr [esp + 0x1c]
		add eax, 0x300
		cmp eax, 0x10139820
		mov dword ptr [esp + 0x1c], eax
		jl L_outer_body
		lea edi, [ebp + 0x5c]
		mov ecx, 8
		or eax, 0xffffffff
		mov word ptr [ebp + 0x50], 0x7fff
		mov dword ptr [ebp + 0x7c], ebx
		mov byte ptr [ebp + 0x58], bl
		rep stosd
		mov eax, 0x447a0000
		mov dword ptr [ebp + 0x170], ebx
		mov dword ptr [ebp + 0x16c], ebx
		pop edi
		mov dword ptr [ebp + 0x1c], eax
		mov dword ptr [ebp + 0x14], 0x3f800000
		mov dword ptr [ebp + 0x20], 0x41400000
		mov dword ptr [ebp + 0x10], 0x43a50000
		mov dword ptr [ebp + 0x18], eax
		xor esi, esi
		pop ebx
	L_stat_loop:
		push 0x2a
		call gm_RandomMod
		and eax, 0xffff
		add esp, 4
		mov dword ptr [esp + 0x14], eax
		fild dword ptr [esp + 0x14]
		_emit 0xd8
		_emit 0x05
		_emit 0x08
		_emit 0x58
		_emit 0x02
		_emit 0x10
		call __ftol
		mov byte ptr [esi + ebp + 0x80], al
		inc esi
		cmp esi, 5
		jl L_stat_loop
		xor ecx, ecx
		mov byte ptr [ebp + 0xd], 9
		_emit 0x8a
		_emit 0x0d
		_emit 0x39
		_emit 0x54
		_emit 0x03
		_emit 0x10
		mov edx, dword ptr [ebp + 4]
		mov eax, ecx
		push 0xf42400
		shl eax, 6
		sub eax, ecx
		xor ecx, ecx
		lea eax, [eax + eax*2]
		mov cx, word ptr [eax*4 + 0x100a8c94]
		push ecx
		push edx
		call gm_AddOrAccumulateObject
		push 2
		call gm_RandomMod
		add esp, 0x10
		mov byte ptr [ebp + 2], 3
		pop esi
		pop ebp
		ret
	}
}

/* Reads VFS data with error checking. Wraps the VFS read
 * call and returns 0 on success, non-zero on failure. */

// FUNCTION: SERVER 0x10012440
// ls_ReadVfsDataChecked

int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx)
{
	unsigned int result;
	result = ReadVfsData(outBuffer, elementSize, elementCount, streamCtx);
	return result > 0;
}

/* Loads the savegame header block. Reads version info,
 * map name, player count, and game settings from the
 * save file stream. */

// FUNCTION: SERVER 0x10012470
// ls_LoadSavegameHeader

int __cdecl ls_LoadSavegameHeader(int param_1, char* param_2)
{
	char* ebx;
	int i;

	ebx = (char*) m_AllocTracked(0xe100, &g_1002d4fc);
	if (!ls_ReadVfsDataChecked(param_2, 4, 1, (void*) param_1)) {
		return 0;
	}
	g_save_version = *(int*) param_2;
	if (!ls_ReadVfsDataChecked(param_2 + 4, 1, 1, (void*) param_1)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(param_2 + 5, 0x20, 1, (void*) param_1)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(param_2 + 0x28, 8, 1, (void*) param_1)) {
		return 0;
	}
	if (!ls_ReadVfsDataChecked(param_2 + 0x30, 1, 1, (void*) param_1)) {
		return 0;
	}
	if (g_save_version >= 0x10033) {
		if (!ls_ReadVfsDataChecked(param_2 + 0x31, 1, 1, (void*) param_1)) {
			return 0;
		}
	}
	if (g_save_version >= 0x10028) {
		if (!ls_ReadVfsDataChecked(param_2 + 0x32, 0xe, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x40, 0x10, 1, (void*) param_1)) {
			return 0;
		}
		if (g_save_version >= 0x10054) {
			if (!ls_ReadVfsDataChecked(param_2 + 0x50, 0x10, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(param_2 + 0x63, 1, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(param_2 + 0x64, 4, 1, (void*) param_1)) {
				return 0;
			}
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x60, 1, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x61, 1, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x62, 1, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x68, 4, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x6c, 1, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(param_2 + 0x6d, 1, 1, (void*) param_1)) {
			return 0;
		}
		if (g_save_version >= 0x1002b) {
			if (!ls_ReadVfsDataChecked(param_2 + 0x70, 4, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(param_2 + 0x74, 4, 1, (void*) param_1)) {
				return 0;
			}
		}
		else {
			*(int*) (param_2 + 0x70) = -1;
			*(int*) (param_2 + 0x74) = -1;
		}
		if (g_save_version >= 0x10034) {
			char* score_ptr = param_2 + 0x78;
			for (i = 0; i < 8; i++) {
				if (!ls_ReadVfsDataChecked(score_ptr, 4, 1, (void*) param_1)) {
					return 0;
				}
				score_ptr = score_ptr + 4;
			}
			ebx = *(char**) &ebx;
		}
		if (!ls_ReadVfsDataChecked(ebx, 0xe100, 1, (void*) param_1)) {
			return 0;
		}
	}
	if (ebx != (char*) 0) {
		m_FreeTracked(ebx);
	}
	if (g_save_version < 0x10025) {
		return 0;
	}
	if (g_save_version >= 0x10038) {
		if (!ls_ReadVfsDataChecked(param_2 + 0x98, 4, 1, (void*) param_1)) {
			return 0;
		}
	}
	else {
		*(int*) (param_2 + 0x98) = 2;
	}
	if (g_save_version >= 0x10039) {
		if (!ls_ReadVfsDataChecked(param_2 + 0x9c, 0x60, 1, (void*) param_1)) {
			return 0;
		}
	}
	else {
		*(int*) (param_2 + 0x9c) = g_1002d4f0;
		*(int*) (param_2 + 0xa0) = g_1002d4f4;
		*(char*) (param_2 + 0xa4) = g_1002d4f8;
	}
	return 1;
}

/* Loads existing entities from a save file. Reads entity
 * records in bulk and links them into the runtime entity
 * tables. */

// FUNCTION: SERVER 0x100127d0
// ls_LoadExistingEntities


int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);
void __cdecl gm_CleanupObjectEntities(void);

__declspec(naked) int __cdecl ls_LoadExistingEntities(int param_1)
{
	(void) param_1;
	__asm {
		push ecx
		push ebx
		push ebp
		push esi
		push edi
		call gm_CleanupObjectEntities
		mov edi, dword ptr [esp + 0x18]
		lea eax, [esp + 0x10]
		push edi
		push 1
		push 4
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_have_count
	L_ret0:
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		pop ecx
		ret
	L_have_count:
		mov eax, dword ptr [esp + 0x10]
		xor ebp, ebp
		test eax, eax
		jle L_done
		xor ebx, ebx
	L_loop:
		_emit 0x8b
		_emit 0x0d
		_emit 0x34
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		push edi
		push 1
		push 2
		lea esi, [ebx + ecx]
		push esi
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je L_ret0
		push edi
		push 1
		lea edx, [esi + 2]
		push 4
		push edx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je L_ret0
		push edi
		push 1
		lea eax, [esi + 6]
		push 4
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je L_ret0
		push edi
		push 1
		lea ecx, [esi + 0xa]
		push 4
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je L_ret0
		push edi
		push 1
		lea edx, [esi + 0xe]
		push 4
		push edx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_ret0
		push edi
		push 1
		lea eax, [esi + 0x12]
		push 1
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_ret0
		push edi
		push 1
		lea ecx, [esi + 0x13]
		push 1
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_ret0
		push edi
		push 1
		add esi, 0x1c
		push 0x1f
		push esi
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_ret0
		mov eax, dword ptr [esp + 0x10]
		inc ebp
		add ebx, 0x43
		cmp ebp, eax
		jl L_loop
	L_done:
		pop edi
		pop esi
		_emit 0xa3
		_emit 0x50
		_emit 0x54
		_emit 0x03
		_emit 0x10
		pop ebp
		mov eax, 1
		pop ebx
		pop ecx
		ret
	}
}

/* Loads building entity state from a save file. Reads
 * building type, owner, upgrade level, and production
 * state for each building entity. */

// STUB: SERVER 0x100128f0
// ls_LoadBuildingEntityState

unsigned int __cdecl ls_LoadBuildingEntityState(unsigned int param_1)
{
	int entity_count;
	int current_index;
	char* esi;
	int load_result;
	int* ebx;
	unsigned int offset;
	int dummy;
	register int neg1;

	gm_ResetAllEntities();

	if (!ls_ReadVfsDataChecked(&entity_count, 4, 1, (void*) param_1)) {
		return 0;
	}

	current_index = 0;
	if (0 < entity_count) {
		offset = 0;
		neg1 = -1;
		do {
			esi = (char*) (offset + g_entity_array_ptr);

			if (!ls_ReadVfsDataChecked(esi, 1, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x01, 4, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x05, 0x20, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x25, 2, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x27, 2, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x29, 2, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x2b, 4, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x2f, 1, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x34, 1, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x35, 4, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x39, 4, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x3d, 4, 1, (void*) param_1)) {
				return 0;
			}

			ebx = (int*) (esi + 0x41);
			if (!ls_ReadVfsDataChecked(ebx, 4, 1, (void*) param_1)) {
				return 0;
			}
			if (*ebx > 4) {
				*ebx = 2;
			}

			if (!ls_ReadVfsDataChecked(esi + 0x45, 4, 1, (void*) param_1)) {
				return 0;
			}

			if (g_file_version >= 0x10028) {
				if (!ls_ReadVfsDataChecked(esi + 0x49, 4, 1, (void*) param_1)) {
					return 0;
				}
			}

			if (g_file_version < 0x10032) {
				if (!ls_ReadVfsDataChecked(&dummy, 4, 1, (void*) param_1)) {
					return 0;
				}
			}

			if (g_file_version >= 0x10057) {
				if (!ls_ReadVfsDataChecked(esi + 0x4d, 4, 1, (void*) param_1)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(esi + 0x51, 4, 1, (void*) param_1)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(esi + 0x55, 4, 1, (void*) param_1)) {
					return 0;
				}
			}

			if (!ls_ReadVfsDataChecked(esi + 0x5a, 2, 1, (void*) param_1)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(esi + 0x5c, 1, 1, (void*) param_1)) {
				return 0;
			}

			if (esi[0] == 0x1e) {
				*(int*) (esi + 0x71) = (int) m_AllocTracked(0x600, (const char*) 0x1002d510);
				for (load_result = 0; load_result < 0x600; load_result += 0x18) {
					if (!ls_ReadVfsDataChecked((void*) (load_result + *(int*) (esi + 0x71)), 4, 1, (void*) param_1)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 4 + *(int*) (esi + 0x71)),
							4,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 8 + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 9 + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xa + *(int*) (esi + 0x71)),
							2,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0x10 + *(int*) (esi + 0x71)),
							4,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xc + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					if (!ls_ReadVfsDataChecked(
							(void*) (load_result + 0xd + *(int*) (esi + 0x71)),
							1,
							1,
							(void*) param_1
						)) {
						return 0;
					}
					*(int*) (load_result + 0x14 + *(int*) (esi + 0x71)) = 0;
				}
			}
			else if (esi[0] == 0x48 || esi[0] == 0x49 || esi[0] == 0x4a) {
				if (g_file_version >= 0x10047) {
					load_result = ls_LoadGraveyardData(param_1, (int) esi);
				}
				else {
					if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, (void*) param_1)) {
						return 0;
					}
					*(int*) (esi + 0x65) = AllocGraveyardField((int) esi);
					goto label_10012d72;
				}
				if (load_result == 0) {
					return 0;
				}
			}
			else if (esi[0] == 0x4b || esi[0] == 0x4c || esi[0] == 0x4d) {
				if (g_file_version >= 0x10049) {
					load_result = ahm_AllocAhmInfo(param_1, (int) esi);
				}
				else {
					int* ahm_info;
					if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, (void*) param_1)) {
						return 0;
					}
					ahm_info = (int*) m_AllocTracked(0x3c, (const char*) 0x1002d504);
					*(int*) (esi + 0x65) = (int) ahm_info;
					*ahm_info = neg1;
					goto label_10012d72;
				}
				if (load_result == 0) {
					return 0;
				}
			}
			else {
				if (!ls_ReadVfsDataChecked(esi + 0x65, 0x30, 1, (void*) param_1)) {
					return 0;
				}
			}

		label_10012d72:
			if (g_file_version >= 0x10043) {
				if (!ls_ReadVfsDataChecked(esi + 0x99, 0x10, 1, (void*) param_1)) {
					return 0;
				}
			}
			else {
				int* state_ptr = (int*) (esi + 0x99);
				int zero = 0;
				*state_ptr = zero;
				*(int*) ((char*) state_ptr + 4) = zero;
				*(int*) ((char*) state_ptr + 8) = zero;
				*(int*) ((char*) state_ptr + 0xc) = zero;
				*(int*) (esi + 0xa5) = neg1;
				*state_ptr = *state_ptr | 1;
			}

			*(int*) (esi + 0x30) = 0x1388;
			*(int*) (esi + 0x95) = neg1;
			current_index++;
			offset += 0xa9;
		} while (current_index < entity_count);
	}

	if (!ls_ReadVfsDataChecked(&g_101de454, 4, 1, (void*) param_1)) {
		return 0;
	}

	g_101de55c = (int) realloc((void*) g_101de55c, g_101de454 * 0x60);

	current_index = 0;
	for (load_result = 0; load_result < g_101de454; load_result++) {
		if (!ls_ReadVfsDataChecked((void*) (current_index + g_101de55c), 0x40, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked((void*) (current_index + 0x40 + g_101de55c), 0x10, 1, (void*) param_1)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked((void*) (current_index + 0x50 + g_101de55c), 0x10, 1, (void*) param_1)) {
			return 0;
		}
		current_index += 0x60;
	}

	return 1;
}

/* Loads dynamic (non-building) entities from a save file.
 * Reads citizens, objects, and transient game entities. */

// STUB: SERVER 0x10012eb0
// ls_LoadDynamicEntities

/* Game function - reads entity data records from VFS file */

int __cdecl ls_LoadDynamicEntities(void* file)
{
	char* rec;

	rec = (char*) 0x1009aca2;
	do {
		if (!ls_ReadVfsDataChecked(rec - 2, 2, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec, 0x10, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x12, 4, 1, (void*) file)) {
			return 0;
		}
		if (g_file_version >= 0x1002c) {
			if (!ls_ReadVfsDataChecked(rec + 0x26, 4, 1, (void*) file)) {
				return 0;
			}
		}
		if (!ls_ReadVfsDataChecked(rec + 0x1a, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x1e, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x2a, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x2e, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x32, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x36, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x3e, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x42, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x46, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x4a, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x4e, 4, 1, (void*) file)) {
			return 0;
		}
		if (g_file_version >= 0x10014) {
			if (!ls_ReadVfsDataChecked(rec + 0x52, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x56, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x5a, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x3a, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x62, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x66, 4, 1, (void*) file)) {
				return 0;
			}
			if (!ls_ReadVfsDataChecked(rec + 0x6a, 4, 1, (void*) file)) {
				return 0;
			}
		}
		if (g_file_version >= 0x10056) {
			if (!ls_ReadVfsDataChecked(rec + 0x5e, 4, 1, (void*) file)) {
				return 0;
			}
		}
		else {
			*(int*) (rec + 0x5e) = 0x3f800000;
		}
		if (g_file_version >= 0x10015) {
			int count;
			int i;
			char* p;
			count = (g_file_version >= 0x10046) ? 0x11 : 0x0e;
			i = 0;
			p = rec + 0x72;
			if (count > 0) {
				do {
					if (!ls_ReadVfsDataChecked(p, 1, 1, (void*) file)) {
						return 0;
					}
					i++;
					p++;
				} while (i < count);
			}
		}
		if (!ls_ReadVfsDataChecked(rec + 0x86, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x8a, 0x10, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0x9a, 0x0c, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(rec + 0xa6, 4, 1, (void*) file)) {
			return 0;
		}
		if (g_file_version >= 0x10018) {
			if (!ls_ReadVfsDataChecked(rec + 0x6e, 4, 1, (void*) file)) {
				return 0;
			}
		}
		rec += 0xac;
	} while (rec < (char*) 0x1009b762);

	return 1;
}

/* Master entity loader: orchestrates loading all entity
 * types from a save file in the correct order (buildings
 * first, then citizens, then objects). */

// STUB: SERVER 0x10013230
// ls_LoadEntities

// DATA: SERVER 0x1002d4ec
extern int g_save_version;
// DATA: SERVER 0x10035434
extern int g_citizen_count;
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

int __cdecl ls_LoadEntities(int param_1)
{
	int stream;
	int read_result;
	int inner_result;
	unsigned short entity_slot;
	int entity_index;
	int ref_value;

	stream = param_1;
	read_result = ls_ReadVfsDataChecked((void*) &entity_slot, 2, 1, (void*) param_1);
	if (read_result == 0) {
		return 0;
	}
	read_result = ls_ReadVfsDataChecked((void*) &param_1, 4, 1, (void*) stream);
	if (read_result == 0) {
		return 0;
	}
	g_citizen_count = param_1;
	read_result = ls_ReadVfsDataChecked((void*) 0x10035470, 4, 1, (void*) stream);
	if (read_result == 0) {
		return 0;
	}
	read_result = ls_ReadVfsDataChecked((void*) 0x10035474, 4, 1, (void*) stream);
	if (read_result == 0) {
		return 0;
	}
	if (g_save_version > 0x10016) {
		for (read_result = (int) 0x10035478; read_result < (int) 0x10035498; read_result += 4) {
			inner_result = ls_ReadVfsDataChecked((void*) read_result, 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
		}
	}
	entity_index = 0;
	if (0 < param_1) {
		do {
			read_result = ls_ReadVfsDataChecked((void*) &entity_slot, 2, 1, (void*) stream);
			if (read_result == 0) {
				return 0;
			}
			read_result = (entity_slot & 0xffff) * 0x21c;
			*(unsigned short*) (read_result + 0x100358a0) = entity_slot;
			if (g_save_version < 0x1003e) {
				*(int*) (read_result + 0x10035aac) = -1;
			}
			else {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035aac), 4, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358a2), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358a4), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358a8), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358a9), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358aa), 2, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358ac), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358ad), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358b0), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358b4), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358b8), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358bc), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358c0), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358c4), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version > 0x1003a) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358c8), 2, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358cc), 4, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358d0), 0x10, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version > 0x10030) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358e0), 0x10, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358f0), 2, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358f4), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358f8), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x100358fc), 0x20, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version > 0x10023) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x1003591c), 4, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035920), 5, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035928), 0xa8, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a04), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a05), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a06), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a07), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a08), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a09), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			*(int*) (read_result + 0x10035a0c) = 0;
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a0c), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			*(int*) (read_result + 0x10035a10) = 0;
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a10), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version < 0x10020) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a14), 2, 1, (void*) stream);
			}
			else {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a14), 4, 1, (void*) stream);
			}
			if (inner_result == 0) {
				return 0;
			}
			*(int*) (read_result + 0x10035a1c) = 0;
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a1c), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a20), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a2c), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a30), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version < 0x1003e) {
				*(int*) (read_result + 0x10035a30) = 4;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a34), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a38), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a3c), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a40), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a44), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a48), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a4c), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a50), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a51), 1, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a54), 0x10, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a68), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version < 0x10049) {
				*(int*) (read_result + 0x10035a6c) = 0;
			}
			else {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a6c), 4, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a70), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a74), 0x10, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a84), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a88), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a8c), 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			if (g_save_version > 0x10029) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a90), 4, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			if (g_save_version > 0x10020) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a65), 1, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			inner_result = ls_ReadVfsDataChecked((void*) &ref_value, 4, 1, (void*) stream);
			if (inner_result == 0) {
				return 0;
			}
			*(int*) (read_result + 0x10035a24) = ref_value;
			if (g_save_version > 0x10020) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035a94), 0x18, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
			}
			if (g_save_version > 0x10035) {
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035ab0), 4, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035ab4), 1, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035ab5), 1, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035ab6), 1, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
				inner_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035ab7), 1, 1, (void*) stream);
				if (inner_result == 0) {
					return 0;
				}
				read_result = ls_ReadVfsDataChecked((void*) (read_result + 0x10035ab8), 1, 1, (void*) stream);
				if (read_result == 0) {
					return 0;
				}
			}
			entity_index = entity_index + 1;
		} while (entity_index < param_1);
	}
	return 1;
}

/* Loads town-level data from a save file. Reads town name,
 * treasury, population, building counts, and political
 * state (offices, elections). */

// STUB: SERVER 0x10013b10
// ls_LoadTownData

int __cdecl ls_LoadTownData(int file)
{
	int count;
	char* ptr;
	char* inner;
	char* base;
	int i;

	count = 0x3e;
	if (g_file_version >= 0x10048) {
		if (!ls_ReadVfsDataChecked(&count, 4, 1, (void*) file)) {
			return 0;
		}
	}

	for (ptr = (char*) 0x1009b768; ptr < (char*) 0x100a8c38; ptr += 0x2a90) {
		if (!ls_ReadVfsDataChecked(ptr - 8, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr - 4, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 4, 4, 1, (void*) file)) {
			return 0;
		}

		i = 0;
		if (count > 0) {
			inner = ptr + 0x10;
			do {
				if (!ls_ReadVfsDataChecked(inner - 8, 2, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner - 4, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 4, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x18, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x1c, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x28, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x2c, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x30, 4, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x34, 2, 1, (void*) file)) {
					return 0;
				}
				if (!ls_ReadVfsDataChecked(inner + 0x24, 4, 1, (void*) file)) {
					return 0;
				}
				i++;
				inner += 0x80;
			} while (i < count);
		}

	}

	ptr = (char*) 0x100a8c88;
	do {
		base = ptr - 0x48;

		if (!ls_ReadVfsDataChecked(base, 0x20, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr - 8, 8, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 4, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 8, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 0xc, 2, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 0x10, 8, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 0x18, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(ptr + 0x19, 1, 1, (void*) file)) {
			return 0;
		}

		inner = ptr + 0x1c;
		for (i = 0; i < 10; i++) {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, (void*) file)) {
				return 0;
			}
			inner += 8;
		}

		inner = base + 0xb4;
		for (i = 0; i < 10; i++) {
			if (!ls_ReadVfsDataChecked(inner, 8, 1, (void*) file)) {
				return 0;
			}
			inner += 8;
		}

		if (!ls_ReadVfsDataChecked(base + 0x104, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x105, 1, 1, (void*) file)) {
			return 0;
		}

		inner = base + 0x108;
		for (i = 0; i < 4; i++) {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, (void*) file)) {
				return 0;
			}
			inner += 4;
		}

		inner = base + 0x118;
		for (i = 0; i < 4; i++) {
			if (!ls_ReadVfsDataChecked(inner, 4, 1, (void*) file)) {
				return 0;
			}
			inner += 4;
		}

		if (!ls_ReadVfsDataChecked(base + 0x128, 4, 1, (void*) file)) {
			return 0;
		}

		inner = base + 0x12c;
		for (i = 0; i < 0xb; i++) {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, (void*) file)) {
				return 0;
			}
			inner++;
		}

		if (!ls_ReadVfsDataChecked(base + 0x137, 1, 1, (void*) file)) {
			return 0;
		}

		inner = base + 0x138;
		for (i = 0; i < 7; i++) {
			if (!ls_ReadVfsDataChecked(inner, 1, 1, (void*) file)) {
				return 0;
			}
			inner++;
		}

		if (!ls_ReadVfsDataChecked(base + 0x13f, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x140, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x141, 1, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x142, 1, 1, (void*) file)) {
			return 0;
		}

		inner = base + 0x144;
		for (i = 0; i < 8; i++) {
			if (!ls_ReadVfsDataChecked(inner, 0x12, 1, (void*) file)) {
				return 0;
			}
			inner += 0x12;
		}

		if (!ls_ReadVfsDataChecked(base + 0x1d4, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x1d8, 4, 1, (void*) file)) {
			return 0;
		}
		if (!ls_ReadVfsDataChecked(base + 0x1dc, 0xd0, 1, (void*) file)) {
			return 0;
		}

		if (g_file_version >= 0x10037) {
			if (!ls_ReadVfsDataChecked(base + 0x2ec, 8, 1, (void*) file)) {
				return 0;
			}
		}

		ptr += 0x2f4;
	} while (ptr < (char*) 0x100a9858);

	return 1;
}

/* Converts an entity ID to a runtime pointer. Searches the
 * entity tables for a matching ID and returns the memory
 * address. Used during save loading to resolve references. */

extern char s_ls_ID2Ptr____Stadtspieler_Id_not_1002d580[];
extern char s_D__Develop_DieGildeAddOn_loadsav_1002d550[];
extern char s_ls_ID2Ptr____Houston__wir_haben_e_1002d520[];

// FUNCTION: SERVER 0x10014070
// ls_ID2Ptr

__declspec(naked) unsigned int ls_ID2Ptr(void)
{
	__asm {
		_emit 0xa1
		_emit 0x6c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		sub esp, 0xc
		push eax
		call gm_LookupEntityRecordById
		add esp, 4
		_emit 0xa3
		_emit 0x6c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		test eax, eax
		jne L_have_player
		push 1
		push offset s_ls_ID2Ptr____Stadtspieler_Id_not_1002d580
		push 0x1016
		push offset s_D__Develop_DieGildeAddOn_loadsav_1002d550
		call LogMessageInternal
		add esp, 0x10
		xor eax, eax
		add esp, 0xc
		ret
	L_have_player:
		push ebp
		push esi
		push edi
		push 0xa
		push 5
		push 1
		call gm_StartFilteredEntitySearch
		_emit 0xa3
		_emit 0x3c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0xa1
		_emit 0xec
		_emit 0xd4
		_emit 0x02
		_emit 0x10
		add esp, 0xc
		cmp eax, 0x10017
		jl L_skip_lookup_array
		mov esi, 0x10035478
	L_lookup_loop:
		mov ecx, dword ptr [esi]
		push ecx
		call gm_LookupEntityRecordById
		mov dword ptr [esi], eax
		add esi, 4
		add esp, 4
		cmp esi, 0x10035498
		jl L_lookup_loop
	L_skip_lookup_array:
		mov esi, 0x10035a10
		mov edi, 0xffff
	L_entity_loop:
		cmp word ptr [esi - 0x170], di
		je L_entity_skip
		mov ecx, dword ptr [esi - 4]
		lea eax, [esi - 4]
		cmp ecx, -1
		jne L_resolve_a
		mov dword ptr [eax], 0
		jmp L_check_b
	L_resolve_a:
		push ecx
		push 0
		push 0
		push eax
		call gm_ResolveEntityById
		add esp, 0x10
	L_check_b:
		mov eax, dword ptr [esi]
		cmp eax, -1
		jne L_resolve_b
		mov dword ptr [esi], 0
		jmp L_entity_skip
	L_resolve_b:
		push eax
		push 0
		push 0
		push esi
		call gm_ResolveEntityById
		add esp, 0x10
	L_entity_skip:
		add esi, 0x21c
		cmp esi, 0x1009ae10
		jl L_entity_loop
		_emit 0xa1
		_emit 0x50
		_emit 0x54
		_emit 0x03
		_emit 0x10
		xor ebp, ebp
		test eax, eax
		jle L_finish
		xor edi, edi
	L_outer:
		_emit 0x8b
		_emit 0x15
		_emit 0x34
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		xor eax, eax
		mov ax, word ptr [edi + edx]
		lea esi, [edi + edx]
		_emit 0x8b
		_emit 0x15
		_emit 0x50
		_emit 0xe4
		_emit 0x1d
		_emit 0x10
		mov ecx, eax
		shl ecx, 6
		add edx, ecx
		cmp byte ptr [eax + edx], 0x1d
		jne L_after_clear
		mov dword ptr [esi + 0x24], 0
	L_after_clear:
		mov eax, dword ptr [esi + 6]
		cmp eax, -1
		je near L_inc
		push eax
		lea eax, [esp + 0x18]
		lea ecx, [esp + 0x14]
		push eax
		lea edx, [esp + 0x14]
		push ecx
		push edx
		call gm_ResolveEntityById
		add esp, 0x10
		test eax, eax
		jne L_resolved
		push 1
		push offset s_ls_ID2Ptr____Houston__wir_haben_e_1002d520
		push 0x1050
		push offset s_D__Develop_DieGildeAddOn_loadsav_1002d550
		call LogMessageInternal
		add esp, 0x10
		jmp L_inc
	L_resolved:
		mov eax, dword ptr [esp + 0xc]
		test eax, eax
		je L_chk_b
		mov ecx, dword ptr [eax + 0x5d]
		test ecx, ecx
		jne L_walk_5d
		mov dword ptr [eax + 0x5d], esi
		jmp L_inc
	L_walk_5d:
		mov eax, dword ptr [ecx + 0x3f]
		test eax, eax
		je L_attach_3f
	L_walk_5d_loop:
		mov ecx, eax
		mov eax, dword ptr [ecx + 0x3f]
		test eax, eax
		jne L_walk_5d_loop
		jmp L_attach_3f
	L_chk_b:
		mov eax, dword ptr [esp + 0x10]
		test eax, eax
		je L_chk_c
		mov ecx, dword ptr [eax + 0x14]
		test ecx, ecx
		jne L_walk_14
		mov dword ptr [eax + 0x14], esi
		jmp L_inc
	L_walk_14:
		mov eax, dword ptr [ecx + 0x3f]
		test eax, eax
		je L_attach_3f
	L_walk_14_loop:
		mov ecx, eax
		mov eax, dword ptr [ecx + 0x3f]
		test eax, eax
		jne L_walk_14_loop
		jmp L_attach_3f
	L_chk_c:
		mov eax, dword ptr [esp + 0x14]
		mov ecx, dword ptr [eax + 0x178]
		test ecx, ecx
		jne L_walk_178
		mov dword ptr [eax + 0x178], esi
		jmp L_inc
	L_walk_178:
		mov eax, dword ptr [ecx + 0x3f]
		test eax, eax
		je L_attach_3f
	L_walk_178_loop:
		mov ecx, eax
		mov eax, dword ptr [ecx + 0x3f]
		test eax, eax
		jne L_walk_178_loop
	L_attach_3f:
		mov dword ptr [ecx + 0x3f], esi
	L_inc:
		_emit 0xa1
		_emit 0x50
		_emit 0x54
		_emit 0x03
		_emit 0x10
		inc ebp
		add edi, 0x43
		cmp ebp, eax
		jl near L_outer
	L_finish:
		call gm_EntitySetField
		pop edi
		pop esi
		mov eax, 1
		pop ebp
		add esp, 0xc
		ret
	}
}

/* Receives and loads a complete game state from a client.
 * Called during lobby-to-game transition to receive the
 * savegame data stream and initialize the game world. */

// STUB: SERVER 0x10014260
// srv_RecvGame

int srv_RecvGame(void)
{
	int file_handle;
	int load_status;
	char* entity_state_ptr;

	file_handle = OpenVfsStream((char*) g_101deae8, (char*) g_101deac0, (int) (const char*) 0x1002944c);
	if (file_handle == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x11fe,
			"ls_RecvGame(): Can\'t open File",
			1
		);
		m_FreeTracked((void*) g_101de560);
		g_101de560 = 0;
		return 0;
	}
	ls_LoadSavegameHeader(file_handle, (char*) g_save_info);
	if (((g_save_info[1] & 2) == 0) || (0x1005a < g_save_info[0]) || (g_save_info[0] < 0x10013)) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
			0x120a,
			"srv_RecvGame(): Can\'t load Counter",
			1
		);
		CloseVfsStream(file_handle);
		m_FreeTracked((void*) g_101de560);
		g_101de560 = 0;
		return 0;
	}
	*(int*) 0x1003546c = 0;
	load_status = ls_ReadVfsDataChecked((void*) 0x10030b6c, 4, 1, (void*) file_handle);
	if (load_status != 0) {
		load_status = ls_ReadVfsDataChecked((void*) 0x1176408c, 4, 1, (void*) file_handle);
		if (load_status != 0) {
			load_status = ls_ReadVfsDataChecked((void*) 0x10035880, 0xe, 1, (void*) file_handle);
			if (load_status != 0) {
				load_status = ls_ReadVfsDataChecked((void*) 0x10035439, 1, 1, (void*) file_handle);
				if (load_status != 0) {
					load_status = ls_ReadVfsDataChecked((void*) 0x1003546c, 4, 1, (void*) file_handle);
					if (load_status != 0) {
						load_status = ls_ReadVfsDataChecked((void*) 0x1003542c, 4, 1, (void*) file_handle);
						if (load_status != 0) {
							load_status = ls_ReadVfsDataChecked((void*) 0x10035430, 4, 1, (void*) file_handle);
							if (load_status != 0) {
								load_status = ls_ReadVfsDataChecked((void*) 0x10035434, 4, 1, (void*) file_handle);
								if (load_status != 0) {
									ls_ReadVfsDataChecked((void*) 0x10035440, 4, 1, (void*) file_handle);
									ls_ReadVfsDataChecked((void*) 0x101de580, 0x18, 1, (void*) file_handle);
									if (g_save_version >= 0x10030) {
										ls_ReadVfsDataChecked((void*) 0x10030b70, 4, 1, (void*) file_handle);
									}
									if (g_save_version >= 0x1003d) {
										ls_ReadVfsDataChecked((void*) 0x10035408, 4, 1, (void*) file_handle);
									}
									else {
										*(int*) 0x10035408 = 1000000;
									}
									load_status = ls_LoadExistingEntities(file_handle);
									if (load_status != 0) {
										load_status = ls_LoadBuildingEntityState(file_handle);
										if (load_status == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x123d,
												"LoadGame(): Can\'t load Buildings",
												1
											);
											CloseVfsStream(file_handle);
											m_FreeTracked((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										load_status = ls_LoadDynamicEntities((void*) file_handle);
										if (load_status == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x1246,
												"srv_RecvGame(): Can\'t load Dynasties",
												1
											);
											CloseVfsStream(file_handle);
											m_FreeTracked((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										load_status = ls_LoadEntities(file_handle);
										if (load_status == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x124f,
												"srv_RecvGame(): Can\'t load Players",
												1
											);
											CloseVfsStream(file_handle);
											m_FreeTracked((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										entity_state_ptr = (char*) 0x100358a2;
										do {
											if (*(unsigned short*) (entity_state_ptr - 2) != 0xffff &&
												*entity_state_ptr == '\x06') {
												*entity_state_ptr = '\x05';
											}
											entity_state_ptr = entity_state_ptr + 0x21c;
										} while ((int) entity_state_ptr < (int) 0x1009aca2);
										load_status = ls_LoadTownData(file_handle);
										if (load_status == 0) {
											LogMessageInternal(
												"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
												0x125b,
												"srv_RecvGame(): Can\'t load Towns",
												1
											);
											CloseVfsStream(file_handle);
											m_FreeTracked((void*) g_101de560);
											g_101de560 = 0;
											return 0;
										}
										if (g_save_version >= 0x10045) {
											load_status = amt_fio_LoadAemter(file_handle, g_save_version);
											if (load_status == 0) {
												LogMessageInternal(
													"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
													0x1266,
													"srv_RecvGame(): Can\'t load Aemter",
													1
												);
												CloseVfsStream(file_handle);
												return 0;
											}
										}
										load_status = ls_ID2Ptr();
										if (load_status != 0) {
											CloseVfsStream(file_handle);
											return 1;
										}
										LogMessageInternal(
											"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
											0x126f,
											"srv_RecvGame(): Can\'t convert IDs to Pointers",
											1
										);
										CloseVfsStream(file_handle);
										m_FreeTracked((void*) g_101de560);
										g_101de560 = 0;
										return 0;
									}
									LogMessageInternal(
										"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
										0x1234,
										"srv_RecvGame(): Can\'t load Objects",
										1
									);
									CloseVfsStream(file_handle);
									m_FreeTracked((void*) g_101de560);
									g_101de560 = 0;
									return 0;
								}
							}
						}
					}
				}
			}
		}
	}
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\loadsave\\loadsave.c",
		0x121e,
		"srv_RecvGame(): Can\'t load Counter",
		1
	);
	CloseVfsStream(file_handle);
	m_FreeTracked((void*) g_101de560);
	g_101de560 = 0;
	return 0;
}
