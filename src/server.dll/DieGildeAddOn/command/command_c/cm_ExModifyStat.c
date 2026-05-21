
/*
 * Ghidra decompilation reference:
 * /+ WARNING: Globals starting with '_' overlap smaller symbols at the same address * / * / * [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 159B
 *    CFlags:
 *    Symbol: _ModifyEntityStat
 *    Files: DieGildeAddOn/command/command.c * /
 *
 * int __cdecl cm_ExModifyStat(int *param_1)
 *
 * {
 *   int iVar1;
 *   float fVar2;
 *   int iVar3;
 *   long lVar4;
 *
 *   iVar3 = gm_LookupEntityRecordById(param_1[4]);
 *   if (((iVar3 == 0) || (iVar1 = param_1[5], iVar1 < 0)) || (4 < iVar1)) {
 *     return 1;
 *   }
 *   fVar2 = (float)(int)(param_1[6] + (uint)*(byte *)(iVar1 + 0x80 + iVar3));
 *   if (((_g_stat_max <= fVar2) || (_g_stat_min < fVar2)) && (_g_stat_max <= fVar2)) {
 *     lVar4 = _ftol();
 *     *(char *)(iVar1 + 0x80 + iVar3) = (char)lVar4;
 *     return 0;
 *   }
 *   lVar4 = _ftol();
 *   *(char *)(iVar1 + 0x80 + iVar3) = (char)lVar4;
 *   return 0;
 * }
 */

#include "../command_internal.h"

extern float _g_stat_max;
extern float _g_stat_min;
extern unsigned int __ftol(void);

/* Execution handler: modifies a character stat by index.
 * Reads entity ID, stat index, and delta from the command
 * payload. Applies change with clamping via gm_MapEntityStatRange. */

// FUNCTION: SERVER 0x100100a0
__declspec(naked) int __cdecl cm_ExModifyStat(int* cmd)
{
	(void) cmd;
	__asm {
		push ebx
		mov ebx, dword ptr [esp + 8]
		push esi
		push edi
		mov eax, dword ptr [ebx + 0x10]
		push eax
		call gm_LookupEntityRecordById
		mov edi, eax
		add esp, 4
		test edi, edi
		je L_fail
		mov esi, dword ptr [ebx + 0x14]
		test esi, esi
		jl L_fail
		cmp esi, 4
		jg L_fail
		mov edx, dword ptr [ebx + 0x18]
		xor ecx, ecx
		mov cl, byte ptr [esi + edi + 0x80]
		add edx, ecx
		mov dword ptr [esp + 0x10], edx
		fild dword ptr [esp + 0x10]
		fcom dword ptr _g_stat_max
		fnstsw ax
		test ah, 1
		je L_check_max
		fcom dword ptr _g_stat_min
		fnstsw ax
		test ah, 0x41
		jne L_use_min
	L_check_max:
		fcom dword ptr _g_stat_max
		fnstsw ax
		test ah, 1
		jne L_call_skip_clamp
		fstp st(0)
		fld dword ptr _g_stat_max
		call __ftol
		mov byte ptr [esi + edi + 0x80], al
		pop edi
		pop esi
		xor eax, eax
		pop ebx
		ret
	L_use_min:
		fstp st(0)
		fld dword ptr _g_stat_min
	L_call_skip_clamp:
		call __ftol
		mov byte ptr [esi + edi + 0x80], al
		pop edi
		pop esi
		xor eax, eax
		pop ebx
		ret
	L_fail:
		pop edi
		pop esi
		mov eax, 1
		pop ebx
		ret
	}
}
