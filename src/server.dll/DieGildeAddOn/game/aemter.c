#include <stdio.h>
#include "../../Units/Error/error.h"

// SIZE 0x18
typedef struct {
	int value;
	char type;
	char pad[19];
} ENT;

#pragma pack(push, 1)
// SIZE 0x18
typedef struct {
	char key;
	char pad[3];
	int entityId;
	char field8;
	char rest[15];
} SlotEntry;
#pragma pack(pop)

extern SlotEntry DAT_101de5a0[];
extern int DAT_101de5a4;
extern char DAT_101de5a8;
extern int DAT_101de5ac;
extern char DAT_101de5b0;
void* __cdecl gm_LookupEntityRecordById(int);
extern int DAT_101de5b4[];
extern ENT g_ents[];
extern ENT g_ents2[];
extern unsigned short DAT_10035884;
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx);
void __cdecl InitBuildingTypeTable(void);

/* Validates if an entity is eligible for an office position.
 * Checks entity type, existing office holdings, and eligibility
 * requirements. Returns 0 on success, non-zero on failure. */

// FUNCTION: SERVER 0x1000b1c0
// amt_ValidateOfficeCandidate

void* __cdecl gm_LookupEntityRecordById(int entityId);

__declspec(naked) int __cdecl amt_ValidateOfficeCandidate(int* arg1)
{
	(void) arg1;
	__asm {
		push ebx
		push esi
		mov esi, dword ptr [esp + 0xc]
		mov eax, dword ptr [esi]
		push eax
		call gm_LookupEntityRecordById
		add esp, 4
		test eax, eax
		je L_ret0
		mov cl, byte ptr [eax + 0x168]
		test cl, cl
		jne L_ret0
		mov dl, byte ptr [esi + 4]
		xor ecx, ecx
		mov eax, 0x101de5a0
	L_loop1:
		cmp byte ptr [eax], dl
		je L_found1
		add eax, 0x18
		inc ecx
		cmp eax, 0x101de870
		jl L_loop1
	L_ret0:
		pop esi
		xor eax, eax
		pop ebx
		ret
	L_found1:
		cmp ecx, 0x1e
		jge L_ret0
		lea eax, [ecx + ecx*2]
		shl eax, 3
		cmp dword ptr [eax + 0x101de5a4], -1
		jne L_ret0
		cmp byte ptr [eax + 0x101de5b0], 3
		jne L_ret0
		cmp dword ptr [eax + 0x101de5ac], 4
		jge L_ret0
		mov bl, byte ptr [eax + 0x101de5a8]
		mov al, byte ptr [esi + 6]
		cmp al, bl
		jne L_ret0
		mov dl, byte ptr [esi + 5]
		cmp dl, 0xff
		je L_ret1
		xor ecx, ecx
		mov eax, 0x101de5a0
	L_loop2:
		cmp byte ptr [eax], dl
		je L_found2
		add eax, 0x18
		inc ecx
		cmp eax, 0x101de870
		jl L_loop2
		pop esi
		xor eax, eax
		pop ebx
		ret
	L_found2:
		cmp ecx, 0x1e
		jge L_ret0
		lea eax, [ecx + ecx*2]
		shl eax, 3
		cmp bl, byte ptr [eax + 0x101de5a8]
		jne L_ret0
		cmp dword ptr [eax + 0x101de5a4], -1
		jne L_ret0
		cmp byte ptr [eax + 0x101de5b0], 3
		jne L_ret0
		cmp dword ptr [eax + 0x101de5ac], 4
		jge L_ret0
	L_ret1:
		pop esi
		mov eax, 1
		pop ebx
		ret
	}
}

/* Validates preconditions and assigns an office to an entity.
 * Performs eligibility checks, then updates the office holder
 * table and entity links. */

extern char DAT_10029bb8[];

// FUNCTION: SERVER 0x1000b290
// ValidateAndAssignOffice

