
#include "../command_internal.h"
#include "../../../Units/Error/error.h"

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 346B
 *    CFlags: 
 *    Symbol: _ExMoveObject
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExMoveObjekt(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   int iVar2;
 *   int iVar3;
 *   int *piVar4;
 *   int *piVar5;
 *   uint line;
 *   char *msg;
 *   int iVar6;
 *   void *pvStack_8;
 *   void *pvStack_4;
 *   
 *   iVar6 = param_1;
 *   iVar2 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x14));
 *   *(int *)(iVar6 + 0x14) = iVar2;
 *   iVar2 = gm_ResolveEntityById(&pvStack_8,(void **)&param_1,&pvStack_4,iVar2);
 *   if (iVar2 == 0) {
 *     iVar6 = 8;
 *     msg = s_cm_ExMoveObjekt___Invalid__quell_1002d024;
 *     line = 0x30a1;
 *   }
 *   else {
 *     if (pvStack_8 == (void *)0x0) {
 *       if (param_1 == 0) {
 *         piVar4 = (int *)((int)pvStack_4 + 0x178);
 *       }
 *       else {
 *         piVar4 = (int *)(param_1 + 0x14);
 *       }
 *     }
 *     else {
 *       piVar4 = (int *)((int)pvStack_8 + 0x5d);
 *     }
 *     iVar2 = gm_GetFieldByType((char *)iVar6,*(int *)(iVar6 + 0x10));
 *     *(int *)(iVar6 + 0x10) = iVar2;
 *     iVar2 = gm_ResolveEntityById(&pvStack_8,(void **)&param_1,&pvStack_4,iVar2);
 *     if (iVar2 == 0) {
 *       iVar6 = 1;
 *       msg = s_cm_ExMoveObjekt___Invalid__ziel__1002cff4;
 *       line = 0x30bd;
 */


extern char s_cm_ExMoveObjekt___Invalid__quell_1002d024[];
extern char s_cm_ExMoveObjekt___Invalid__ziel__1002cff4[];
extern char s_cm_ExMoveObjekt___Objekt_nicht_v_1002cfc4[];

/* Execution handler: moves an object from one inventory slot
 * to another. Validates source and destination entities, then
 * transfers the object via gm_SubObjekt + gm_AddOrAccumulateObject. */

// FUNCTION: SERVER 0x1000e530
__declspec(naked) int __cdecl cm_ExMoveObjekt(int cmd, char* result)
{
	(void) cmd;
	(void) result;
	__asm {
		sub esp, 8
		push ebx
		push esi
		mov esi, dword ptr [esp + 0x14]
		push edi
		mov eax, dword ptr [esi + 0x14]
		push eax
		push esi
		call gm_GetFieldByType
		lea ecx, [esp + 0x18]
		mov dword ptr [esi + 0x14], eax
		push eax
		lea edx, [esp + 0x24]
		push ecx
		lea eax, [esp + 0x1c]
		push edx
		push eax
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_src_ok
		push 8
		push offset s_cm_ExMoveObjekt___Invalid__quell_1002d024
		push 0x30a1
		jmp L_log_fail
	L_src_ok:
		mov eax, dword ptr [esp + 0xc]
		test eax, eax
		je L_src_b
		lea ebx, [eax + 0x5d]
		jmp L_src_done
	L_src_b:
		mov eax, dword ptr [esp + 0x18]
		test eax, eax
		je L_src_c
		lea ebx, [eax + 0x14]
		jmp L_src_done
	L_src_c:
		mov ecx, dword ptr [esp + 0x10]
		lea ebx, [ecx + 0x178]
	L_src_done:
		mov edx, dword ptr [esi + 0x10]
		push edx
		push esi
		call gm_GetFieldByType
		mov dword ptr [esi + 0x10], eax
		push eax
		lea eax, [esp + 0x1c]
		lea ecx, [esp + 0x24]
		push eax
		lea edx, [esp + 0x1c]
		push ecx
		push edx
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_dst_ok
		push 1
		push offset s_cm_ExMoveObjekt___Invalid__ziel__1002cff4
		push 0x30bd
		jmp L_log_fail
	L_dst_ok:
		mov eax, dword ptr [esp + 0xc]
		test eax, eax
		je L_dst_b
		lea edi, [eax + 0x5d]
		jmp L_dst_done
	L_dst_b:
		mov eax, dword ptr [esp + 0x18]
		test eax, eax
		je L_dst_c
		lea edi, [eax + 0x14]
		jmp L_dst_done
	L_dst_c:
		mov eax, dword ptr [esp + 0x10]
		lea edi, [eax + 0x178]
	L_dst_done:
		mov ecx, dword ptr [esi + 0x18]
		push ecx
		push esi
		call gm_GetFieldByType
		mov dword ptr [esi + 0x18], eax
		mov ecx, dword ptr [ebx]
		add esp, 8
		xor edx, edx
		test ecx, ecx
		mov dword ptr [esp + 0x18], ecx
		je L_notfound
	L_scan:
		cmp dword ptr [ecx + 2], eax
		je L_have_node
		mov edx, ecx
		mov ecx, dword ptr [ecx + 0x3f]
		test ecx, ecx
		mov dword ptr [esp + 0x18], ecx
		jne L_scan
		jmp L_notfound
	L_have_node:
		test edx, edx
		jne L_unlink_prev
		mov edx, dword ptr [ecx + 0x3f]
		mov dword ptr [ebx], edx
		jmp L_after_unlink
	L_unlink_prev:
		mov eax, dword ptr [ecx + 0x3f]
		mov dword ptr [edx + 0x3f], eax
	L_after_unlink:
		mov eax, dword ptr [esp + 0x18]
		test eax, eax
		jne L_attach
	L_notfound:
		push 8
		push offset s_cm_ExMoveObjekt___Objekt_nicht_v_1002cfc4
		push 0x30f9
	L_log_fail:
		push offset s_D__Develop_DieGildeAddOn_command_1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop edi
		pop esi
		pop ebx
		add esp, 8
		ret
	L_attach:
		mov ecx, dword ptr [esi + 0x10]
		mov dword ptr [eax + 6], ecx
		mov eax, dword ptr [esp + 0x18]
		mov edx, dword ptr [edi]
		mov dword ptr [eax + 0x3f], edx
		mov eax, dword ptr [esp + 0x1c]
		mov ecx, dword ptr [esp + 0x18]
		test eax, eax
		mov dword ptr [edi], ecx
		je L_done
		mov byte ptr [eax], 1
	L_done:
		pop edi
		pop esi
		xor eax, eax
		pop ebx
		add esp, 8
		ret
	}
}
