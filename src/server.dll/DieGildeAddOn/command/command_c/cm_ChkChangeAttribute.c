
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

#include "../command_internal.h"
#include "../../../Units/Error/error.h"


extern char s_cm_ChkChangeAttribute___Invalid_I_1002c9e0[];
extern char s_cm_ChkChangeAttribute___Error_i_1002c9a0[];
extern char s_cm_ChkChangeAttribute___Source_obj_1002c958[];
extern char s_cm_ChkChangeAttribute___Target_obj_1002c90c[];

#pragma pack(push, 1)
typedef struct {
	signed char kind;
	signed char value;
	unsigned short offs;
} AttrEntry;
#pragma pack(pop)

/* Validation handler: resolves entity by ID and validates each
 * attribute field descriptor (kind/value/offset) in the command
 * payload. Returns 1 on invalid entity ID. */

// FUNCTION: SERVER 0x1000cde0
__declspec(naked) int __cdecl cm_ChkChangeAttribute(int param_1, char* param_2)
{
	(void) param_1;
	(void) param_2;
	__asm {
		sub esp, 0x10
		push ebx
		push ebp
		push esi
		push edi
		mov edi, dword ptr [esp + 0x24]
		mov eax, dword ptr [edi + 0x10]
		push eax
		push edi
		call gm_GetFieldByType
		lea ecx, [esp + 0x18]
		mov dword ptr [edi + 0x10], eax
		push eax
		lea edx, [esp + 0x28]
		push ecx
		lea eax, [esp + 0x28]
		push edx
		push eax
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_resolved
		push 1
		push offset s_cm_ChkChangeAttribute___Invalid_I_1002c9e0
		push 0x243d
		jmp L_log_and_fail
	L_resolved:
		mov eax, dword ptr [esp + 0x18]
		mov edx, dword ptr [esp + 0x10]
		test eax, eax
		je L_chk_b
		mov ebp, eax
		jmp L_have_base
	L_chk_b:
		mov eax, dword ptr [esp + 0x1c]
		test eax, eax
		mov ebp, eax
		jne L_have_base
		mov ebp, edx
	L_have_base:
		mov al, byte ptr [edi + 0x14]
		lea esi, [edi + 0x15]
		test al, al
		mov dword ptr [esp + 0x14], 0
		jbe L_done
	L_iter:
		movsx ebx, byte ptr [esi]
		movsx edi, byte ptr [esi + 1]
		inc esi
		xor eax, eax
		inc esi
		mov ax, word ptr [esi]
		add esi, 2
		add eax, ebp
		test edx, edx
		je L_after_check
		lea ecx, [edx + 4]
		cmp eax, ecx
		je L_error_self
		lea ecx, [edx + 0x5c]
		cmp eax, ecx
		jne L_after_check
		mov eax, dword ptr [esi]
		mov edx, dword ptr [ecx]
		add eax, edx
		push eax
		call gm_LookupEntityRecordById
		add esp, 4
		test eax, eax
		je L_error_src
		mov eax, dword ptr [eax + 0x5c]
		mov edx, dword ptr [esp + 0x10]
		cmp eax, -1
		je L_after_check
		cmp eax, dword ptr [edx + 4]
		jne L_error_tgt
	L_after_check:
		mov eax, ebx
		dec eax
		je L_kind1
		dec eax
		je L_kind2
		sub eax, 2
		jne L_kind_done
		test edi, edi
		jbe L_kind_done
		lea esi, [esi + edi*4]
		jmp L_kind_done
	L_kind2:
		test edi, edi
		jbe L_kind_done
		lea esi, [esi + edi*2]
		jmp L_kind_done
	L_kind1:
		test edi, edi
		jbe L_kind_done
		add esi, edi
	L_kind_done:
		mov edi, dword ptr [esp + 0x24]
		mov eax, dword ptr [esp + 0x14]
		xor ecx, ecx
		inc eax
		mov cl, byte ptr [edi + 0x14]
		mov dword ptr [esp + 0x14], eax
		cmp eax, ecx
		jb L_iter
	L_done:
		pop edi
		pop esi
		pop ebp
		xor eax, eax
		pop ebx
		add esp, 0x10
		ret
	L_error_self:
		push 1
		push offset s_cm_ChkChangeAttribute___Error_i_1002c9a0
		push 0x2479
		jmp L_log_and_fail
	L_error_src:
		push 1
		push offset s_cm_ChkChangeAttribute___Source_obj_1002c958
		push 0x249b
		jmp L_log_and_fail
	L_error_tgt:
		push 1
		push offset s_cm_ChkChangeAttribute___Target_obj_1002c90c
		push 0x24a5
	L_log_and_fail:
		push offset s_D__Develop_DieGildeAddOn_command_1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop edi
		pop esi
		pop ebp
		pop ebx
		add esp, 0x10
		ret
	}
}