__declspec(naked) unsigned int ValidateAndAssignOffice(unsigned int* arg1)
{
	(void) arg1;
	__asm {
		sub esp, 0x18
		push ebx
		push ebp
		push esi
		mov esi, dword ptr [esp + 0x28]
		push edi
		mov eax, dword ptr [esi]
		push eax
		call gm_LookupEntityRecordById
		mov ebp, eax
		add esp, 4
		test ebp, ebp
		je L_fail
		_emit 0x66
		_emit 0x81
		_emit 0x7d
		_emit 0x00
		_emit 0xff
		_emit 0xff
		je L_fail
		mov al, byte ptr [ebp + 0x168]
		test al, al
		jne L_fail
		mov al, byte ptr [esi + 4]
		xor edx, edx
		mov ecx, 0x101de5a0
	L_scan1:
		cmp byte ptr [ecx], al
		je L_found1
		add ecx, 0x18
		inc edx
		cmp ecx, 0x101de870
		jl L_scan1
	L_fail:
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		add esp, 0x18
		ret
	L_found1:
		cmp edx, 0x1e
		jge L_fail
		mov cl, byte ptr [esi + 6]
		lea edx, [edx + edx*2]
		shl edx, 3
		mov byte ptr [esp + 0x2c], cl
		mov al, byte ptr [edx + 0x101de5a8]
		cmp cl, al
		jne L_fail
		mov bl, byte ptr [esi + 5]
		cmp bl, 0xff
		je L_simple_path
		xor esi, esi
		mov ecx, 0x101de5a0
	L_scan2:
		cmp byte ptr [ecx], bl
		je L_found2
		add ecx, 0x18
		inc esi
		cmp ecx, 0x101de870
		jl L_scan2
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		add esp, 0x18
		ret
	L_found2:
		cmp esi, 0x1e
		jge L_fail
		lea ebx, [esi + esi*2]
		shl ebx, 3
		cmp al, byte ptr [ebx + 0x101de5a8]
		jne L_fail
		and eax, 0xff
		lea edi, [esp + 0x10]
		lea ecx, [eax + eax*2]
		mov eax, dword ptr [esp + 0x2c]
		lea esi, [ecx*8 + 0x10029bb8]
		mov ecx, 6
		rep movsd
		mov esi, dword ptr [esp + 0x10]
		mov ecx, eax
		and ecx, 0xff
		cmp esi, ecx
		jne L_fail
		mov ecx, dword ptr [esp + 0x20]
		test ecx, ecx
		je L_fail
		mov ecx, dword ptr [edx + 0x101de5a4]
		or esi, 0xffffffff
		cmp ecx, esi
		jne L_fail
		cmp byte ptr [edx + 0x101de5b0], 3
		jne L_fail
		mov edi, dword ptr [edx + 0x101de5ac]
		mov ecx, 4
		cmp edi, ecx
		jge L_fail
		cmp dword ptr [ebx + 0x101de5a4], esi
		jne L_fail
		cmp dword ptr [ebx + 0x101de5ac], ecx
		jge L_fail
		mov byte ptr [ebp + 0x168], al
		mov ecx, dword ptr [edx + 0x101de5ac]
		inc ecx
		pop edi
		mov dword ptr [edx + 0x101de5ac], ecx
		mov eax, dword ptr [ebx + 0x101de5ac]
		inc eax
		pop esi
		mov dword ptr [ebx + 0x101de5ac], eax
		pop ebp
		mov eax, 1
		pop ebx
		add esp, 0x18
		ret
	L_simple_path:
		cmp dword ptr [edx + 0x101de5a4], -1
		jne L_fail
		cmp byte ptr [edx + 0x101de5b0], 3
		jne L_fail
		cmp dword ptr [edx + 0x101de5ac], 4
		jge L_fail
		mov byte ptr [ebp + 0x168], cl
		mov eax, dword ptr [edx + 0x101de5ac]
		inc eax
		pop edi
		pop esi
		mov dword ptr [edx + 0x101de5ac], eax
		pop ebp
		mov eax, 1
		pop ebx
		add esp, 0x18
		ret
	}
}

