
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 135B
 *    CFlags: 
 *    Symbol: _ExSetEntityField
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExChangeFloat(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   int iVar2;
 *   void *pvStack_8;
 *   void *pvStack_4;
 *   
 *   iVar1 = param_1;
 *   iVar2 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x10));
 *   *(int *)(iVar1 + 0x10) = iVar2;
 *   iVar2 = gm_ResolveEntityById(&pvStack_4,&pvStack_8,(void **)&param_1,iVar2);
 *   if (iVar2 == 0) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x347f,
 *                        s_cm_ExChangeFloat___Invalid_Id_1002d134,1);
 *     return 1;
 *   }
 *   if ((param_1 == 0) && (param_1 = (int)pvStack_8, pvStack_8 == (void *)0x0)) {
 *     param_1 = (int)pvStack_4;
 *   }
 *   *(float *)(param_1 + *(int *)(iVar1 + 0x14)) =
 *        *(float *)(iVar1 + 0x18) + *(float *)(param_1 + *(int *)(iVar1 + 0x14));
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *   }
 *   return 0;
 * }
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ExChangeFloat___Invalid_Id_1002d134[];

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/* Execution handler: modifies a floating-point attribute on an
 * entity. Similar to cm_ExChangeAttribute but operates on float
 * values rather than integers. */

// FUNCTION: SERVER 0x1000eb70
__declspec(naked) int __cdecl cm_ExChangeFloat(int cmd, char* result)
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
		lea ecx, [esp + 0x18]
		mov dword ptr [esi + 0x10], eax
		push eax
		lea edx, [esp + 0x10]
		push ecx
		lea eax, [esp + 0x18]
		push edx
		push eax
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_resolved
		push 1
		push 0x1002d134
		push 0x347f
		push 0x1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop esi
		add esp, 8
		ret
	L_resolved:
		mov eax, dword ptr [esp + 0x10]
		test eax, eax
		jne L_have_addr
		mov eax, dword ptr [esp + 4]
		test eax, eax
		jne L_have_addr
		mov eax, dword ptr [esp + 8]
	L_have_addr:
		mov edx, dword ptr [esi + 0x14]
		fld dword ptr [esi + 0x18]
		fadd dword ptr [eax + edx]
		add eax, edx
		fstp dword ptr [eax]
		mov eax, dword ptr [esp + 0x14]
		test eax, eax
		je L_done
		mov byte ptr [eax], 1
	L_done:
		xor eax, eax
		pop esi
		add esp, 8
		ret
	}
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

