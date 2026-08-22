#include <stdio.h>
#include "../../Units/Error/error.h"

// SIZE 0x18
typedef struct {
	int value;
	char type;
	char pad[19];
} ENT;

extern int g_aemter_table;
void* __cdecl gm_LookupEntityRecordById(int);
extern ENT g_ents[];
extern ENT g_ents2[];
extern unsigned short g_default_value_b;
int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, int streamCtx);
void __cdecl InitBuildingTypeTable(void);

/* Validates if an entity is eligible for an office position.
 * Checks entity type, existing office holdings, and eligibility
 * requirements. Returns 0 on success, non-zero on failure. */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
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
		mov si, word ptr [g_default_value_b]
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
		mov dx, word ptr [g_default_value_b]
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

char s_amt_fio_LoadAemter____Can_t_load_1002a0c8[] = "amt_fio_LoadAemter(): Can't load count";
char s_D__Develop_DieGildeAddOn_game_ae_1002a0a0[] = "D:\\Develop\\DieGildeAddOn\\game\\aemter.c";
char s_amt_fio_LoadAemter____count_read_1002a06c[] = "amt_fio_LoadAemter(): count read is %i, expected %i";
char s_amt_fio_LoadAemter____Can_t_load_1002a048[] = "amt_fio_LoadAemter(): Can't load id";
char s_amt_fio_LoadAemter____Can_t_load_1002a01c[] = "amt_fio_LoadAemter(): Can't load mplayerid";
char s_amt_fio_LoadAemter____Can_t_load_10029ff4[] = "amt_fio_LoadAemter(): Can't load mamt";
char s_amt_fio_LoadAemter____Can_t_load_10029fcc[] = "amt_fio_LoadAemter(): Can't load pcount";
char s_amt_fio_LoadAemter____Can_t_load_10029fa4[] = "amt_fio_LoadAemter(): Can't load status";
char s_amt_fio_LoadAemter____Can_t_load_10029f78[] = "amt_fio_LoadAemter(): Can't load msetter";
extern int __cdecl sprintf(char*, const char*, ...);