/* Validates a generic office command string. Parses the command
 * buffer and checks that the referenced entities and office
 * type are valid. Returns 0 if valid. */

// FUNCTION: SERVER 0x1000b440
// amt_ValidateCommand

__declspec(naked) int __cdecl amt_ValidateCommand(char* arg1)
{
	(void) arg1;
	__asm {
		push esi
		mov esi, dword ptr [esp + 8]
		cmp byte ptr [esi + 6], 0xff
		je L_ret1
		mov dl, byte ptr [esi]
		xor ecx, ecx
		mov eax, 0x101de5a0
	L_loop:
		cmp byte ptr [eax], dl
		je L_found
		add eax, 0x18
		inc ecx
		cmp eax, 0x101de990
		jl L_loop
		pop esi
		xor eax, eax
		ret
	L_found:
		cmp ecx, 0x2a
		jl L_check_b0
		pop esi
		xor eax, eax
		ret
	L_check_b0:
		lea eax, [ecx + ecx*2]
		shl eax, 3
		cmp byte ptr [eax + 0x101de5b0], 1
		je L_check_b4
		pop esi
		xor eax, eax
		ret
	L_check_b4:
		cmp dword ptr [eax + 0x101de5b4], -1
		je L_check_p7
		pop esi
		xor eax, eax
		ret
	L_check_p7:
		mov eax, dword ptr [esi + 7]
		cmp eax, -1
		je L_check_p1
		push eax
		call gm_LookupEntityRecordById
		add esp, 4
		test eax, eax
		jne L_check_p1
		pop esi
		ret
	L_check_p1:
		mov eax, dword ptr [esi + 1]
		cmp eax, -1
		je L_ret1
		push eax
		call gm_LookupEntityRecordById
		add esp, 4
		test eax, eax
		jne L_ret1
		pop esi
		ret
	L_ret1:
		pop esi
		mov eax, 1
		ret
	}
}

/* Executes an office assignment. Updates the office holder table,
 * assigns benefits and duties to the new holder, and notifies
 * the game state of the change. */

// FUNCTION: SERVER 0x1000B820
// amt_FindEntity26

void __cdecl amt_FindEntity26(int val)
{
	unsigned int i;
	for (i = 0x29; i != 0; i--) {
		if (g_ents[i].type == 0x26) {
			g_ents[i].value = val;
			return;
		}
	}
}

/* Searches for an entity with type 0x27 (specific entity class)
 * matching the given value. Used for office-related lookups. */

// FUNCTION: SERVER 0x1000B850
// amt_FindEntity27

void __cdecl amt_FindEntity27(int val)
{
	unsigned int i;
	for (i = 0x29; i != 0; i--) {
		if (g_ents2[i].type == 0x27) {
			g_ents2[i].value = val;
			return;
		}
	}
}

/* Swaps two office holders. Exchanges position assignments
 * between the entities referenced in the param array. Returns 0
 * on success, or non-zero if the swap is invalid. */

// FUNCTION: SERVER 0x1000b880
// amt_SwapOfficeHolders

