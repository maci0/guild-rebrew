
#include "../command_internal.h"

extern char* g_entity_type_table;

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 135B
 *    CFlags: 
 *    Symbol: _GetBuildingStatCount
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_GetBuildingStatCount(uchar *param_1)
 * 
 * {
 *   char cVar1;
 *   int iVar2;
 *   int iVar3;
 *   
 *   iVar2 = *(int *)(param_1 + 0x65);
 *   cVar1 = *(char *)(g_entity_type_table + (uint)*param_1 * 0x24d + 0x247);
 *   if (cVar1 == '\x01') {
 *     iVar3 = 8;
 *     if (*(char *)(iVar2 + 0x19) == '\x01') {
 *       return 0xc;
 *     }
 *   }
 *   else if (cVar1 == '\x02') {
 *     iVar3 = 0xc;
 *     if (*(char *)(iVar2 + 0x19) == '\x01') {
 *       iVar3 = 0x12;
 *     }
 *     if (*(char *)(iVar2 + 0x1a) == '\x01') {
 *       return iVar3 + 2;
 *     }
 *   }
 *   else {
 *     iVar3 = 0x10;
 *     if (*(char *)(iVar2 + 0x19) == '\x01') {
 *       iVar3 = 0x18;
 *     }
 *     if (*(char *)(iVar2 + 0x1a) == '\x01') {
 *       iVar3 = iVar3 + 4;
 *     }
 *     if (*(char *)(iVar2 + 0x1b) == '\x01') {
 *       iVar3 = iVar3 + 2;
 *     }
 *   }
 *   return iVar3;
 * }
 */

// FUNCTION: SERVER 0x100104a0
__declspec(naked) int __cdecl cm_GetBuildingStatCount(uchar* param_1)
{
	(void) param_1;
	__asm {
		mov edx, dword ptr [esp + 4]
		xor ecx, ecx
		push ebx
		push esi
		mov cl, byte ptr [edx]
		mov esi, dword ptr [g_entity_type_table]
		add esi, ecx
		lea eax, [ecx + ecx*2]
		shl eax, 4
		add eax, ecx
		mov ecx, dword ptr [edx + 0x65]
		mov dl, 1
		lea eax, [eax + eax*2]
		lea eax, [esi + eax*4]
		mov al, byte ptr [eax + 0x247]
		cmp al, dl
		jne L_chk2
		mov bl, byte ptr [ecx + 0x19]
		mov eax, 8
		cmp bl, dl
		jne L_done
		pop esi
		mov eax, 0xc
		pop ebx
		ret
	L_chk2:
		cmp al, 2
		jne L_else
		mov bl, byte ptr [ecx + 0x19]
		mov eax, 0xc
		cmp bl, dl
		jne L_chk1a_t2
		mov eax, 0x12
	L_chk1a_t2:
		cmp byte ptr [ecx + 0x1a], dl
		jne L_done
		pop esi
		add eax, 2
		pop ebx
		ret
	L_else:
		mov bl, byte ptr [ecx + 0x19]
		mov eax, 0x10
		cmp bl, dl
		jne L_chk1a_else
		mov eax, 0x18
	L_chk1a_else:
		cmp byte ptr [ecx + 0x1a], dl
		jne L_chk1b
		add eax, 4
	L_chk1b:
		cmp byte ptr [ecx + 0x1b], dl
		jne L_done
		add eax, 2
	L_done:
		pop esi
		pop ebx
		ret
	}
}
