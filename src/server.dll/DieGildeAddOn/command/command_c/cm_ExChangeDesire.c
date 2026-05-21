
#include "../command_internal.h"
#include "../../../Units/Error/error.h"


extern double _g_stat_min_d;
extern double _g_stat_max_d;

/* Execution handler: modifies a character's desire/need stat.
 * Reads entity and stat index from the command, applies a delta
 * or sets an absolute value to the desire field. */

// FUNCTION: SERVER 0x1000e9c0
__declspec(naked) int __cdecl cm_ExChangeDesire(uchar* cmd, uchar* result)
{
	(void) cmd;
	(void) result;
	__asm {
		push edi
		mov edi, dword ptr [esp + 8]
		mov eax, dword ptr [edi + 0x10]
		push eax
		push edi
		call gm_GetFieldByType
		lea ecx, [esp + 0x10]
		push eax
		push ecx
		push 0
		push 0
		mov dword ptr [edi + 0x10], eax
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_resolved
		push 1
		push 0x1002d0f4
		push 0x33af
		push 0x1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop edi
		ret
	L_resolved:
		mov al, byte ptr [edi + 0x14]
		push ebx
		xor ebx, ebx
		lea edx, [edi + 0x15]
		test al, al
		jbe L_after_loop
		push esi
	L_loop:
		xor eax, eax
		mov al, byte ptr [edx]
		inc edx
		fld dword ptr [edx]
		lea ecx, [eax + eax*2 + 0x24]
		mov eax, dword ptr [esp + 0x10]
		shl ecx, 2
		add edx, 4
		fadd dword ptr [ecx + eax]
		fstp dword ptr [ecx + eax]
		mov esi, dword ptr [esp + 0x10]
		fld dword ptr [ecx + esi]
		fcomp _g_stat_max_d
		fnstsw ax
		test ah, 1
		jne L_clamp_chk
		fld dword ptr [ecx + esi]
		fcomp _g_stat_min_d
		fnstsw ax
		test ah, 1
		je L_use_max
	L_clamp_chk:
		fld dword ptr [ecx + esi]
		fcomp _g_stat_max_d
		fnstsw ax
		test ah, 1
		je L_load_min
		fld _g_stat_max_d
		jmp L_store
	L_load_min:
		fld dword ptr [ecx + esi]
		jmp L_store
	L_use_max:
		fld _g_stat_min_d
	L_store:
		fstp dword ptr [ecx + esi]
		xor eax, eax
		inc ebx
		mov al, byte ptr [edi + 0x14]
		cmp ebx, eax
		jb L_loop
		pop esi
	L_after_loop:
		mov eax, dword ptr [esp + 0x10]
		pop ebx
		test eax, eax
		je L_done
		mov byte ptr [eax], 1
	L_done:
		xor eax, eax
		pop edi
		ret
	}
}