__declspec(naked) int __cdecl amt_SwapOfficeHolders(int* arg1)
{
	(void) arg1;
	__asm {
		push ebx
		mov ebx, dword ptr [esp + 8]
		push ebp
		push esi
		mov eax, dword ptr [ebx]
		push edi
		push eax
		call gm_LookupEntityRecordById
		add esp, 4
		mov dword ptr [esp + 0x14], eax
		test eax, eax
		jne L_have_req
		pop edi
		pop esi
		pop ebp
		pop ebx
		ret
	L_have_req:
		mov ecx, dword ptr [eax + 0x194]
		mov eax, dword ptr [ebx + 6]
		cmp ecx, eax
		jge L_scan_a
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		ret
	L_scan_a:
		mov dl, byte ptr [ebx + 4]
		xor ecx, ecx
		mov eax, 0x101de5a0
	L_loop_a:
		cmp byte ptr [eax], dl
		je L_found_a
		add eax, 0x18
		inc ecx
		cmp eax, 0x101de870
		jl L_loop_a
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		ret
	L_found_a:
		lea edx, [ecx + ecx*2]
		lea edi, [edx*8 + 0x101de5a0]
		test edi, edi
		jne L_have_a
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		ret
	L_have_a:
		mov eax, dword ptr [edi + 4]
		push eax
		call gm_LookupEntityRecordById
		mov ebp, eax
		add esp, 4
		test ebp, ebp
		jne L_scan_b
		pop edi
		pop esi
		pop ebp
		pop ebx
		ret
	L_scan_b:
		mov dl, byte ptr [ebx + 5]
		xor ecx, ecx
		mov eax, 0x101de5a0
	L_loop_b:
		cmp byte ptr [eax], dl
		je L_found_b
		add eax, 0x18
		inc ecx
		cmp eax, 0x101de870
		jl L_loop_b
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		ret
	L_found_b:
		lea ecx, [ecx + ecx*2]
		lea esi, [ecx*8 + 0x101de5a0]
		test esi, esi
		jne L_have_b
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		ret
	L_have_b:
		mov edx, dword ptr [esi + 4]
		push edx
		call gm_LookupEntityRecordById
		add esp, 4
		test eax, eax
		jne L_do_swap
		pop edi
		pop esi
		pop ebp
		pop ebx
		ret
	L_do_swap:
		mov cl, byte ptr [esi + 8]
		mov byte ptr [ebp + 0x166], cl
		mov dl, byte ptr [edi + 8]
		mov byte ptr [eax + 0x166], dl
		mov ecx, dword ptr [esi + 4]
		mov eax, dword ptr [edi + 4]
		mov dword ptr [edi + 4], ecx
		mov dword ptr [esi + 4], eax
		mov eax, dword ptr [esp + 0x14]
		mov edx, dword ptr [ebx + 6]
		pop edi
		mov ecx, dword ptr [eax + 0x194]
		pop esi
		sub ecx, edx
		pop ebp
		mov dword ptr [eax + 0x194], ecx
		mov eax, 1
		pop ebx
		ret
	}
}

/* Clears all entity links for an office position. Removes
 * the holder and resets associated entity references. */

// FUNCTION: SERVER 0x1000b990
// amt_ClearEntityLinks

__declspec(naked) int __cdecl amt_ClearEntityLinks(int arg1)
{
	(void) arg1;
	__asm {
		push ebx
		push ebp
		mov ebp, dword ptr [esp + 0xc]
		push esi
		mov si, word ptr [DAT_10035884]
		xor ebx, ebx
		xor eax, eax
		mov ecx, 0x101de5b4
	L_loop1:
		mov edx, dword ptr [ebp + 4]
		cmp dword ptr [ecx - 0x10], edx
		jne L_else1
		cmp si, 0xb
		mov dword ptr [ecx - 0x10], 0xffffffff
		seta dl
		add edx, 3
		mov dword ptr [ecx], 0xffffffff
		mov byte ptr [ecx - 4], dl
		mov dword ptr [ecx - 8], ebx
		or al, 1
		jmp L_loop1_next
	L_else1:
		cmp dword ptr [ecx], edx
		jne L_loop1_next
		mov dword ptr [ecx], 0xffffffff
		mov byte ptr [ecx - 4], 1
	L_loop1_next:
		add ecx, 0x18
		cmp ecx, 0x101de9a4
		jl L_loop1
		cmp byte ptr [ebp + 0x168], bl
		je L_skip_loop2
		mov ecx, 0x101de5ac
	L_loop2:
		mov dl, byte ptr [ecx - 4]
		cmp dl, byte ptr [ebp + 0x168]
		jne L_loop2_next
		mov edx, dword ptr [ecx]
		cmp edx, ebx
		jle L_loop2_next
		dec edx
		or al, 1
		mov dword ptr [ecx], edx
	L_loop2_next:
		add ecx, 0x18
		cmp ecx, 0x101de99c
		jl L_loop2
	L_skip_loop2:
		mov byte ptr [ebp + 0x166], bl
		mov byte ptr [ebp + 0x169], bl
		mov byte ptr [ebp + 0x168], bl
		pop esi
		pop ebp
		pop ebx
		ret
	}
}

