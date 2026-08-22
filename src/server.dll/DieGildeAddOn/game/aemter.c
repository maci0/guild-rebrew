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

