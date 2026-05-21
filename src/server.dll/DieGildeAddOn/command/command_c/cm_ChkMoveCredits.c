
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 267B
 *    CFlags: 
 *    Symbol: _CheckMoveCredits
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ChkMoveCredits(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   int iVar2;
 *   int *piVar3;
 *   undefined4 extraout_ECX;
 *   uint line;
 *   char *msg;
 *   void *local_8;
 *   void *local_4;
 *   
 *   iVar1 = param_1;
 *   if (*(int *)(param_1 + 0x14) == -1) {
 *     return 0;
 *   }
 *   iVar2 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x14));
 *   *(int *)(iVar1 + 0x14) = iVar2;
 *   iVar2 = gm_ResolveEntityById((void **)&param_1,&local_8,&local_4,iVar2);
 *   if (iVar2 == 0) {
 *     msg = s_cm_ChkMoveCredits____Invalid__qu_1002c7a4;
 *     line = 0x22f9;
 *   }
 *   else {
 *     if (param_1 == 0) {
 *       if (local_8 == (void *)0x0) {
 *         piVar3 = (int *)((int)local_4 + 0x178);
 *       }
 *       else {
 *         piVar3 = (int *)((int)local_8 + 0x14);
 *       }
 *     }
 *     else {
 *       piVar3 = (int *)(param_1 + 0x5d);
 *     }
 *     iVar2 = gm_QueryEntitySum(*piVar3,CONCAT31((int3)((uint)extraout_ECX >> 8),
 *                                             *(undefined1 *)(iVar1 + 0x1c)));
 *     if (-1 < iVar2 - *(int *)(iVar1 + 0x1d)) {
 *       return 0;
 *     }
 *     msg = s_cm_ChkMoveCredits____Not_enough_m_1002c774;
 *     line = 0x231b;
*/

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ChkMoveCredits____Invalid__qu_1002c7a4[];
extern char s_cm_ChkMoveCredits____Not_enough_m_1002c774[];

/* Validation handler: resolves entity by ID and checks if a
 * credit (currency) transfer is valid. Returns 1 on invalid
 * entity, otherwise validates the transfer amount. */

// FUNCTION: SERVER 0x1000cb20
__declspec(naked) int __cdecl cm_ChkMoveCredits(int cmd, char* result)
{
	(void) cmd;
	(void) result;
	__asm {
		sub esp, 8
		push esi
		mov esi, dword ptr [esp + 0x10]
		mov eax, dword ptr [esi + 0x14]
		cmp eax, -1
		je L_ret0
		push eax
		push esi
		call gm_GetFieldByType
		mov dword ptr [esi + 0x14], eax
		push eax
		lea eax, [esp + 0x14]
		lea ecx, [esp + 0x10]
		push eax
		lea edx, [esp + 0x20]
		push ecx
		push edx
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_resolved
		push 1
		push 0x1002c7a4
		push 0x22f9
		jmp L_log
	L_resolved:
		mov eax, dword ptr [esp + 0x10]
		test eax, eax
		je L_no_p1
		add eax, 0x5d
		jmp L_have_sum
	L_no_p1:
		mov eax, dword ptr [esp + 4]
		test eax, eax
		je L_use_area
		add eax, 0x14
		jmp L_have_sum
	L_use_area:
		mov eax, dword ptr [esp + 8]
		add eax, 0x178
	L_have_sum:
		mov cl, byte ptr [esi + 0x1c]
		mov edx, dword ptr [eax]
		push ecx
		push edx
		call gm_QueryEntitySum
		mov ecx, dword ptr [esi + 0x1d]
		add esp, 8
		sub eax, ecx
		jns L_ret0
		push 1
		push 0x1002c774
		push 0x231b
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