/* Updates entity links for an office assignment. Sets up
 * the bidirectional references between the office slot and
 * the entity holding it. */

// FUNCTION: SERVER 0x1000ba30
// amt_UpdateEntityLinks

__declspec(naked) void __cdecl amt_UpdateEntityLinks(int arg1, int arg2)
{
	(void) arg1;
	(void) arg2;
	__asm {
		mov dx, word ptr [DAT_10035884]
		push ebx
		push ebp
		mov ebp, dword ptr [esp + 0xc]
		push esi
		xor ebx, ebx
		xor esi, esi
		mov eax, 0x101de5b4
	L_loop1:
		mov ecx, dword ptr [ebp + 4]
		cmp dword ptr [eax - 0x10], ecx
		jne L_else1
		cmp dword ptr [esp + 0x14], ebx
		je L_else1_load
		mov ebp, dword ptr [esp + 0x10]
		cmp dx, 0xb
		seta cl
		mov dword ptr [eax - 0x10], 0xffffffff
		add ecx, 3
		mov dword ptr [eax], 0xffffffff
		mov byte ptr [eax - 4], cl
		mov dword ptr [eax - 8], ebx
		or esi, 1
		jmp L_loop1_next
	L_else1_load:
		mov ebp, dword ptr [esp + 0x10]
	L_else1:
		cmp dword ptr [eax], ecx
		jne L_loop1_next
		mov dword ptr [eax], 0xffffffff
		mov byte ptr [eax - 4], 1
	L_loop1_next:
		add eax, 0x18
		cmp eax, 0x101de9a4
		jl L_loop1
		cmp byte ptr [ebp + 0x168], bl
		je L_skip_loop2
		mov eax, 0x101de5ac
	L_loop2:
		mov dl, byte ptr [eax - 4]
		mov cl, byte ptr [ebp + 0x168]
		cmp dl, cl
		jne L_loop2_next
		mov ecx, dword ptr [eax]
		cmp ecx, ebx
		jle L_loop2_next
		dec ecx
		or esi, 1
		mov dword ptr [eax], ecx
	L_loop2_next:
		add eax, 0x18
		cmp eax, 0x101de99c
		jl L_loop2
	L_skip_loop2:
		cmp dword ptr [esp + 0x14], ebx
		je L_skip_param2
		mov byte ptr [ebp + 0x166], bl
		mov byte ptr [ebp + 0x169], bl
	L_skip_param2:
		mov byte ptr [ebp + 0x168], bl
		pop esi
		pop ebp
		pop ebx
		ret
	}
}

/* File I/O loader for office data (Aemter). Reads office
 * holder assignments from a save file via VFS and populates
 * the runtime office tables. */

extern char s_amt_fio_LoadAemter____Can_t_load_1002a0c8[];
extern char s_D__Develop_DieGildeAddOn_game_ae_1002a0a0[];
extern char s_amt_fio_LoadAemter____count_read_1002a06c[];
extern char s_amt_fio_LoadAemter____Can_t_load_1002a048[];
extern char s_amt_fio_LoadAemter____Can_t_load_1002a01c[];
extern char s_amt_fio_LoadAemter____Can_t_load_10029ff4[];
extern char s_amt_fio_LoadAemter____Can_t_load_10029fcc[];
extern char s_amt_fio_LoadAemter____Can_t_load_10029fa4[];
extern char s_amt_fio_LoadAemter____Can_t_load_10029f78[];
extern int __cdecl sprintf(char*, const char*, ...);

