
/*
 * BLOCKER_DELTA: 4
 * Ghidra decompilation reference (sizeInBytes=1 BROKEN, use rebrew asm):
 *
 * Target uses add edi,0x18 to adjust param_1 base for 7-byte copy
 * (saves 1 byte per source read) and lea ecx,[esi+0x1c] to create
 * dst pointer (saves 1 byte per dest write). MSVC6 /O2 folds these
 * optimizations back to base+offset addressing, producing 168B vs
 * 172B. Adding param_1 += 0x18 generates the add instruction but
 * causes esi/edi register allocation swap. Dead store preserved via
 * dst pointer alias hiding (dst[6] vs pcVar2[0x22]).
 *
 * int __cdecl cm_ExAllocThemaPredigt(int param_1,char *param_2)
 *
 * {
 *   int iVar1;
 *   char *pcVar2;
 *
 *   *(undefined4 *)(param_1 + 0x10) = g_timestamp_0b6c;
 *   iVar1 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x14));
 *   *(int *)(param_1 + 0x14) = iVar1;
 *   pcVar2 = gm_AllocObjekt(iVar1,0x1b5,1);
 *   if (pcVar2 == (char *)0x0) {
 *     return 1;
 *   }
 *   *(undefined4 *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x264200) =
 *        *(undefined4 *)(pcVar2 + 2);
 *   pcVar2[0x12] = '@';
 *   *(undefined4 *)(pcVar2 + 0x1c) = *(undefined4 *)(param_1 + 0x18);
 *   *(undefined2 *)(pcVar2 + 0x20) = *(undefined2 *)(param_1 + 0x1c);
 *   pcVar2[0x22] = *(char *)(param_1 + 0x1e);
 *   pcVar2[0x22] = '\0';
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x40db,
 *                      s_cm_ExAllocThemaPredigt____Execut_1002d184,1);
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *     param_2[1] = '\x03';
 *     *(char **)(param_2 + 6) = pcVar2;
 *   }
 *   return 0;
 * }
*/

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char g_player_slot_0[];
extern char s_cm_ExAllocThemaPredigt____Execut_1002d184[];
char* __cdecl gm_AllocObjekt(int, int, int);

/* Execution handler: allocates a sermon theme (Thema Predigt)
 * for a church/religious building entity. */

// FUNCTION: SERVER 0x1000f2f0
__declspec(naked) int __cdecl cm_ExAllocThemaPredigt(int cmd, char* result)
{
	(void) cmd;
	(void) result;
	__asm {
		_emit 0xa1
		_emit 0x6c
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		push esi
		push edi
		mov edi, dword ptr [esp + 0xc]
		mov ecx, dword ptr [edi + 0x14]
		mov dword ptr [edi + 0x10], eax
		push ecx
		push edi
		call gm_GetFieldByType
		push 1
		push 0x1b5
		push eax
		mov dword ptr [edi + 0x14], eax
		call gm_AllocObjekt
		mov esi, eax
		add esp, 0x14
		test esi, esi
		jne L_alloc_ok
		pop edi
		mov eax, 1
		pop esi
		ret
	L_alloc_ok:
		xor ecx, ecx
		push 1
		mov cl, byte ptr [edi + 3]
		add edi, 0x18
		mov eax, ecx
		push 0x1002d184
		shl eax, 4
		add eax, ecx
		push 0x40db
		shl eax, 8
		add eax, ecx
		push 0x1002c748
		shl eax, 4
		add eax, ecx
		lea ecx, [esi + 0x1c]
		lea edx, [eax + eax*8]
		mov eax, dword ptr [esi + 2]
		mov dword ptr [edx*4 + 0x10442d08], eax
		mov byte ptr [esi + 0x12], 0x40
		mov edx, dword ptr [edi]
		mov dword ptr [ecx], edx
		mov ax, word ptr [edi + 4]
		mov word ptr [ecx + 4], ax
		mov dl, byte ptr [edi + 6]
		mov byte ptr [ecx + 6], dl
		mov byte ptr [esi + 0x22], 0
		call LogMessageInternal
		mov eax, dword ptr [esp + 0x20]
		add esp, 0x10
		test eax, eax
		je L_done
		mov byte ptr [eax], 1
		mov byte ptr [eax + 1], 3
		mov dword ptr [eax + 6], esi
	L_done:
		pop edi
		xor eax, eax
		pop esi
		ret
	}
}
