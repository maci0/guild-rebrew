
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 162B
 *    CFlags: 
 *    Symbol: _CheckChangeBits
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ChkChangeBits(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   int iVar2;
 *   void *pvVar3;
 *   uint line;
 *   char *msg;
 *   void *local_8;
 *   void *local_4;
 *   
 *   iVar1 = param_1;
 *   iVar2 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x10));
 *   *(int *)(iVar1 + 0x10) = iVar2;
 *   iVar2 = gm_ResolveEntityById((void **)&param_1,&local_4,&local_8,iVar2);
 *   if (iVar2 == 0) {
 *     msg = s_cm_ChkChangeBits___Invalid_Id_1002ca54;
 *     line = 0x250d;
 *   }
 *   else {
 *     pvVar3 = (void *)param_1;
 *     if ((param_1 == 0) && (pvVar3 = local_4, local_4 == (void *)0x0)) {
 *       pvVar3 = local_8;
 *     }
 *     if ((((local_8 == (void *)0x0) ||
 *          ((uint *)(*(int *)(iVar1 + 0x14) + (int)pvVar3) != (uint *)((int)local_8 + 0x1c8))) ||
 *         ((*(uint *)(iVar1 + 0x1c) & 0x800000) == 0)) ||
 *        ((*(uint *)((int)local_8 + 0x1c8) & 0x800000) == 0)) {
 *       return 0;
 *     }
 *     msg = s_cm_ChkChangeBits___Invalid_actio_1002ca04;
 *     line = 0x2533;
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,msg,1);
 *   return 1;
 * }
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ChkChangeBits___Invalid_Id_1002ca54[];
extern char s_cm_ChkChangeBits___Invalid_actio_1002ca04[];

/* Validation handler: resolves entity by ID from the command
 * packet's field type info. Logs and rejects if entity ID is
 * invalid. Used as precondition check for bit-field changes. */

// FUNCTION: SERVER 0x1000cf30
__declspec(naked) int __cdecl cm_ChkChangeBits(int cmd, char* result)
{
	(void) cmd;
	(void) result;
	__asm {
		sub esp, 8
		push esi
		mov esi, dword ptr [esp + 0x10]
		mov eax, dword ptr [esi + 0x10]
		push eax
		push esi
		call gm_GetFieldByType
		lea ecx, [esp + 0xc]
		mov dword ptr [esi + 0x10], eax
		push eax
		lea edx, [esp + 0x14]
		push ecx
		lea eax, [esp + 0x20]
		push edx
		push eax
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_resolved
		push 1
		push 0x1002ca54
		push 0x250d
		jmp L_log
	L_resolved:
		mov ecx, dword ptr [esp + 0x10]
		mov eax, dword ptr [esp + 4]
		test ecx, ecx
		jne L_have_ref
		mov ecx, dword ptr [esp + 8]
		test ecx, ecx
		jne L_have_ref
		mov ecx, eax
	L_have_ref:
		test eax, eax
		je L_ret0
		mov edx, dword ptr [esi + 0x14]
		add eax, 0x1c8
		add edx, ecx
		cmp edx, eax
		jne L_ret0
		test dword ptr [esi + 0x1c], 0x800000
		je L_ret0
		test dword ptr [eax], 0x800000
		je L_ret0
		push 1
		push 0x1002ca04
		push 0x2533
	L_log:
		push 0x1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop esi
		add esp, 8
		ret
	L_ret0:
		xor eax, eax
		pop esi
		add esp, 8
		ret
	}
}
