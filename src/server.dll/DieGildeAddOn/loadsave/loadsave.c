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
extern int g_query_limit;
int __cdecl ls_LoadGraveyardData(int stream_ctx, int dest_buf);
int __cdecl ahm_AllocAhmInfo(int building, int slot);
extern int g_file_version; /* 0x1002d4ec */
;
extern unsigned char* g_entity_ptr; /* 0x1014d8c0 */
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
extern char s_ls_ID2Ptr____Stadtspieler_Id_not_1002d580[];
extern char s_D__Develop_DieGildeAddOn_loadsav_1002d550[];
extern char s_ls_ID2Ptr____Houston__wir_haben_e_1002d520[];
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


__declspec(naked) int __cdecl ls_LoadGraveyardData(int arg1, int arg2)
{
	(void) arg1;
	(void) arg2;
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

int __cdecl ls_LoadGraveyardData_unused(int arg1, int arg2)
{
	int field_base;
	int ret;
	int ptr;
	int edi;
	int i;
	(void) arg1;
	(void) arg2;
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

__declspec(naked) void ls_InitNewDynastyEntity(int arg1, int arg2, char* arg3, char* arg4)
{
	(void) arg1;
	(void) arg2;
	(void) arg3;
	(void) arg4;
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

// FUNCTION: SERVER 0x100127d0
// ls_LoadExistingEntities


void __cdecl gm_CleanupObjectEntities(void);

__declspec(naked) int __cdecl ls_LoadExistingEntities(int arg1)
{
	(void) arg1;
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

// DATA: SERVER 0x1002d4ec
// DATA: SERVER 0x10035434
extern int g_citizen_count;
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

int __cdecl ls_LoadEntities(int arg1)
{
	int stream;
	int read_result;
	int inner_result;
	unsigned short entity_slot;
	int entity_index;
	int ref_value;

	stream = arg1;
	read_result = ls_ReadVfsDataChecked((void*) &entity_slot, 2, 1, (void*) arg1);
	if (read_result == 0) {
		return 0;
	}
	read_result = ls_ReadVfsDataChecked((void*) &arg1, 4, 1, (void*) stream);
	if (read_result == 0) {
		return 0;
	}
	g_citizen_count = arg1;
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
	if (0 < arg1) {
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
		} while (entity_index < arg1);
	}
	return 1;
}

/* Loads town-level data from a save file. Reads town name,
 * treasury, population, building counts, and political
 * state (offices, elections). */

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
