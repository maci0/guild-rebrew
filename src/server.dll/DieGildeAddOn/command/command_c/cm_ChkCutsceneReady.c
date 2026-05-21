
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 120B
 *    CFlags: 
 *    Symbol: _CheckCutsceneReady
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ChkCutsceneReady(char *obj)
 * 
 * {
 *   int entity_ptr;
 *   int *id_ptr;
 *   int i;
 *   
 *   if (*(int *)(obj + 0x10) == -1) {
 *     return 1;
 *   }
 *   i = 0;
 *   id_ptr = (int *)(obj + 0x14);
 *   while( true ) {
 *     entity_ptr = gm_LookupEntityRecordById(*id_ptr);
 *     if (((entity_ptr != 0) &&
 *         (((*(char *)(entity_ptr + 2) == '\x06' || (*(char *)(entity_ptr + 2) == '\a')) &&
 *          (*(int *)(entity_ptr + 0x20c) != -1)))) &&
 *        (*(int *)(entity_ptr + 0x20c) != *(int *)(obj + 0x10))) break;
 *     i = i + 1;
 *     id_ptr = id_ptr + 1;
 *     if (0xf < i) {
 *       return 0;
 *     }
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x26db,
 *                      s_cm_ChkCutsceneReady____failed____1002caa8,1);
 *   return 1;
 * }
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ChkCutsceneReady____failed____1002caa8[];

/* Validation handler: checks if up to 16 entities referenced
 * by IDs in the command payload are all in cutscene-ready state
 * (entity type 0x06 or 0x07). Returns 0 when all are ready,
 * 1 if any entity is missing or not ready. */

// FUNCTION: SERVER 0x1000d260
__declspec(naked) int __cdecl cm_ChkCutsceneReady(char* obj)
{
	(void) obj;
	__asm {
		push ebx
		mov ebx, dword ptr [esp + 8]
		push esi
		push edi
		cmp dword ptr [ebx + 0x10], -1
		jne L_have_target
		pop edi
		pop esi
		mov eax, 1
		pop ebx
		ret
	L_have_target:
		xor edi, edi
		lea esi, [ebx + 0x14]
	L_loop:
		mov eax, dword ptr [esi]
		push eax
		call gm_LookupEntityRecordById
		add esp, 4
		test eax, eax
		je L_continue
		mov cl, byte ptr [eax + 2]
		cmp cl, 6
		je L_chk_ent
		cmp cl, 7
		jne L_continue
	L_chk_ent:
		mov eax, dword ptr [eax + 0x20c]
		cmp eax, -1
		je L_continue
		cmp eax, dword ptr [ebx + 0x10]
		jne L_break
	L_continue:
		inc edi
		add esi, 4
		cmp edi, 0x10
		jl L_loop
		pop edi
		pop esi
		xor eax, eax
		pop ebx
		ret
	L_break:
		push 1
		push 0x1002caa8
		push 0x26db
		push 0x1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop edi
		pop esi
		pop ebx
		ret
	}
}