// FUNCTION: SERVER 0x1000baf0
// amt_fio_LoadAemter

__declspec(naked) unsigned int __cdecl amt_fio_LoadAemter(int arg1, int arg2)
{
	(void) arg1;
	(void) arg2;
	__asm {
		sub esp, 0x104
		xor eax, eax
		push ebx
		push ebp
		push esi
		push edi
		cmp dword ptr [esp + 0x11c], 0x10051
		setl al
		dec eax
		and eax, 5
		add eax, 0x25
		mov ebp, eax
		call InitBuildingTypeTable
		mov edi, dword ptr [esp + 0x118]
		test edi, edi
		jne L_have_handle
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		add esp, 0x104
		ret
	L_have_handle:
		push edi
		push 1
		lea ecx, [esp + 0x18]
		push 4
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		jne L_count_ok
		push 1
		push offset s_amt_fio_LoadAemter____Can_t_load_1002a0c8
		push 0xe73
		push offset s_D__Develop_DieGildeAddOn_game_ae_1002a0a0
		call LogMessageInternal
		add esp, 0x10
		xor eax, eax
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x104
		ret
	L_count_ok:
		mov eax, dword ptr [esp + 0x10]
		cmp eax, ebp
		je L_loop_init
		push 0x2a
		push eax
		lea edx, [esp + 0x1c]
		push offset s_amt_fio_LoadAemter____count_read_1002a06c
		push edx
		call sprintf
		lea eax, [esp + 0x24]
		push 1
		push eax
		push 0xe7c
		push offset s_D__Develop_DieGildeAddOn_game_ae_1002a0a0
		call LogMessageInternal
		add esp, 0x20
		xor eax, eax
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x104
		ret
	L_loop_init:
		xor ebx, ebx
		test ebp, ebp
		jbe near L_done
		mov esi, 0x101de5a4
	L_loop:
		push edi
		push 1
		lea ecx, [esi - 4]
		push 1
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_err_id
		push edi
		push 1
		push 4
		push esi
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_err_playerid
		push edi
		push 1
		lea edx, [esi + 4]
		push 1
		push edx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_err_amt
		push edi
		push 1
		lea eax, [esi + 8]
		push 4
		push eax
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_err_pcount
		push edi
		push 1
		lea ecx, [esi + 0xc]
		push 1
		push ecx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_err_status
		push edi
		push 1
		lea edx, [esi + 0x10]
		push 4
		push edx
		call ls_ReadVfsDataChecked
		add esp, 0x10
		test eax, eax
		je near L_err_last
		inc ebx
		add esi, 0x18
		cmp ebx, ebp
		jb near L_loop
	L_done:
		pop edi
		pop esi
		pop ebp
		mov eax, 1
		pop ebx
		add esp, 0x104
		ret
	L_err_id:
		push 1
		push offset s_amt_fio_LoadAemter____Can_t_load_1002a048
		push 0xe82
		push offset s_D__Develop_DieGildeAddOn_game_ae_1002a0a0
		call LogMessageInternal
		add esp, 0x10
		xor eax, eax
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x104
		ret
	L_err_playerid:
		push 1
		push offset s_amt_fio_LoadAemter____Can_t_load_1002a01c
		push 0xe83
		push offset s_D__Develop_DieGildeAddOn_game_ae_1002a0a0
		call LogMessageInternal
		add esp, 0x10
		xor eax, eax
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x104
		ret
	L_err_amt:
		push 1
		push offset s_amt_fio_LoadAemter____Can_t_load_10029ff4
		push 0xe84
		push offset s_D__Develop_DieGildeAddOn_game_ae_1002a0a0
		call LogMessageInternal
		add esp, 0x10
		xor eax, eax
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x104
		ret
	L_err_pcount:
		push 1
		push offset s_amt_fio_LoadAemter____Can_t_load_10029fcc
		push 0xe85
		push offset s_D__Develop_DieGildeAddOn_game_ae_1002a0a0
		call LogMessageInternal
		add esp, 0x10
		xor eax, eax
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x104
		ret
	L_err_status:
		push 1
		push offset s_amt_fio_LoadAemter____Can_t_load_10029fa4
		push 0xe86
		push offset s_D__Develop_DieGildeAddOn_game_ae_1002a0a0
		call LogMessageInternal
		add esp, 0x10
		xor eax, eax
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x104
		ret
	L_err_last:
		push 1
		push offset s_amt_fio_LoadAemter____Can_t_load_10029f78
		push 0xe87
		push offset s_D__Develop_DieGildeAddOn_game_ae_1002a0a0
		call LogMessageInternal
		add esp, 0x10
		xor eax, eax
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x104
		ret
	}
}

