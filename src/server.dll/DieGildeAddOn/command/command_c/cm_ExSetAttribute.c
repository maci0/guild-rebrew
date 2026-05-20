
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

#include "../../../Units/Error/error.h"
#include "../command_internal.h"

extern char s_cm_ExSetAttribute___Invalid_Id_1002d0d4[];
/* Command handler: applies attribute updates to a game entity.
 * Resolves the target entity by ID from the command packet (offset 0x10),
 * then iterates over a list of field descriptors starting at offset 0x15.
 * Each descriptor contains: fieldSize (1/2/4 bytes), count, and a 16-bit
 * offset into the entity struct. Copies 'count' elements of the given size
 * from the command buffer into the entity at the specified offset.
 * Sets *param_2 = 1 on success (if non-null). Returns 1 on invalid entity ID. */

// FUNCTION: SERVER 0x1000e8d0
__declspec(naked) int __cdecl cm_ExSetAttribute(int cmd, char* result)
{
	(void) cmd;
	(void) result;
	__asm {
		sub esp, 8
		push ebp
		mov ebp, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 0x10]
		push eax
		push ebp
		call gm_GetFieldByType
		lea ecx, [esp + 0x10]
		mov dword ptr [ebp + 0x10], eax
		push eax
		lea edx, [esp + 0x10]
		push ecx
		lea eax, [esp + 0x20]
		push edx
		push eax
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_resolved
		push 1
		push 0x1002d0d4
		push 0x32ed
		push 0x1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop ebp
		add esp, 8
		ret
	L_resolved:
		mov eax, dword ptr [esp + 0x10]
		push ebx
		test eax, eax
		push edi
		je L_chk_obj
		mov edi, eax
		jmp L_have_p1
	L_chk_obj:
		mov eax, dword ptr [esp + 0xc]
		test eax, eax
		mov edi, eax
		jne L_have_p1
		mov edi, dword ptr [esp + 0x10]
	L_have_p1:
		mov cl, byte ptr [ebp + 0x14]
		xor ebx, ebx
		test cl, cl
		lea eax, [ebp + 0x15]
		jbe L_loop_done
		push esi
	L_loop:
		movsx edx, byte ptr [eax]
		movsx esi, byte ptr [eax + 1]
		inc eax
		xor ecx, ecx
		inc eax
		mov cx, word ptr [eax]
		add eax, 2
		add ecx, edi
		dec edx
		je L_size1
		dec edx
		je L_size2
		sub edx, 2
		jne L_loop_next
		test esi, esi
		jbe L_loop_next
	L_loop_size4:
		mov edx, dword ptr [eax]
		add eax, 4
		mov dword ptr [ecx], edx
		add ecx, 4
		dec esi
		jne L_loop_size4
		jmp L_loop_next
	L_size2:
		test esi, esi
		jbe L_loop_next
	L_loop_size2_inner:
		mov dx, word ptr [eax]
		add eax, 2
		mov word ptr [ecx], dx
		add ecx, 2
		dec esi
		jne L_loop_size2_inner
		jmp L_loop_next
	L_size1:
		test esi, esi
		jbe L_loop_next
	L_loop_size1_inner:
		mov dl, byte ptr [eax]
		mov byte ptr [ecx], dl
		inc ecx
		inc eax
		dec esi
		jne L_loop_size1_inner
	L_loop_next:
		xor ecx, ecx
		inc ebx
		mov cl, byte ptr [ebp + 0x14]
		cmp ebx, ecx
		jb L_loop
		pop esi
	L_loop_done:
		mov eax, dword ptr [esp + 0x1c]
		pop edi
		test eax, eax
		pop ebx
		je L_done
		mov byte ptr [eax], 1
	L_done:
		xor eax, eax
		pop ebp
		add esp, 8
		ret
	}
}