// DATA: SERVER 0x101de5a4
extern char g_aemter_table[];

unsigned int __cdecl amt_fio_LoadAemter_unused(int stream_handle, int version)
{
	unsigned int num_entries;
	unsigned int i;
	char* ptr;
	unsigned int stored_count;
	char buf[256];

	num_entries = (((unsigned int) (version < 0x10051) - 1) & 5) + 0x25;

	InitBuildingTypeTable();

	if (stream_handle == 0) {
		return 0;
	}

	if (ls_ReadVfsDataChecked(&stored_count, 4, 1, stream_handle) == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\aemter.c",
			0xe73,
			"amt_fio_LoadAemter(): Can\'t load count",
			1
		);
		return 0;
	}

	if (stored_count != num_entries) {
		sprintf(buf, "amt_fio_LoadAemter(): wrong count %d (expected %d)", stored_count, 0x2a);
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe7c, buf, 1);
		return 0;
	}

	i = 0;
	if (num_entries > 0) {
		ptr = g_aemter_table;
		do {
			if (ls_ReadVfsDataChecked(ptr - 4, 1, 1, stream_handle) == 0) {
				goto err_id;
			}
			if (ls_ReadVfsDataChecked(ptr, 4, 1, stream_handle) == 0) {
				goto err_playerid;
			}
			if (ls_ReadVfsDataChecked(ptr + 4, 1, 1, stream_handle) == 0) {
				goto err_amt;
			}
			if (ls_ReadVfsDataChecked(ptr + 8, 4, 1, stream_handle) == 0) {
				goto err_pcount;
			}
			if (ls_ReadVfsDataChecked(ptr + 0xc, 1, 1, stream_handle) == 0) {
				goto err_status;
			}
			if (ls_ReadVfsDataChecked(ptr + 0x10, 4, 1, stream_handle) == 0) {
				goto err_last;
			}
			i++;
			ptr += 0x18;
		} while (i < num_entries);
	}

	return 1;

err_id:
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe82, "amt_fio_LoadAemter(): Can\'t load id", 1);
	return 0;
err_playerid:
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\aemter.c",
		0xe83,
		"amt_fio_LoadAemter(): Can\'t load mplayerid",
		1
	);
	return 0;
err_amt:
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\aemter.c",
		0xe84,
		"amt_fio_LoadAemter(): Can\'t load mamt",
		1
	);
	return 0;
err_pcount:
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\aemter.c",
		0xe85,
		"amt_fio_LoadAemter(): Can\'t load pcount",
		1
	);
	return 0;
err_status:
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\aemter.c",
		0xe86,
		"amt_fio_LoadAemter(): Can\'t load status",
		1
	);
	return 0;
err_last:
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\aemter.c", 0xe87, "amt_fio_LoadAemter(): Can\'t load ???", 1);
	return 0;
}
